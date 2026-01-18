#ifndef THINGSBOARD_SERVICE_H
#define THINGSBOARD_SERVICE_H

#include <ESP8266WiFi.h>
#include "ThingsBoard.h"

/* ============== THINGSBOARD ============== */
#define TOKEN               "Obpv1Q6a8wRETCFCiycA"
#define THINGSBOARD_SERVER  "mqtt.thingsboard.cloud"

/* ============== GPIO ==================== */
#define PUMP_PIN D1
#define MODE_LED D2

/* ============== OBJECT ================== */
extern WiFiClient espClient;
extern ThingsBoard tb;

/* ============== STATE FLAGS ============= */
extern bool pumpStateFlag;   // trạng thái bơm
extern bool autoModeFlag;    // chế độ auto / manual

/* ============== API ===================== */
void TB_Init();
void TB_Loop();

/* ============== RPC ===================== */
RPC_Response rpcMode(const RPC_Data &data);
RPC_Response rpcPump(const RPC_Data &data);

#endif
