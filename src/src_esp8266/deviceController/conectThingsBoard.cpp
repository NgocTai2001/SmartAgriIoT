#include "ThingsBoardService.h"

/* ============== OBJECT ================== */
WiFiClient espClient;
ThingsBoard tb(espClient);

/* ============== STATE FLAGS ============= */
bool pumpStateFlag = false;
bool autoModeFlag  = false;

static bool subscribed = false;

/* ============== RPC CALLBACK: MODE ====== */
RPC_Response rpcMode(const RPC_Data &data)
{
  bool state = data;

  autoModeFlag = state;   // 🔥 CỜ ĐỔI Ở ĐÂY

  Serial.println(state
    ? "AUTO MODE => ON"
    : "AUTO MODE => OFF");

  digitalWrite(MODE_LED, state ? HIGH : LOW);
  tb.sendAttributeBool("autoMode", state);

  return RPC_Response("autoMode", state);
}

/* ============== RPC CALLBACK: PUMP ====== */
RPC_Response rpcPump(const RPC_Data &data)
{
  bool state = data;

  pumpStateFlag = state;  // 🔥 CỜ ĐỔI Ở ĐÂY

  Serial.println(state
    ? "PUMP => ON"
    : "PUMP => OFF");

  digitalWrite(PUMP_PIN, state ? HIGH : LOW);
  tb.sendAttributeBool("pumpState", state);

  return RPC_Response("pumpState", state);
}

/* ============== RPC LIST ================ */
static const size_t callbacks_size = 2;

static RPC_Callback callbacks[callbacks_size] = {
  { "getValue_1", rpcMode },
  { "getValue_2", rpcPump }
};

/* ============== INIT ==================== */
void TB_Init()
{
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(MODE_LED, OUTPUT);

  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(MODE_LED, LOW);
}

/* ============== LOOP ==================== */
void TB_Loop()
{
  // WiFi do main lo, ở đây chỉ kiểm tra
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!tb.connected()) {
    subscribed = false;

    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("ThingsBoard connect FAIL");
      delay(500);
      return;
    }

    Serial.println("ThingsBoard connected");
  }

  if (!subscribed) {
    if (tb.RPC_Subscribe(callbacks, callbacks_size)) {
      Serial.println("RPC subscribed");
      subscribed = true;
    }
  }

  tb.loop();
}
