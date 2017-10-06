
/***************************************************
  Copyright (C) 2017  Steffen Ochs, Holger Imbery

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  HISTORY: Please refer Github History

 ****************************************************/

//#define MQTT_DEBUG              // ENABLE SERIAL MQTT DEBUG MESSAGES

#ifdef MQTT_DEBUG
  #define MQPRINT(...)    Serial.print(__VA_ARGS__)
  #define MQPRINTLN(...)  Serial.println(__VA_ARGS__)
  #define MQPRINTP(...)   Serial.print(F(__VA_ARGS__))
  #define MQPRINTPLN(...) Serial.println(F(__VA_ARGS__))
  #define MQPRINTF(...)   Serial.printf(__VA_ARGS__)
  
#else
  #define MQPRINT(...)     //blank line
  #define MQPRINTLN(...)   //blank line 
  #define MQPRINTP(...)    //blank line
  #define MQPRINTPLN(...)  //blank line
  #define MQPRINTF(...)    //blank line
#endif
 
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Start MQTT
void connectToMqtt() {
  if (iot.P_MQTT_on) pmqttClient.connect();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MQTT Handler
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  IPRINTPLN("d:MQTT");
  if (WiFi.isConnected()) connectToMqtt;
}

void onMqttConnect(bool sessionPresent) {
  IPRINTPLN("c:MQTT");
  MQPRINTP("[MQTT]\tSession present: ");
  MQPRINTLN(sessionPresent);
  String adress = F("WLanThermo/");
  adress += sys.host;
  adress += F("/set/#");
  uint16_t packetIdSub = pmqttClient.subscribe(adress.c_str(), 2);
  MQPRINTP("[MQTT]\tSubscribing at QoS 2, packetId: ");
  MQPRINTLN(packetIdSub);
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  MQPRINTPLN("[MQTT]\tSubscribe acknowledged.");
  MQPRINTP("packetId: ");
  MQPRINTLN(packetId);
  MQPRINTP("qos: ");
  MQPRINTLN(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  MQPRINTPLN("[MQTT]\tUnsubscribe acknowledged.");
  MQPRINTP("packetId: ");
  MQPRINTLN(packetId);
}

void onMqttMessage(char* topic, char* datas, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  String topic_prefix = F("WLanThermo/");
  topic_prefix += sys.host;
  topic_prefix += F("/set/");
  int topic_prefix_length = topic_prefix.length();
  String topic_short = String(topic);
  topic_short.remove(0, topic_prefix_length);

  if (topic_short.startsWith("channels")) {

    bodyWebHandler.setChannels((uint8_t*) datas);
  /*
  DynamicJsonBuffer jsonBuffer;
  JsonObject& _cha = jsonBuffer.parseObject((const char*)datas);   
  if (!_cha.success());
  
  int num = _cha["number"];
  if (num > 0) {
    num--;          // Intern beginnt die Zählung bei 0
    String _name = _cha["name"].asString();                  // KANALNAME
    if (_name.length() < 11)  ch[num].name = _name;
    byte _typ = _cha["typ"];                                 // FÜHLERTYP
    if (_typ > -1 && _typ < SENSORTYPEN) ch[num].typ = _typ;  
    float _limit = _cha["min"];                              // LIMITS
    if (_limit > LIMITUNTERGRENZE && _limit < LIMITOBERGRENZE) ch[num].min = _limit;
    _limit = _cha["max"];
    if (_limit > LIMITUNTERGRENZE && _limit < LIMITOBERGRENZE) ch[num].max = _limit;
    ch[num].alarm = _cha["alarm"];                           // ALARM
    ch[num].color = _cha["color"].asString();                // COLOR
  } else ;

  setconfig(eCHANNEL,{});                                      // SPEICHERN
  */
 }  
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Configuration MQTT
void set_pmqtt() {
  pmqttClient.onConnect(onMqttConnect);
  pmqttClient.onDisconnect(onMqttDisconnect);
  pmqttClient.onSubscribe(onMqttSubscribe);
  pmqttClient.onUnsubscribe(onMqttUnsubscribe);
  pmqttClient.onMessage(onMqttMessage);
  pmqttClient.setServer(iot.P_MQTT_HOST.c_str(), iot.P_MQTT_PORT);
  pmqttClient.setCredentials(iot.P_MQTT_USER.c_str(), iot.P_MQTT_PASS.c_str());
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Send data to private MQTT Broker
void sendpmqtt() {

  if (pmqttClient.connected()) {

    unsigned long vorher = millis();
    String prefix = F("WLanThermo/");
    prefix += sys.host;
    prefix += F("/status");
    prefix += F("/data");
    String payload = cloudData();
    pmqttClient.publish(prefix.c_str(), iot.P_MQTT_QoS, false, payload.c_str());
    MQPRINTF("[MQTT]\tp: %ums\r\n", millis() - vorher);   // Published to MQTT Broker

  } else {
    MQPRINTPLN("[MQTT]\tf:");        // not connect to MQTT Broker
    pmqttClient.connect();
  }
}

