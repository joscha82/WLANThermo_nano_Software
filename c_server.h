 /*************************************************** 
    Copyright (C) 2016  Steffen Ochs

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


// Beispiele:
// https://github.com/spacehuhn/wifi_ducky/blob/master/esp8266_wifi_duck/esp8266_wifi_duck.ino

// WebSocketClient: https://github.com/Links2004/arduinoWebSockets/issues/119

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void deviceObj(JsonObject  &jObj) {
  
  jObj["device"] = "nano";
  jObj["serial"] = String(ESP.getChipId(), HEX);
  jObj["hw_version"] = String("V")+String(sys.hwversion);
  jObj["sw_version"] = FIRMWAREVERSION;
  jObj["api_version"] = SERVERAPIVERSION;
  jObj["language"] = sys.language;
  
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void updateObj(JsonObject  &jObj) {
  
  jObj["available"] = true;
  
}

void alexaObj(JsonObject  &jObj) {
  
  jObj["task"] = "save";    // save or delete
  jObj["token"] = "xxx";
  
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void urlObj(JsonObject  &jObj) {

  for (int i = 0; i < NUMITEMS(serverurl); i++) {
  
    JsonObject& _obj = jObj.createNestedObject(servertyp[i]);
    _obj["host"] =  serverurl[i].host;
    _obj["page"] =  serverurl[i].page;
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void dataObj(JsonObject  &jObj, bool cloud, int red = 0) {

  JsonObject& system = jObj.createNestedObject("system");

  system["time"] = String(now()-(red*5));
  system["soc"] = battery.percentage;
  system["charge"] = battery.charge;
  system["rssi"] = wifi.rssi;
  system["unit"] = sys.unit;
  
  JsonArray& channel = jObj.createNestedArray("channel");

  for (int i = 0; i < CHANNELS; i++) {
    JsonObject& data = channel.createNestedObject();
    data["number"]= i+1;
    data["name"]  = ch[i].name;
    data["typ"]   = ch[i].typ;
    data["temp"]  = limit_float(ch[i].temp, i);
    data["min"]   = ch[i].min;
    data["max"]   = ch[i].max;
    data["alarm"] = ch[i].alarm;
    data["color"] = ch[i].color;
  }

  if (cloud) {
    JsonObject& master = jObj.createNestedObject("pitmaster");

    master["channel"] = bbq[0].getChannel_ID()+1;
    master["pid"] = bbq[0].getPID_ID();
    master["value"] = (int)bbq[0].getValue();
    master["set"] = bbq[0].getSoll();
    switch (bbq[0].getStatus()) {
      case PITOFF:   master["typ"] = "off";    break;
      case DUTYCYCLE: // show manual
      case MANUAL:   master["typ"] = "manual"; break;
      case AUTO:     master["typ"] = "auto";   break;
      case AUTOTUNE: master["typ"] = "autotune"; break;
      case VOLTAGE:  master["typ"] = "supply"; break;
      default: master["typ"] = "off"; break;
    }
  } else { 
    
    JsonArray& master = jObj.createNestedArray("pitmaster");

    for (int i = 0; i < PITMASTERSIZE; i++) {
      JsonObject& ma = master.createNestedObject();
      ma["id"] = i;
      ma["channel"] = bbq[i].getChannel_ID()+1;
      ma["pid"] = bbq[i].getPID_ID();
      ma["io"] = bbq[i].getIO();
      ma["value"] = (int)bbq[i].getValue();
      ma["set"] = bbq[i].getSoll();
      switch (bbq[i].getStatus()) {
        case PITOFF:   ma["typ"] = "off";    break;
        case DUTYCYCLE: // show manual
        case MANUAL:   ma["typ"] = "manual"; break;
        case AUTO:     ma["typ"] = "auto";   break;
        case AUTOTUNE: ma["typ"] = "autotune"; break;
        case VOLTAGE:  ma["typ"] = "supply"; break;
        default:       ma["typ"] = "off"; break;
      } 
      ma["supply"] = sys.supplyout;
    }
  }
    
  if (htu.exist()) {
    JsonObject& _htu = jObj.createNestedObject("htu");
    _htu["temp"] = htu.temp();
    _htu["hum"] = htu.hum();
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void cloudObj(JsonObject  &jObj) {

  jObj["task"] = "save";
  jObj["api_token"] = iot.CL_token; 

  JsonArray& data = jObj.createNestedArray("data");

 #ifdef MEMORYCLOUD
  if (cloudcount > 0) {
    long cur = now();

    for (int i = 0; i < cloudcount; i++) {
      JsonObject& _obj = data.createNestedObject();
      parseLog(_obj, i, (cur-((cloudcount-i)*3)));  
    }

    cloudcount = 0;
  }
  #endif
  
  //for (int i = 0; i < 3; i++) {  
    JsonObject& _obj = data.createNestedObject();
    dataObj(_obj, true); //, 2-i);  // 
  //}

}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
void noteObj(JsonObject  &jObj) {

  jObj["task"] = "Alert";
  jObj["channel"] = 1;
  jObj["message"] = iot.CL_token; 

  JsonArray& services = jObj.createNestedArray("services");

  //for (int i = 0; i < NUMITEMS(serverurl); i++) {
  
    JsonObject& _obj1 = services.createNestedObject();
    _obj1["service"] =  "telegram";
    _obj1["key1"] =  "xxx";
    _obj1["key2"] =  "xxx";

    JsonObject& _obj2 = services.createNestedObject();
    _obj2["service"] =  "pushover";
    _obj2["key1"] =  "xxx";
    _obj2["key2"] =  "xxx";

    JsonObject& _obj3 = services.createNestedObject();
    _obj3["service"] =  "mail";
    _obj3["adress"] =  "xxx";
  
  //}
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
String apiData(byte typ) {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& device = root.createNestedObject("device");
  deviceObj(device);

  switch (typ) {

    case APIUPDATE: {
      JsonObject& update = root.createNestedObject("update");
      updateObj(update);
      
      JsonObject& url = root.createNestedObject("url");
      urlObj(url);
      break;
    }

    case APICLOUD: {
      JsonObject& cloud = root.createNestedObject("cloud");
      cloudObj(cloud);
      break;
    }

    case APINOTE: {
      JsonObject& note = root.createNestedObject("notification");
      noteObj(note);
      break;
    }

    case APIALEXA: {
      JsonObject& alexa = root.createNestedObject("alexa");
      alexaObj(alexa);
      break;
    }
  }
  
  String jsonStr;
  root.printTo(jsonStr);
  
  return jsonStr;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
String cloudData(bool cloud) {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  dataObj(root, cloud);
  
  //JsonObject& api = root.createNestedObject("api");
  //api["version"] = APIVERSION;

  String jsonStr;
  root.printTo(jsonStr);
  
  return jsonStr;
}


static AsyncClient * DataClient = NULL;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
void sendDataCloud() {

  if(DataClient) {
    AsyncClient * client = DataClient;
    DataClient = NULL;
    delete client;
    return;                 //client already exists
  }

  DataClient = new AsyncClient();
  if(!DataClient)  return;               //could not allocate client

  DataClient->onError([](void * arg, AsyncClient * client, int error){
    DPRINTF("[HTTP] GET... failed, error: %s\n", DataClient->errorToString(error));
    printClient(serverurl[CLOUDLINK].page.c_str(),CLIENTERRROR);
    DataClient = NULL;
    delete client;
  }, NULL);

  DataClient->onConnect([](void * arg, AsyncClient * client){

   DataClient->onError(NULL, NULL);

   client->onDisconnect([](void * arg, AsyncClient * c){
    printClient(serverurl[CLOUDLINK].page.c_str() ,DISCONNECT);
    DataClient = NULL;
    delete c;
   }, NULL);

   //send the request
   printClient(serverurl[CLOUDLINK].page.c_str(),SENDTO);
   String message = apiData(APICLOUD);  //cloudData(true);   //
   String adress = createCommand(POSTMETH,NOPARA,serverurl[CLOUDLINK].page.c_str(),serverurl[CLOUDLINK].host.c_str(),message.length());
   adress += message;
   Serial.println(adress); 
   client->write(adress.c_str());
   
      
  }, NULL);

  if(!DataClient->connect(serverurl[CLOUDLINK].host.c_str(), 80)){
   printClient(serverurl[CLOUDLINK].page.c_str() ,CONNECTFAIL);
   AsyncClient * client = DataClient;
   DataClient = NULL;
   delete client;
  }    
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
String cloudSettings() {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& _system = root.createNestedObject("system");

  _system["time"] =       String(now());
  _system["ap"] =         sys.apname;
  _system["host"] =       sys.host;
  _system["language"] =   sys.language;
  _system["unit"] =       sys.unit;
  _system["fastmode"] =   sys.fastmode;
  _system["version"] =    FIRMWAREVERSION;
  _system["getupdate"] =  update.version;
  _system["autoupd"] =    update.autoupdate;
  _system["hwversion"] =  String("V")+String(sys.hwversion);
  //_system["advanced"] =  sys.advanced;
  
  JsonArray& _typ = root.createNestedArray("sensors");
  for (int i = 0; i < SENSORTYPEN; i++) {
    _typ.add(ttypname[i]);
  }

  JsonArray& _pit = root.createNestedArray("pid");
  for (int i = 0; i < pidsize; i++) {
    JsonObject& _pid = _pit.createNestedObject();
    _pid["name"] =    pid[i].name;
    _pid["id"] =      pid[i].id;
    _pid["aktor"] =   pid[i].aktor;
    _pid["Kp"] =      limit_float(pid[i].Kp, -1);
    _pid["Ki"] =      limit_float(pid[i].Ki, -1);
    _pid["Kd"] =      limit_float(pid[i].Kd, -1);
    _pid["Kp_a"] =    limit_float(pid[i].Kp_a, -1);
    _pid["Ki_a"] =    limit_float(pid[i].Ki_a, -1);
    _pid["Kd_a"] =    limit_float(pid[i].Kd_a, -1);
    _pid["DCmmin"] =  pid[i].DCmin;
    _pid["DCmmax"] =  pid[i].DCmax;
  }

  JsonArray& _aktor = root.createNestedArray("aktor");
  _aktor.add("SSR");
  _aktor.add("FAN");
  _aktor.add("SERVO");
  if (sys.god & (1<<2)) _aktor.add("DAMPER"); 

  JsonObject& _iot = root.createNestedObject("iot");
  _iot["TSwrite"] =   iot.TS_writeKey; 
  _iot["TShttp"] =    iot.TS_httpKey;
  _iot["TSuser"] =    iot.TS_userKey;
  _iot["TSchID"] =    iot.TS_chID;
  _iot["TSshow8"] =   iot.TS_show8;
  _iot["TSint"] =     iot.TS_int;
  _iot["TSon"] =      iot.TS_on;
  _iot["PMQhost"] =   iot.P_MQTT_HOST;
  _iot["PMQport"] =   iot.P_MQTT_PORT;
  _iot["PMQuser"] =   iot.P_MQTT_USER;
  _iot["PMQpass"] =   iot.P_MQTT_PASS;
  _iot["PMQqos"] =    iot.P_MQTT_QoS;
  _iot["PMQon"] =     iot.P_MQTT_on;
  _iot["PMQint"] =    iot.P_MQTT_int;
  _iot["TGon"]    =   iot.TG_on;
  _iot["TGtoken"] =   iot.TG_token;
  _iot["TGid"] =      iot.TG_id;
  _iot["CLon"] =      iot.CL_on;
  _iot["CLtoken"] =   iot.CL_token;
  _iot["CLint"] =     iot.CL_int;

  JsonArray& _hw = root.createNestedArray("hardware");
  _hw.add(String("V")+String(1));
  if (sys.hwversion > 1) _hw.add(String("V")+String(2));

  JsonArray& _noteservice = root.createNestedArray("notification");
  _noteservice.add("telegram");
  _noteservice.add("pushover");

  JsonObject& api = root.createNestedObject("api");
  api["version"] = APIVERSION;

  String jsonStr;
  root.printTo(jsonStr);
  
  return jsonStr;
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
void server_setup() {

  MDNS.begin(sys.host.c_str());  // siehe Beispiel: WiFi.hostname(host); WiFi.softAP(host);
    
  server.addHandler(&nanoWebHandler);
  server.addHandler(&bodyWebHandler);
  //server.addHandler(&logHandler);
    
  server.on("/help",HTTP_GET, [](AsyncWebServerRequest *request) {
    request->redirect("https://github.com/WLANThermo-nano/WLANThermo_nano_Software/blob/master/README.md");
  }).setFilter(ON_STA_FILTER);

/*
  server.on("/test",HTTP_POST, [](AsyncWebServerRequest *request) {
    Serial.println("hallo");
    request->redirect("http://api.wlanthermo.de/index1.php");
  }).setFilter(ON_STA_FILTER);
    
      
  server.on("/info",[](AsyncWebServerRequest *request){
    FSInfo fs_info;
    SPIFFS.info(fs_info);
    String ssidstr;
    for (int i = 0; i < wifi.savedlen; i++) {
        ssidstr += " ";
        ssidstr += String(i+1);
        ssidstr += ": "; 
        ssidstr += wifi.savedssid[i];
    }
    
  request->send(200,"","bytes: " + String(fs_info.usedBytes) + " | " + String(fs_info.totalBytes) + "\n"
      +"heap: "      + String(ESP.getFreeHeap()) + "\n"
      +"sn: "        + String(ESP.getChipId(), HEX) + "\n"
      +"batlimit: "+String(battery.min) + " | " + String(battery.max) + "\n"
      +"bat: "       + String(battery.voltage) + " | " + String(battery.sim) + " | " + String(battery.simc) + "\n"
      +"batstat: "  + String(battery.state) + " | " +String(battery.setreference) + "\n"
      +"ssid: "     + ssidstr + "\n"
      +"wifimode: " + String(WiFi.getMode()) + "\n"
      +"mac:" + String(getMacAddress())
      );
  });

  server.on("/restart",[](AsyncWebServerRequest *request){
     sys.restartnow = true;
    request->redirect("/");
    }).setFilter(ON_STA_FILTER);

  server.on("/newtoken",[](AsyncWebServerRequest *request){
    ESP.wdtDisable(); 
    iot.CL_token = newToken();
    setconfig(eTHING,{});
    lastUpdateCloud = 0; // Daten senden forcieren
    ESP.wdtEnable(10);
    request->send(200, TEXTPLAIN, iot.CL_token);
  });
*/

/*
  server.on("/getGOD",[](AsyncWebServerRequest *request){
    request->send(200, TEXTPLAIN, String(sys.god));
  });
  
  server.on("/setGOD",[](AsyncWebServerRequest *request){
    if (request->method() == HTTP_GET) {
      request->send(200, "text/html", "<form method='POST' action='/setGOD'>GOD MODE: <input type='text' name='god'><br><br><input type='submit' value='Speichern'></form>");
    } else if (request->method() == HTTP_POST) {
      if(!request->authenticate(sys.www_username, sys.www_password.c_str()))
        return request->requestAuthentication();
      sys.god = request->getParam("god")->value().toInt();
      // System für Damper aktivieren
      if (sys.god & (1<<3)) {
        sys.hwversion = 2;  // Damper nur mit v2 Konfiguration
        set_pid(1);         // es wird ein Servo gebraucht
        setconfig(ePIT,{});
      }
      if (sys.god & (1<<4) && sys.hwversion == 1) sys.god ^= (1<<4); // nicht bei v1
      setconfig(eSYSTEM,{});
      request->send(200, TEXTPLAIN, TEXTTRUE);
    } else request->send(500, TEXTPLAIN, BAD_PATH);
  });
  */
/*
  server.on("/god",[](AsyncWebServerRequest *request){
    sys.god ^= (1<<0);    // XOR
    setconfig(eSYSTEM,{});
    if (sys.god & (1<<0)) request->send(200, TEXTPLAIN, TEXTON);
    else request->send(200, TEXTPLAIN, TEXTOFF);
  });

  server.on("/nobattery",[](AsyncWebServerRequest *request){
    sys.god ^= (1<<1);    // XOR
    setconfig(eSYSTEM,{});
    if (sys.god & (1<<1)) request->send(200, TEXTPLAIN, TEXTON);
    else request->send(200, TEXTPLAIN, TEXTOFF);
  });

  server.on("/typk",[](AsyncWebServerRequest *request){
    if (sys.hwversion == 1) {
      sys.god ^= (1<<2);    // XOR
      setconfig(eSYSTEM,{});
    }
    if (sys.god & (1<<2)) request->send(200, TEXTPLAIN, TEXTON);
    else request->send(200, TEXTPLAIN, TEXTOFF);
  });

  server.on("/damper",[](AsyncWebServerRequest *request){
    if (request->method() == HTTP_GET) {
      request->send(200, "text/html", "<form method='POST' action='/damper'>Beim Hinzufuegen es Dampers werden die PID-Profile zurueckgesetzt: <br><br><input type='submit' value='Hinzufuegen'></form>");
    } else if (request->method() == HTTP_POST) {
      if(!request->authenticate(sys.www_username, sys.www_password.c_str()))
        return request->requestAuthentication();
      sys.god |= (1<<3);  //OR
      sys.hwversion = 2;  // Damper nur mit v2 Konfiguration
      set_pid(1);         // es wird ein Servo gebraucht
      setconfig(ePIT,{});
      setconfig(eSYSTEM,{});
      request->send(200, TEXTPLAIN, TEXTADD);
    } else request->send(500, TEXTPLAIN, BAD_PATH);
  });

  server.on("/pitsupply",[](AsyncWebServerRequest *request){
    if (sys.hwversion > 1 && !sys.pitsupply) {
      sys.pitsupply = true;
      setconfig(eSYSTEM,{});
      request->send(200, TEXTPLAIN, TEXTON);
    } else {
      sys.pitsupply = false;
      setconfig(eSYSTEM,{});
      request->send(200, TEXTPLAIN, TEXTOFF);
    }
  });

*/  

  server.on("/v2",[](AsyncWebServerRequest *request){
    sys.hwversion = 2;
    setconfig(eSYSTEM,{});
    request->send(200, TEXTPLAIN, "v2");
  });

  server.on("/servo",[](AsyncWebServerRequest *request){
    set_pid(1);
    setconfig(ePIT,{});
    request->send(200, TEXTPLAIN, TEXTADD);
  });

  server.on("/setbattmax",[](AsyncWebServerRequest *request){
    if (request->method() == HTTP_GET) {
      request->send(200, "text/html", "<form method='POST' action='/setbattmax'>Maximale Batteriespannung in mV eingeben: <input type='number' name='battmax'><br><br><input type='submit' value='Speichern'></form>");
    } else if (request->method() == HTTP_POST) {
      if(!request->authenticate(sys.www_username, sys.www_password.c_str()))
        return request->requestAuthentication();
      if (request->hasParam("battmax", true)) { 
        int battmax = request->getParam("battmax", true)->value().toInt(); 
        battery.max = constrain(battmax,BATTMIN, 4200);
        setconfig(eSYSTEM,{});
        request->send(200, TEXTPLAIN, "Gespeichert");
      }
    } else request->send(500, TEXTPLAIN, BAD_PATH);
  });

  /*

  server.on("/stop",[](AsyncWebServerRequest *request){
    disableAllHeater();
    setconfig(ePIT,{});
    request->send(200, TEXTPLAIN, "Stop pitmaster");
  });
   
  server.on("/ampere",[](AsyncWebServerRequest *request){
    ch[5].typ = 11;
    setconfig(eCHANNEL,{});
    request->send(200, TEXTPLAIN, TEXTTRUE);
  });

  server.on("/ohm",[](AsyncWebServerRequest *request){
    ch[0].typ = 12;
    setconfig(eCHANNEL,{});
    request->send(200, TEXTPLAIN, TEXTTRUE);
  });

  server.on("/autotune",[](AsyncWebServerRequest *request) { 
      if(request->hasParam("over")&&request->hasParam("timelimit")){
        ESP.wdtDisable(); 
        long limit = request->getParam("timelimit")->value().toInt();
        int over = request->getParam("over")->value().toInt();
        byte id = 0;  // Pitmaster1
        bbq[id].startautotunePID(over, limit);
        ESP.wdtEnable(10);
        request->send(200, TEXTPLAIN, TEXTTRUE);
      } else request->send(200, TEXTPLAIN, TEXTFALSE);
  });
*/

  // to avoid multiple requests to ESP
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html"); // gibt alles im Ordner frei
    
  // 404 NOT found: called when the url is not defined here
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404);
  });
      
  server.begin();
  IPRINTPLN("HTTP server started");
  MDNS.addService("http", "tcp", 80);
}

