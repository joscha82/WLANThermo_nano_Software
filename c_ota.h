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

 /*
 * Example:
 *
 * Check for new update
 * http://update.wlanthermo.de/checkUpdate.php?device="nano"&serial="Serialnummer"&hw_version="v1"&sw_version="currentVersion"
 * ----------------------------------------------------------------------------------------------------------------------------------------
 * Download Firmware-version XYZ
 * http://update.wlanthermo.de/checkUpdate.php?device="nano"serial="Serialnummer"&hw_version="v1"&sw_version="currentVersion"&getFirmware="XYZ"
 * ----------------------------------------------------------------------------------------------------------------------------------------
 * Download Spiffs-version XYZ
 * http://update.wlanthermo.de/checkUpdate.php?device="nano"serial="Serialnummer"&hw_version="v1"&sw_version="currentVersion"&getSpiffs="XYZ"
 * ----------------------------------------------------------------------------------------------------------------------------------------
 */ 

#ifdef OTA

  #include <ArduinoOTA.h>           // OTA

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Configuration OTA
  void set_ota(){

    ArduinoOTA.setHostname((const char *)sys.host.c_str());

    ArduinoOTA.onStart([]() {
      display.clear();
      display.setFont(ArialMT_Plain_10);
      display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 10, "OTA Update");
      display.display();
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      display.drawProgressBar(4, 32, 120, 8, progress / (total / 100) );
      display.display();
    });

    ArduinoOTA.onEnd([]() {
      display.clear();
      display.setFont(ArialMT_Plain_10);
      display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
      display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, "Restart");
      display.display();
    });

    ArduinoOTA.onError([](ota_error_t error) {
	    DPRINTF("Error[%u]: ", error);
	
		  switch (error) {
			  case OTA_AUTH_ERROR:
			    DPRINTPLN("Auth Failed");
				  break;
			  case OTA_BEGIN_ERROR:
				  DPRINTPLN("Connect Failed");
				  break;
			  case OTA_CONNECT_ERROR:
				  DPRINTPLN("Connect Failed");
				  break;
			  case OTA_RECEIVE_ERROR:
				  DPRINTPLN("Receive Failed");
				  break;
			  case OTA_END_ERROR:
				  DPRINTPLN("End Failed");
				  break;
			  default:
				  DPRINTPLN("OTA unknown ERROR");
				  break;
		  }
	  });
  }

#endif

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Do http update
void do_http_update() {

  // UPDATE beendet
  if (update.state == 4){
    question.typ = OTAUPDATE;
    drawQuestion(0);
    update.get = "false";
    update.state = 0;
    setconfig(eSYSTEM,{});  // Speichern
    update.state = -1;        // Neue Suche anstoßen
    IPRINTPLN("u:finish");  // Update finished
    return;
  }
  
  if((wifi.mode == 1)) {                 // nur bei STA
    if (update.get != "false") {

      // UPDATE Adresse
      String adress = "?";
      adress += createParameter(SERIALNUMBER);
      adress += createParameter(DEVICE);
      adress += createParameter(UPDATEVERSION);

      // UPDATE 2x Wiederholen falls schief gelaufen
      if (update.count < 3) update.count++;   // Wiederholung
      else  {
        update.state = 0;
        setconfig(eSYSTEM,{});
        question.typ = OTAUPDATE;
        drawQuestion(0);
        IPRINTPLN("u:cancel");      // Update canceled
        displayblocked = false;
        update.count = 0;
        return;
      }

      // UPDATE spiffs oder firmware
      displayblocked = true;
      t_httpUpdate_return ret;
    
      if (update.state == 1) {
        update.state = 2;  // Nächster Updatestatus
        drawUpdate("Webinterface");
        setconfig(eSYSTEM,{});                                      // SPEICHERN
        IPRINTPLN("u:SPIFFS ...");
        update.spiffsUrl = F("http://");
        update.spiffsUrl += serverurl[SPIFFSLINK].host;
        update.spiffsUrl += serverurl[SPIFFSLINK].page;
        adress = update.spiffsUrl + adress;   //
        Serial.println(adress);
        ret = ESPhttpUpdate.updateSpiffs(adress);

    
      } else if (update.state == 3) {
        update.state = 4;
        drawUpdate("Firmware");
        setconfig(eSYSTEM,{});                                      // SPEICHERN
        IPRINTPLN("u:FW ...");
        update.firmwareUrl = F("http://"); 
        update.firmwareUrl += serverurl[FIRMWARELINK].host;
        update.firmwareUrl += serverurl[FIRMWARELINK].page;
        adress = update.firmwareUrl + adress;  //
        Serial.println(adress);
        ret = ESPhttpUpdate.update(adress);
    
      } 

      // UPDATE Ereigniskontrolle
      switch(ret) {
        case HTTP_UPDATE_FAILED:
          DPRINTF("[HTTP]\tUPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          DPRINTPLN("");
          if (update.state == 2) update.state = 1;  // Spiffs wiederholen
          else  update.state = 3;                 // Firmware wiederholen
          //setconfig(eSYSTEM,{});
          drawUpdate("error");
          break;

        case HTTP_UPDATE_NO_UPDATES:
          DPRINTPLN("[HTTP]\tNO_UPDATES");
          displayblocked = false;
          break;

        case HTTP_UPDATE_OK:
          DPRINTPLN("[HTTP]\tUPDATE_OK");
          if (update.state == 2) ESP.restart();   // falls nach spiffs kein automatischer Restart durchgeführt wird
          break;
      }
    } else {
      IPRINTPLN("u:no");
      update.state = 0;   // Vorgang beenden
    }
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Read time stamp from HTTP Header
void readUTCfromHeader(String payload) {

  int index = payload.indexOf("Date: ");
  if (index > -1) {
            
    char date_string[27];
    for (int i = 0; i < 26; i++) {
      char c = payload[index+i+6];
      date_string[i] = c;
    }

    tmElements_t tmx;
    string_to_tm(&tmx, date_string);
    setTime(makeTime(tmx));

    IPRINTP("UTC: ");
    DPRINTLN(digitalClockDisplay(now()));
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Read time stamp from HTTP Header
void readLocation(String payload, int len) {

  int index = payload.indexOf("Location: ");
  if (index > -1) {
    payload = payload.substring(index+10,len);            // "Location" entfernen     
    payload = payload.substring(0,payload.indexOf("\n")); // Ende des Links
    Serial.println(payload);
            
    index = payload.indexOf("?");       // Eventuelle Anhänge entfernen
    if (index > -1) payload = payload.substring(0,index);
    len = payload.length();
    index = payload.indexOf("://");     // http entfernen
    if (index > -1) payload = payload.substring(index+3,len);
    index = payload.indexOf("/");

    if (index > -1) {
      serverurl[APILINK].host = payload.substring(0,index);
      serverurl[APILINK].page = payload.substring(index,len);
      setconfig(eSERVER,{});   // für Serverlinks
      sys.restartnow = true;
    }
  }
}
/*

// see: https://github.com/me-no-dev/ESPAsyncTCP/issues/18
static AsyncClient * updateClient = NULL;
bool updateClientssl;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Check if there is http update
void check_http_update() {

  if (update.state < 1) {
    if((wifi.mode == 1 && update.autoupdate)) {

      if(updateClient) return;                 //client already exists

      updateClient = new AsyncClient();
      if(!updateClient)  return;               //could not allocate client

      updateClient->onError([](void * arg, AsyncClient * client, int error){
        DPRINTF("[HTTP] GET... failed, error: %s\n", updateClient->errorToString(error));
        updateClient = NULL;
        delete client;
        update.get = "false";
      }, NULL);

      updateClient->onConnect([](void * arg, AsyncClient * client){

        printClient(serverurl[APILINK].page.c_str() ,CLIENTCONNECT);
        updateClientssl = false;
        
        updateClient->onError(NULL, NULL);

        client->onDisconnect([](void * arg, AsyncClient * c){
          printClient(serverurl[APILINK].page.c_str() ,DISCONNECT);
          updateClient = NULL;
          delete c;
        }, NULL);

        client->onData([](void * arg, AsyncClient * c, void * data, size_t len){
          
          String payload((char*)data);
          int index;
          Serial.println(payload);

          if (payload.indexOf("HTTP/1.1") > -1) {
            readUTCfromHeader(payload);
          }
          
          if ((payload.indexOf("200 OK") > -1) || updateClientssl) {       

            if (payload.indexOf("Connection: close") > -1) {
              updateClientssl = true;// SSL Verbindung
              return;
            }
           
            // Update
            if (updateClientssl) {
              index = payload.indexOf("\n");    // Neue Zeile
              payload = payload.substring(index+1,len);
            } else {
              index = payload.indexOf("\r\n\r\n");       // Trennung von Header und Body
              payload = payload.substring(index+7,len);      // Beginn des Body
            }
            
            index = payload.indexOf("\r");                 // Ende Versionsnummer
            payload = payload.substring(0,index);

            DPRINTP("[HTTP]\tGET: ");
            if (payload == "false") {
              DPRINTPLN("Kein Update");
              update.get = payload;
            }
            else if (payload.indexOf("v") == 0) {
              DPRINTLN(payload);
              update.get = payload;
            } else {
              DPRINTPLN("Fehler");
              update.get = "false";
            }
            setconfig(eSYSTEM,{});    // Speichern
            updateClientssl = false;
          }
           
        }, NULL);

        String message = apiData(APIUPDATE);   
        //send the request  //GETMETH,CHECKUPDATE
        String adress = createCommand(POSTMETH,NOPARA,serverurl[APILINK].page.c_str(),serverurl[APILINK].host.c_str(),message.length());
        adress += message;
        client->write(adress.c_str());
        Serial.println(adress);
    
      }, NULL);

      if(!updateClient->connect(serverurl[APIUPDATE].host.c_str(), 80)){
        printClient(serverurl[APILINK].page.c_str() ,CONNECTFAIL);
        AsyncClient * client = updateClient;
        updateClient = NULL;
        delete client;
      }
      
    
    } else update.get = "false";
    if (update.state == -1) update.state = 0;
    // kein Speichern im EE, Zustand -1 ist nur temporär
  } 
}

// muss lediglich umgeschaltet werden

*/

static AsyncClient * apiClient = NULL;
bool apicontent;

// update.autoupdate einarbeiten

void check_api() {

  if (update.state == -1) {  // || update.state == 2
    if((wifi.mode == 1)) {
  
      if(apiClient) return;                 //client already exists

      apiClient = new AsyncClient();
      if(!apiClient)  return;               //could not allocate client

      apiClient->onError([](void * arg, AsyncClient * client, int error){
        DPRINTF("[HTTP] GET... failed, error: %s\n", apiClient->errorToString(error));
        apiClient = NULL;
        delete client;
      }, NULL);

      apiClient->onConnect([](void * arg, AsyncClient * client){

        printClient(serverurl[APILINK].page.c_str() ,CLIENTCONNECT);
        apicontent = false;
        
        apiClient->onError(NULL, NULL);

        client->onDisconnect([](void * arg, AsyncClient * c){
          printClient(serverurl[APILINK].page.c_str() ,DISCONNECT);
          apiClient = NULL;
          delete c;
        }, NULL);

        client->onData([](void * arg, AsyncClient * c, void * data, size_t len){
          
          String payload((char*)data);
          //Serial.println(payload);

          if (payload.indexOf("HTTP/1.1") > -1) {
            readUTCfromHeader(payload);
          }
          
          if ((payload.indexOf("200 OK") > -1) || apicontent) {
            if (!apicontent) {
              apicontent = true;
              return;
            } else {
              apicontent = false;
              bodyWebHandler.setServerURL((uint8_t*)data);          
            }      
          } else if (payload.indexOf("302 Found") > -1) {
            readLocation(payload, len);
          }
           
        }, NULL);

        //send the request
        String message = apiData(APIUPDATE);
        String adress = createCommand(POSTMETH,NOPARA,serverurl[APILINK].page.c_str(),serverurl[APILINK].host.c_str(),message.length());
        adress += message;
        client->write(adress.c_str());
        Serial.println(adress);
    
      }, NULL);

      if(!apiClient->connect(serverurl[APILINK].host.c_str(), 80)){
        printClient(serverurl[APILINK].page.c_str() ,CONNECTFAIL);
        AsyncClient * client = apiClient;
        apiClient = NULL;
        delete client;
      }

    } else update.get = "false";
    
    if (update.state == -1) update.state = 0;
    else if (update.state == 2) update.state = 3;
    // kein Speichern im EE, Zustand -1 ist nur temporär
  } 
}


