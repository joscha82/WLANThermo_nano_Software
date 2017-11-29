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

struct myRequest {
  String host;
  String url;
  String method;
  String response;
  AsyncWebServerRequest *request;
};

myRequest myrequest;

static AsyncClient * aClient = NULL;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Check if there is http update
void getRequest() {

  if(aClient) return;                 //client already exists

  aClient = new AsyncClient();
  if(!aClient)  return;               //could not allocate client

  aClient->onError([](void * arg, AsyncClient * client, int error){
    aClient = NULL;
    delete client;
  }, NULL);

  aClient->onConnect([](void * arg, AsyncClient * client){

   aClient->onError(NULL, NULL);

   client->onDisconnect([](void * arg, AsyncClient * c){
    IPRINTPLN("cd:myRequest");    // Disconnect Client
    //Serial.println(myrequest.response);
    //myrequest.request->send(404);
    myrequest.request->send(200, "text/plain", myrequest.response);
    myrequest.response = "";
    aClient = NULL;
    delete c;
   }, NULL);

   client->onData([](void * arg, AsyncClient * c, void * data, size_t len){
    String payload((char*)data);
    myrequest.response += payload; 
    IPRINTPLN("Response ex. Request");
   }, NULL);

   //send the request
   IPRINTPLN("Send ex. Request:");
   String url;
   if (myrequest.method == "POST") url += F("POST ");
   else  url += F("GET ");
   url += myrequest.url;
   url += F(" HTTP/1.1\n");
   url += F("Host: ");
   url += myrequest.host;
   //Serial.println(url);
   url += F("\n\n");
   
   client->write(url.c_str());
    
 }, NULL);

 if(!aClient->connect(myrequest.host.c_str(), 80)){
   //Serial.println("[INFO]\MyRequest Client Connect Fail");
   AsyncClient * client = aClient;
   aClient = NULL;
   delete client;
 }    
}



// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
String serverLog() {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["SN"] = String(ESP.getChipId(), HEX);
  JsonArray& _logs = root.createNestedArray("logs");

  if (log_count > 9) {
    
    for (int i = 0; i < 10; i++) {
      if (mylog[i].modification) {    // nur bei Aenderung wird das Log benutzt
        JsonObject& _log = _logs.createNestedObject();
        _log["time"] = mylog[i].timestamp;
        _log["battery"] = mylog[i].battery;
        _log["pit_set"] = (mylog[i].soll==NULL)?NULL:mylog[i].soll/10.0;
        _log["pit_value"] = mylog[i].pitmaster; 
        _log["ch1"] = (mylog[i].tem[0]==NULL)?999:mylog[i].tem[0]/10.0;
        _log["ch2"] = (mylog[i].tem[1]==NULL)?999:mylog[i].tem[1]/10.0;
        _log["ch3"] = (mylog[i].tem[2]==NULL)?999:mylog[i].tem[2]/10.0;
        _log["ch4"] = (mylog[i].tem[3]==NULL)?999:mylog[i].tem[3]/10.0;
        _log["ch5"] = (mylog[i].tem[4]==NULL)?999:mylog[i].tem[4]/10.0;
        _log["ch6"] = (mylog[i].tem[5]==NULL)?999:mylog[i].tem[5]/10.0;
        _log["ch7"] = (mylog[i].tem[6]==NULL)?999:mylog[i].tem[6]/10.0;
        _log["ch8"] = (mylog[i].tem[7]==NULL)?999:mylog[i].tem[7]/10.0;
      } 
    }
  }
 
  String json;
  root.printTo(json);
  
 /*
 
  String json = "{\"SN\":\"";
  json += String(ESP.getChipId(), HEX);
  json += "\",\"logs\":[";
  
  if (log_count > 9) {
    
    for (int i = 0; i < 10; i++) {
      if (mylog[i].modification) {    // nur bei Aenderung wird das Log benutzt
        if (i > 0) json += ",";
        json += "{\"time\":";
        json += mylog[i].timestamp;
        json += ",\"battery\":";
        json += mylog[i].battery;
        json += ",\"pit_set\":";
        if (mylog[i].soll=!NULL) json += mylog[i].soll/10.0;
        json += ",\"pit_value\":";
        json += mylog[i].pitmaster; 
        for (int j = 0; j < 8; j++) {
          json += ",\"ch";
          json += String(j);
          json += "\":";
          if (mylog[i].tem[j]!=NULL)  json += mylog[i].tem[j]/10.0;
        }
        json += "}";
      } 
    }
  }
  json += "]}";

  */
  return json;
}


static AsyncClient * LogClient = NULL;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 
void sendServerLog() {

  if(LogClient) return;                 //client already exists

  LogClient = new AsyncClient();
  if(!LogClient)  return;               //could not allocate client

  LogClient->onError([](void * arg, AsyncClient * client, int error){
    printClient(SAVELOGSLINK,CLIENTERRROR);
    LogClient = NULL;
    delete client;
  }, NULL);

  LogClient->onConnect([](void * arg, AsyncClient * client){

   LogClient->onError(NULL, NULL);

   client->onDisconnect([](void * arg, AsyncClient * c){
    printClient(SAVELOGSLINK ,DISCONNECT);
    LogClient = NULL;
    delete c;
   }, NULL);

   client->onData([](void * arg, AsyncClient * c, void * data, size_t len){
    String payload((char*)data);
    serverAnswer(payload, len);
   }, NULL);

   //send the request
   printClient(SAVELOGSLINK,SENDTO); 

   String message = serverLog(); 
   String adress = createCommand(POSTMETH,NOPARA,SAVELOGSLINK,NANOSERVER,message.length());
   adress += message;
   client->write(adress.c_str());
   //Serial.println(adress);
      
 }, NULL);

 if(!LogClient->connect(NANOSERVER, 80)){
   printClient(SAVELOGSLINK ,CONNECTFAIL);
   AsyncClient * client = LogClient;
   LogClient = NULL;
   delete client;
 }    
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
String cloudData(bool cloud) {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& system = root.createNestedObject("system");

    system["time"] = String(now());
    system["soc"] = battery.percentage;
    system["charge"] = battery.charge;
    system["rssi"] = wifi.rssi;
    system["unit"] = sys.unit;
    //system["sn"] = String(ESP.getChipId(), HEX);
    if (cloud) {
      system["serial"] = String(ESP.getChipId(), HEX);
      system["api_token"] = iot.CL_token; 
    }

    JsonArray& channel = root.createNestedArray("channel");

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
  
    JsonObject& master = root.createNestedObject("pitmaster");

    master["channel"] = pitmaster.channel+1;
    master["pid"] = pitmaster.pid;
    master["value"] = (int)pitmaster.value;
    master["set"] = pitmaster.set;
    if (pitmaster.active)
      if (autotune.initialized)  master["typ"] = "autotune";
      else if (pitmaster.manual) master["typ"] = "manual";
      else  master["typ"] = "auto";
    else master["typ"] = "off";  

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
    printClient(SAVEDATALINK,CLIENTERRROR);
    LogClient = NULL;
    delete client;
  }, NULL);

  DataClient->onConnect([](void * arg, AsyncClient * client){

   DataClient->onError(NULL, NULL);

   client->onDisconnect([](void * arg, AsyncClient * c){
    printClient(SAVEDATALINK ,DISCONNECT);
    DataClient = NULL;
    delete c;
   }, NULL);

   //send the request
   printClient(SAVEDATALINK,SENDTO);
   String message = cloudData(true);   
   String adress = createCommand(POSTMETH,NOPARA,SAVEDATALINK,CLOUDSERVER,message.length());
   adress += message;

   client->write(adress.c_str());
   //Serial.println(adress);
      
  }, NULL);

  if(!DataClient->connect(CLOUDSERVER, 80)){
   printClient(SAVEDATALINK ,CONNECTFAIL);
   AsyncClient * client = DataClient;
   DataClient = NULL;
   delete client;
  }    
}


String cloudSettings() {

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& _system = root.createNestedObject("system");

    _system["time"] =       String(now());
    _system["ap"] =         sys.apname;
    _system["host"] =       sys.host;
    _system["language"] =   sys.language;
    _system["unit"] =       sys.unit;
    _system["hwalarm"] =    sys.hwalarm;
    _system["fastmode"] =   sys.fastmode;
    _system["version"] =    FIRMWAREVERSION;
    _system["getupdate"] =  sys.getupdate;
    _system["autoupd"] =    sys.autoupdate;
    _system["hwversion"] =  String("V")+String(sys.hwversion);
  
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
    if (sys.damper) _aktor.add("DAMPER"); 

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
    //_iot["MSGservice"] = iot.TG_serv;
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
    
    request->send(200,"","totalBytes:" +String(fs_info.totalBytes) + "\n"
      +"usedBytes: " + String(fs_info.usedBytes)+ "\n"
      +"heap: "      + String(ESP.getFreeHeap()) + "\n"
      +"sn: "        + String(ESP.getChipId(), HEX) + "\n"
      +"batlimit: "+String(battery.min) + " | " + String(battery.max) + "\n"
      +"bat: "       + String(battery.voltage) + "\n"
      +"batcor: " +String(battery.correction) + "\n"
      //+"moniVol: "   + String(batteryMonitor.getVCell()) + "\n"
      //+"moniVol2: "  + String(batteryMonitor.getVoltage()) + "\n"
      //+"moniSOC: "   + String(batteryMonitor.getSoC()) + "\n"
      +"ssid: "     + ssidstr + "\n"
      +"wifimode: " + String(WiFi.getMode()) + "\n"
      +"mac:" + String(getMacAddress())
      );
  });

  server.on("/god",[](AsyncWebServerRequest *request){
    sys.god =!sys.god;
    setconfig(eSYSTEM,{});
    if (sys.god) request->send(200, "text/plain", "GodMode aktiviert.");
    else request->send(200, "text/plain", "GodMode deaktiviert.");
  });

  server.on("/clearplot",[](AsyncWebServerRequest *request){
    log_count = 0; //TEST
    request->send(200, "text/plain", "true");
  });

  server.on("/v2",[](AsyncWebServerRequest *request){
    sys.hwversion = 2;
    setconfig(eSYSTEM,{});
    request->send(200, "text/plain", "v2");
  });

  server.on("/pitsupply",[](AsyncWebServerRequest *request){
    if (sys.hwversion > 1 && !sys.pitsupply) {
      sys.pitsupply = true;
      request->send(200, "text/plain", "aktiviert");
    } else {
      sys.pitsupply = false;
      request->send(200, "text/plain", "deaktiviert");
    }
  });

  server.on("/pitpair",[](AsyncWebServerRequest *request){
    pitmaster.pair = true;
    request->send(200, "text/plain", "Pitmaster-Kopplung aktiviert");
  });

  server.on("/damper",[](AsyncWebServerRequest *request){
    pitmaster.pair = false;  //?
    sys.damper = true;
    set_pid(1);
    setconfig(ePIT,{});
    request->send(200, "text/plain", "Aktorik erweitert");
  });

  server.on("/servo",[](AsyncWebServerRequest *request){
    set_pid(1);
    setconfig(ePIT,{});
    request->send(200, "text/plain", "Add pitmaster config");
  });

  server.on("/typk",[](AsyncWebServerRequest *request){
    if (sys.hwversion == 1 && !sys.typk) {
      sys.typk = true;
      set_sensor();
      request->send(200, "text/plain", "Typ K aktiviert");
    } else {
      sys.typk = false;
      request->send(200, "text/plain", "Typ K deaktiviert");
    }
    setconfig(eSYSTEM,{});  // Speichern
  });
   
  server.on("/startlog",[](AsyncWebServerRequest *request){
    chart.on = true;
    request->send(200, "text/plain", "true");
  });

  server.on("/restart",[](AsyncWebServerRequest *request){
    sys.restartnow = true;
    request->send(200, "text/plain", "Restart");
  });

  server.on("/ampere",[](AsyncWebServerRequest *request){
    ch[5].typ = 11;
    setconfig(eCHANNEL,{});
    request->send(200, "text/plain", "Strommessung an Kanal 6");
  });

  server.on("/ohm",[](AsyncWebServerRequest *request){
    ch[0].typ = 12;
    setconfig(eCHANNEL,{});
    request->send(200, "text/plain", "Widerstandsmessung an Kanal 1");
  });

  server.on("/newtoken",[](AsyncWebServerRequest *request){
    ESP.wdtDisable(); 
    iot.CL_token = newToken();
    setconfig(eTHING,{});
    lastUpdateCloud = 0; // Daten senden forcieren
    ESP.wdtEnable(10);
    request->send(200, "text/plain", iot.CL_token);
  });
  

  server.on("/setDC",[](AsyncWebServerRequest *request) { 
      if(request->hasParam("aktor")&&request->hasParam("dc")&&request->hasParam("val")){
        ESP.wdtDisable(); 
        bool dc = request->getParam("dc")->value().toInt();
        byte aktor = request->getParam("aktor")->value().toInt();
        int val = request->getParam("val")->value().toInt();
        DC_control(dc, aktor, val);
        IPRINTP("DC-Test: ");
        DPRINTLN(val);
        ESP.wdtEnable(10);
        request->send(200, "text/plain", "true");
      } else request->send(200, "text/plain", "false");
  });

  server.on("/getRequest",[](AsyncWebServerRequest *request) { 
      if(request->hasParam("url")&&request->hasParam("method")&&request->hasParam("host")){
        //ESP.wdtDisable(); 
        //Serial.println(ESP.getFreeHeap());
        Serial.println("[REQUEST]\t/getRequest");
        myrequest.url = request->getParam("url")->value();
        myrequest.host = request->getParam("host")->value();
        myrequest.method = request->getParam("method")->value();
        myrequest.request = request;
        getRequest(); 
        //ESP.wdtEnable(10);
      } else request->send(200, "text/plain", "false");
  });

  server.on("/autotune",[](AsyncWebServerRequest *request) { 
      if(request->hasParam("cycle")&&request->hasParam("over")&&request->hasParam("timelimit")){
        ESP.wdtDisable(); 
        long limit = request->getParam("timelimit")->value().toInt();
        int over = request->getParam("over")->value().toInt();
        int cycle = request->getParam("cycle")->value().toInt();
        startautotunePID(cycle, true, over, limit);
        ESP.wdtEnable(10);
        request->send(200, "text/plain", "true");
      } else request->send(200, "text/plain", "false");
  });

  server.on("/setadmin",[](AsyncWebServerRequest *request) { 
      if (request->method() == HTTP_GET) {
        request->send(200, "text/html", "<form method='POST' action='/setadmin'>Neues Password eingeben (max. 10 Zeichen): <input type='text' name='wwwpassword'><br><br><input type='submit' value='Change'></form>");
      } else if (request->method() == HTTP_POST) {
        if(!request->authenticate(sys.www_username, sys.www_password.c_str()))
          return request->requestAuthentication();
        if (request->hasParam("wwwpassword", true)) { 
          String password = request->getParam("wwwpassword", true)->value();
          if (password.length() < 11) {
            sys.www_password = password;
            setconfig(eSYSTEM,{});
            request->send(200, "text/plain", "Neues Password aktiv!");
          }
          else request->send(200, "text/plain", "Password zu lang!");
        }
      } else request->send(500, "text/plain", BAD_PATH);

  });

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

