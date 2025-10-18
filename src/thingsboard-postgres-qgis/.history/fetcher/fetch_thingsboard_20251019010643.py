import os
import io
import sys
from dotenv import load_dotenv

# Load environment variables from .env file
load_dotenv()

# Configure UTF-8 output for Windows console
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

# --- ThingsBoard Cloud configuration ---
THINGSBOARD_URL = os.getenv("THINGSBOARD_URL")
DEVICE_ID = os.getenv("DEVICE_ID")
THINGSBOARD_JWT_TOKEN = os.getenv("JWT_TOKEN")
KEYS = os.getenv("KEYS")

# --- PostgreSQL configuration ---
DB_HOST = os.getenv("POSTGRES_HOST")
DB_PORT = os.getenv("POSTGRES_PORT")
DB_NAME = os.getenv("POSTGRES_DB")
DB_USER = os.getenv("POSTGRES_USER")
DB_PASS = os.getenv("POSTGRES_PASSWORD")

# --- Fetcher configuration ---
FETCH_INTERVAL = int(os.getenv("FETCH_INTERVAL", 10))

# Debug print to verify environment loading
print("ThingsBoard URL:", THINGSBOARD_URL)
print("Device ID:", DEVICE_ID)
print("Keys:", KEYS)
print(f"PostgreSQL: {DB_USER}@{DB_HOST}:{DB_PORT}/{DB_NAME}")

# --- Kết nối PostgreSQL ---
def connect_db():
    try:
        conn = psycopg2.connect(
            host=DB_HOST,
            port=DB_PORT,
            database=DB_NAME,
            user=DB_USER,
            password=DB_PASS
        )
        return conn
    except Exception as e:
        print("Lỗi kết nối PostgreSQL:", e)
        sys.exit(1)

# --- Tạo bảng nếu chưa có ---
def create_table(conn):
    with conn.cursor() as cur:
        cur.execute("""
            CREATE TABLE IF NOT EXISTS telemetry (
                id SERIAL PRIMARY KEY,
                ts TIMESTAMP NOT NULL,
                key TEXT NOT NULL,
                value DOUBLE PRECISION
            );
        """)
        conn.commit()

# --- Lưu dữ liệu xuống DB ---
def save_to_db(conn, data):
    with conn.cursor() as cur:
        for key, values in data.items():
            for item in values:
                ts = datetime.fromtimestamp(item["ts"] / 1000.0)
                val = item.get("value")
                cur.execute(
                    "INSERT INTO telemetry (ts, key, value) VALUES (%s, %s, %s);",
                    (ts, key, val)
                )
        conn.commit()
        print(f"Đã lưu {sum(len(v) for v in data.values())} bản ghi vào PostgreSQL.")

# --- Lấy dữ liệu từ ThingsBoard Cloud ---
def fetch_data():
    url = f"{THINGSBOARD_URL}/api/plugins/telemetry/DEVICE/{DEVICE_ID}/values/timeseries?keys={KEYS}"
    headers = {"X-Authorization": f"Bearer {THINGSBOARD_JWT_TOKEN}"}
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        data = response.json()
        print("Dữ liệu telemetry hiện có:")
        print(json.dumps(data, indent=2, ensure_ascii=False))
        return data
    except requests.exceptions.RequestException as e:
        print("Lỗi lấy dữ liệu từ ThingsBoard:", e)
        return None

# --- Chương trình chính ---
if __name__ == "__main__":
    conn = connect_db()
    create_table(conn)

    data = fetch_data()
    if data:
        save_to_db(conn, data)

    conn.close()
