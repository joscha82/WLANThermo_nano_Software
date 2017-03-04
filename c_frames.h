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
    
    HISTORY:
    0.1.00 - 2016-12-30 initial version
    0.2.00 - 2016-12-30 implement ChannelData
    0.2.01 - 2017-01-04 add inactive/active channels and temperature unit
    
 ****************************************************/
 
#define MAXBATTERYBAR 13

byte flash = 0;                       // Flash Battery Symbol in Status Row


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frame while system start 
void drawConnect() {
    
    display.clear();
    display.setColor(WHITE);
    
    // Draw Logo
    display.drawXbm(7, 4, nano_width, nano_height, xbmnano);
    
    display.display();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frame while Loading
void drawLoading() {
  
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    
    display.drawString(10, 49, "LADE-LED BEACHTEN");

    // Lade-Batterie
    display.fillRect(93,21,4,16);   // Draw battery end button
    
    display.fillRect(32,18,17,2);   // Rahmen oben links
    display.fillRect(74,18,18,2);   // Rahmen oben rechts
    
    display.fillRect(32,38,26,2);   // Rahmen unten links
    display.fillRect(66,38,26,2);   // Rahmen unten rechts

    display.fillRect(32,18,2,21);   // Rahmen links
    display.fillRect(90,18,2,21);   // Rahmen rechts
    
    display.fillRect(51,17,21,13);  // Stecker Hauptteil
    display.fillRect(60,30,4,13);   // Stecker Kabel
    display.fillRect(54,7,3,9);     // Stecker Pin
    display.fillRect(66,7,3,9);     // Stecker Pin

    display.display();
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frame while Question
void drawQuestion() {
    
    display.clear();
    display.setColor(WHITE);
    
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);

    bool b0 = true;
    bool b1 = true;
    
    switch (question) {                   // Which Question?

      case CONFIGRESET:
        display.drawString(32,3,"Reset Config?");
        break;

      case HARDWAREALARM:
        display.drawString(35,3,"ALARM! Stop?");
        b1 = false;
        break;
    }

    display.setFont(ArialMT_Plain_16);
    
    if (b1) display.drawString(10,40,"NO");
    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    if (b0) display.drawString(118,40,"YES");
    display.display();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Frame while Question
void drawMenu() {
    
    display.clear();
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);

    // Sandwich
    display.drawLine(3, 3, 13, 3);
    display.drawLine(3, 7, 13, 7);
    display.drawLine(3, 11, 13, 11);

    display.drawString(50,2,"MENU");
    display.drawString(20,18,"Temperature");
    display.drawString(20,33,"Pitmaster");
    display.drawString(20,48,"System");

    display.setColor(INVERSE);
    switch (menu_count) {
      
      case 0:   // Temperature
        display.fillRect(0, 18, 128, 14);
        break;

      case 1:   // Pitmaster
        display.fillRect(0, 33, 128, 14);
        break;

      case 2:   // System
        display.fillRect(0, 48, 128, 14);
        break;
    }
    
    display.setColor(WHITE);
    display.display();
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Status Row

void gBattery(OLEDDisplay *display, OLEDDisplayUiState* state) {

  int battPixel = (BatteryPercentage*MAXBATTERYBAR)/100;  
  flash = !flash; //Toggle flash flag for icon blinking later
  
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(Noto_Sans_8);
  
  if (pitmaster.active)
    display->drawString(33,0, "P  " + String(pitmaster.set,1) + " / " + String(pitmaster.value,0) + "%");
  else  display->drawString(24,0,String(BatteryPercentage)); 
  
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  if (isAP)  display->drawString(128,0,"AP");
  else  {
    //display->drawString(128,0,String(rssi)+" dBm");
    display->fillRect(116,8,2,1); //Draw ground line
    display->fillRect(120,8,2,1); //Draw ground line
    display->fillRect(124,8,2,1); //Draw ground line

    if (rssi > -100) display->fillRect(116,5,2,3); //Draw 1 line
    if (rssi > -85) display->fillRect(120,3,2,5); //Draw 2 line
    if (rssi > -70) display->fillRect(124,1,2,7); //Draw 3 line
  }

  //display->drawString(80,0,String(map(pit_y,0,pit_pause,0,100)) + "%");

  if (!INACTIVESHOW) display->drawString(100,0,"F");
  
  if (flash && BatteryPercentage < 10) {} // nothing for flash effect
  else if (!charge) {
    display->fillRect(18,3,2,4); //Draw battery end button
    display->fillRect(16,8,1,1); //Untere Ecke
    display->drawRect(0,1,16,7); //Draw Outline
    display->setColor(BLACK);
    display->fillRect(4,0,8,10); //Untere Ecke
    display->setColor(WHITE);
    display->drawXbm(4, 0, 8, 10, xbmcharge);
    display->fillRect(2,3,6,4);  // Draw Battery Status
  }
  else {
  display->fillRect(18,3,2,4); //Draw battery end button
  display->fillRect(16,8,1,1); //Untere Ecke
  display->drawRect(0,1,16,7); //Draw Outline
  display->fillRect(2,3,battPixel,4);  // Draw Battery Status
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Main Frames

void drawTemp(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x+19,18+y,20,36,xbmtemp);                            // Symbol
  display->fillRect(x+27,y+43-ch[current_ch].match,4,ch[current_ch].match);   // Current level
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(19+x, 20+y, String(current_ch+1));                // Channel
  display->drawString(114+x, 20+y, ch[current_ch].name);    // Channel Name
  display->setFont(ArialMT_Plain_16);
  if (ch[current_ch].temp!=INACTIVEVALUE) {
    display->drawString(114+x, 36+y, String(ch[current_ch].temp,1)+ " °" + temp_unit); // Channel Temp
  } else display->drawString(114+x, 36+y, "OFF");

  if (pitmaster.active) {
    if (current_ch == pitmaster.channel) {
      display->setFont(ArialMT_Plain_10);
      display->drawString(44+x, 31+y, "P");
      int _cur = ch[current_ch].temp*10;
      int _set = pitmaster.set*10; 
      if (_cur > _set)
        display->drawXbm(x+37,24+y,arrow_height,arrow_width,xbmarrow2); 
      else if (_cur < _set) 
        display->drawXbm(x+37,24+y,arrow_height,arrow_width,xbmarrow1);
      else display->drawXbm(x+37,24+y,arrow_width,arrow_height,xbmarrow);
    }
  }

}

void drawlimito(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)    {
    display->drawXbm(x+19,18+y,20,36,xbmtemp);         // Symbol
    display->fillRect(x+27,y+43-ch[current_ch].match,4,ch[current_ch].match);   // Current level
  }
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(19+x, 20+y, String(current_ch+1));                // Channel
  if (inWork) display->drawString(104+x, 19+y, String(tempor,1)+ " °" + temp_unit);
  else display->drawString(104+x, 19+y, String(ch[current_ch].max,1)+ " °" + temp_unit);  // Upper Limit
  display->drawLine(33+x,25+y,50,25);
}


void drawlimitu(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)    {
  display->drawXbm(x+19,18+y,20,36,xbmtemp);                            // Symbol
  display->fillRect(x+27,y+43-ch[current_ch].match,4,ch[current_ch].match);   // Current level
  }
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(19+x, 20+y, String(current_ch+1));                // Channel
  if (inWork) display->drawString(104+x, 34+y, String(tempor,1)+ " °" + temp_unit);
  else display->drawString(104+x, 34+y, String(ch[current_ch].min,1)+ " °" + temp_unit);  // Lower Limit
  display->drawLine(33+x,39+y,50,39);
}

void drawtyp(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)    {
  display->drawXbm(x+19,18+y,20,36,xbmtemp);                            // Symbol
  display->fillRect(x+27,y+43-ch[current_ch].match,4,ch[current_ch].match);   // Current level
  }
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(19+x, 20+y, String(current_ch+1));                // Channel
  display->drawString(114+x, 20+y, "TYP:");                         
  if (inWork) display->drawString(114+x, 36+y, ttypname[(int) tempor]);
  else display->drawString(114+x, 36+y, ttypname[ch[current_ch].typ]);            // Typ
}

void drawalarm(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  //if (flashinwork) {
    display->drawXbm(x+19,18+y,20,36,xbmtemp);                            // Symbol
    display->fillRect(x+27,y+43-ch[current_ch].match,4,ch[current_ch].match);   // Current level
  //}
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(19+x, 20+y, String(current_ch+1));                // Channel
  display->drawString(114+x, 20+y, "ALARM:");           
  if (flashinwork) {
    if (inWork && tempor) display->drawString(114+x, 36+y, "YES");
    else if (!inWork && ch[current_ch].alarm) display->drawString(114+x, 36+y, "YES");
    else display->drawString(114+x, 36+y, "NO");   // Alarm
  }
}

void drawpit1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork) display->drawXbm(x+21,20+y,pit_width,pit_height,xbmpit);           // Symbol
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "PITMASTER:");           
  if (inWork) display->drawString(114+x, 36+y, pid[(int) tempor].name);
  else display->drawString(114+x, 36+y, pid[pitmaster.typ].name);
}

void drawpit2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)  display->drawXbm(x+21,20+y,pit_width,pit_height,xbmpit);          // Symbol
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "CHANNEL:");           
  if (inWork) display->drawString(114+x, 36+y, String((int)tempor +1));
  else  display->drawString(114+x, 36+y, String(pitmaster.channel+1));
}

void drawpit3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)  display->drawXbm(x+21,20+y,pit_width,pit_height,xbmpit);          // Symbol
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "SET:");           
  if (inWork) display->drawString(114+x, 36+y, String(tempor,1)+ " °" + temp_unit);
  else  display->drawString(114+x, 36+y, String(pitmaster.set,1)+ " °" + temp_unit);
}

void drawpit4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)   display->drawXbm(x+21,20+y,pit_width,pit_height,xbmpit);         // Symbol
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "ACTIVE:");           
  if (inWork && tempor) display->drawString(114+x, 36+y, "YES");
  else if (!inWork && pitmaster.active) display->drawString(114+x, 36+y, "YES");
  else display->drawString(114+x, 36+y, "NO");  
}

void drawsys1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

  display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  
  if (isAP) {
    display->drawString(120, 20, "AP-SSID:");
    display->drawString(120, 36, APNAME);
  }
  else {
    display->drawString(120, 20, "SSID:");
    display->drawString(120, 36, WiFi.SSID());
  }
}

void drawsys2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

  display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(120, 20, "IP:");
  
  if (isAP) display->drawString(120, 36, WiFi.softAPIP().toString());
  else  display->drawString(120, 36, WiFi.localIP().toString());
}

void drawsys3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

  display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(120, 20, "HOST-NAME:");
  
  String hostname = HOSTNAME;
  hostname += String(ESP.getChipId(), HEX);
  display->drawString(120, 36, hostname);
}

void drawsys4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)   display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "UNIT:");
  display->drawString(114+x, 36+y, "°" + temp_unit);
}

void drawsys5(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)   display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(114+x, 20+y, "HW-ALARM:");
  if (inWork && tempor) display->drawString(114+x, 36+y, "YES");
  else if (!inWork && doAlarm) display->drawString(114+x, 36+y, "YES");
  else display->drawString(114+x, 36+y, "NO");
}

void drawsys6(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  
  display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  
  // Draw Version
  display->drawString(114+x, 20+y, "FIRMWARE:");
  display->drawString(114+x,36+y,FIRMWAREVERSION);
}

void drawsys7(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if (flashinwork)   display->drawXbm(x+5,22+y,sys_width,sys_height,xbmsys);
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  
  // Draw Fastmode
  display->drawString(114+x, 20+y, "FASTMODE:");
  if (inWork && tempor) display->drawString(114+x, 36+y, "NO");
  else if (!inWork && INACTIVESHOW) display->drawString(114+x, 36+y, "NO");
  else display->drawString(114+x, 36+y, "YES");
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Initialising Frames

// this array keeps function pointers to all frames
// frames are the single views that slide from right to left
FrameCallback frames[] = { drawTemp, drawlimito, drawlimitu, drawtyp, drawalarm, 
                           drawpit1, drawpit2, drawpit3, drawpit4, 
                           drawsys1, drawsys2, drawsys3, drawsys4, drawsys5, 
                           drawsys6, drawsys7};  // drawFrame3

// how many frames are there?
// int frameCount = 15;           // siehe c_init.h 

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { gBattery };
int overlaysCount = 1;


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Configuration OLEDDisplay

void set_OLED() {
  
  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(30);

  // Customize the active and inactive symbol
  //ui.setActiveSymbol(activeSymbol);
  //ui.setInactiveSymbol(inactiveSymbol);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  //ui.setIndicatorPosition(TOP);

  // Defines where the first frame is located in the bar.
  //ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Add overlays
  ui.setOverlays(overlays, overlaysCount);

  ui.setTimePerFrame(10000);
  ui.setTimePerTransition(300);
  ui.disableAutoTransition();
  ui.disableIndicator();

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  display.clear();
  display.display();

}


