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

    The AutotunePID elements of this program based on the work of 
    AUTHOR: Repetier
    PURPOSE: Repetier-Firmware/extruder.cpp

    HISTORY: Please refer Github History
    
 ****************************************************/

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Set Pitmaster Pin
void set_pitmaster(bool init) {
  
  for (int i = 0; i < PITMASTERSIZE; i++) {
    if (init) {
      bbq[i].setChannel(&ch[0]);
      bbq[i].setPID(&pid[0]);
      bbq[i].setSoll(PITMASTERSETMIN);
      bbq[i].setStatus(PITOFF);
      bbq[i].setResume(true);
      bbq[i].setValue(0);
    }
    
  }

  // PITSUPPLY
  if (sys.hwversion > 1) {
    pinMode(PITSUPPLY, OUTPUT);
    digitalWrite(PITSUPPLY, LOW);
  }
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Control - Pitmaster 12V Supply
  
void pitsupply() {

  if (sys.hwversion > 1) {                // PITSUPPLY nur bei v2

    bool out = false;
    if (bbq[0].getStatus() > PITOFF) {    // PITMASTER 1 aktiv, sonst aus

      switch (bbq[0].getAktor()) {
        case SSR:  out = true; break;               // immer 12V Supply, auch im Akkubetrieb
        case DAMPER:
        case FAN:  
        case SERVO: out = sys.god & (1<<4); break;   // nur falls in der Software aktiviert
        // bei SERVO ist bbq[0] = Servo und bbq[1] = Voltage, hierfür aktivieren  
      }
    }
    sys.supplyout = out;
    digitalWrite(PITSUPPLY, out);       
  
  }
  
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Set Default PID-Settings
void set_pid(byte index) {

  // Name, Nr, Aktor, Kp, Ki, Kd, Kp_a, Ki_a, Kp_a, Ki_min, Ki_max, Switch, DCmin, DCmax, ...
  
  pidsize = 3; //3;
  pid[0] = {"SSR SousVide", 0, 0, 104, 0.2, 0, 20, 0,  0, 0, 95,  0.9, 0,  100};
  pid[1] = {"TITAN 50x50",  1, 1, 3.8, 0.01,   128, 6.2, 0.001, 5, 0, 95,  0.9, 25, 100};
  pid[2] = {"Kamado 50x50", 2, 1, 7.0, 0.019,  630, 6.2, 0.001, 5, 0, 95,  0.9, 25, 100};

  // Monolith Servo 11; 0,008; 0; 15; 0,001; 0
  if (index)
    pid[2] = {"Servo", 2, 2, 12.0, 0.09, 0, 15, 0, 0, 0, 95, 0.9, 20, 80};

}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void disableAllHeater() {
  for (int i=0; i < PITMASTERSIZE; i++)  {
    bbq[i].disableHeater();   
  }
}



