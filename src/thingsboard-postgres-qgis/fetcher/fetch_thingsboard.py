import os
import io
import sys
import json
import time
import psycopg2
import requests
import logging
from datetime import datetime
from dotenv import load_dotenv

# Cấu hình logging
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S"
)

load_dotenv()
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# ThingsBoard thông tin từ .env
THINGSBOARD_URL = os.getenv("THINGSBOARD_URL")
TB_USERNAME = os.getenv("TB_USERNAME")
TB_PASSWORD = os.getenv("TB_PASSWORD")
DEVICE_IDS = os.getenv("DEVICE_IDS") 
KEYS = os.getenv("KEYS") or "temp,Soil,hum,light,wind"
FETCH_INTERVAL = int(os.getenv("FETCH_INTERVAL", 10))

# PostgreSQL thông tin từ .env
DB_HOST = os.getenv("POSTGRES_HOST")
DB_PORT = os.getenv("POSTGRES_PORT")
DB_NAME = os.getenv("POSTGRES_DB")
DB_USER = os.getenv("POSTGRES_USER")
DB_PASS = os.getenv("POSTGRES_PASSWORD")

# Parse device list
DEVICES = {}
for pair in DEVICE_IDS.split(","):
    name, dev_id = pair.split(":")
    DEVICES[name.strip()] = dev_id.strip()

logging.info(f"Devices: {DEVICES}")
logging.info(f"PostgreSQL: {DB_USER}@{DB_HOST}:{DB_PORT}/{DB_NAME}")

# Kết nối PostgreSQL
def connect_db():
    try:
        conn = psycopg2.connect(
            host=DB_HOST, port=DB_PORT, database=DB_NAME,
            user=DB_USER, password=DB_PASS
        )
        logging.info("Connected to PostgreSQL successfully.")
        return conn
    except Exception as e:
        logging.error(f"PostgreSQL connection error: {e}")
        sys.exit(1)

# Tạo bảng nếu chưa tồn tại
def create_tables(conn):
    logging.info("Creating tables if not exist...")
    with conn.cursor() as cur:
        cur.execute("""
            CREATE TABLE IF NOT EXISTS sensor_point (
                id SERIAL PRIMARY KEY,
                name TEXT UNIQUE NOT NULL,
                location geometry(Point, 4326)
            );
        """)
        cur.execute("""
            CREATE TABLE IF NOT EXISTS sensor_data (
                id SERIAL PRIMARY KEY,
                sensor_id INT REFERENCES sensor_point(id) ON DELETE CASCADE,
                ts TIMESTAMP NOT NULL,
                temp DOUBLE PRECISION,
                Soil DOUBLE PRECISION,
                hum DOUBLE PRECISION,
                light DOUBLE PRECISION,
                wind DOUBLE PRECISION
            );
        """)
        conn.commit()
    logging.info("Tables ready.")

# Đảm bảo các điểm sensor tồn tại
def ensure_points(conn):
    with conn.cursor() as cur:
        for name in DEVICES.keys():
            cur.execute("INSERT INTO sensor_point (name) VALUES (%s) ON CONFLICT (name) DO NOTHING;", (name,))
        conn.commit()
    logging.info("Sensor points ensured.")

# Login ThingsBoard để lấy JWT token
def login_thingsboard():
    login_data = {"username": TB_USERNAME, "password": TB_PASSWORD}
    try:
        r = requests.post(f"{THINGSBOARD_URL}/api/auth/login", json=login_data)
        r.raise_for_status()
        jwt = r.json()["token"]
        logging.info("Logged in to ThingsBoard successfully.")
        return jwt
    except requests.exceptions.RequestException as e:
        logging.error(f"ThingsBoard login failed: {e}")
        sys.exit(1)

# Fetch data từ ThingsBoard
def fetch_data(device_id, jwt_token):
    url = f"{THINGSBOARD_URL}/api/plugins/telemetry/DEVICE/{device_id}/values/timeseries?keys={KEYS}"
    headers = {"X-Authorization": f"Bearer {jwt_token}"}
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        logging.info(f"Fetched data for device_id={device_id}")
        return response.json()
    except requests.exceptions.RequestException as e:
        logging.error(f"Fetch error for device_id={device_id}: {e}")
        return None

# Lưu dữ liệu vào PostgreSQL
def save_to_db(conn, device_name, data):
    with conn.cursor() as cur:
        cur.execute("SELECT id FROM sensor_point WHERE name = %s;", (device_name,))
        result = cur.fetchone()
        if not result:
            logging.warning(f"No sensor_point found for {device_name}")
            return
        sensor_id = result[0]

        record = {"ts": None, "temp": None, "Soil": None, "hum": None, "light": None, "wind": None}
        for key, values in data.items():
            if values:
                record[key] = values[0].get("value")
                record["ts"] = datetime.fromtimestamp(values[0]["ts"] / 1000.0)

        if record["ts"]:
            cur.execute("""
                INSERT INTO sensor_data (sensor_id, ts, temp, Soil, hum, light, wind)
                VALUES (%s, %s, %s, %s, %s, %s, %s);
            """, (sensor_id, record["ts"], record["temp"], record["Soil"], record["hum"], record["light"], record["wind"]))
            conn.commit()
            logging.info(f"[{device_name}] Data saved at {record['ts']}")
        else:
            logging.warning(f"No timestamp found in data for {device_name}")

# Main loop
if __name__ == "__main__":
    conn = connect_db()
    create_tables(conn)
    ensure_points(conn)

    JWT_TOKEN = login_thingsboard()  # login ThingsBoard trước khi fetch

    logging.info(f"Fetcher started. Interval = {FETCH_INTERVAL}s")
    while True:
        for name, device_id in DEVICES.items():
            logging.info(f"Fetching data for {name}...")
            data = fetch_data(device_id, JWT_TOKEN)
            if data:
                save_to_db(conn, name, data)
            else:
                logging.warning(f"No data returned for {name}")
        logging.info(f"Sleeping for {FETCH_INTERVAL}s")
        time.sleep(FETCH_INTERVAL)

