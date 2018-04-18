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

#define PITMASTERMAXVALUE 100   // Maximum (PWM) value, the heater should be set
 
 //#define PM_DEBUG              // ENABLE SERIAL AUTOTUNE DEBUG MESSAGES

#ifdef PM_DEBUG
  #define PMPRINT(...)    Serial.print(__VA_ARGS__)
  #define PMPRINTLN(...)  Serial.println(__VA_ARGS__)
  #define PMPRINTP(...)   Serial.print(F(__VA_ARGS__))
  #define PMPRINTPLN(...) Serial.println(F(__VA_ARGS__))
  #define PMPRINTF(...)   Serial.printf(__VA_ARGS__)
  
#else
  #define PMPRINT(...)     //blank line
  #define PMPRINTLN(...)   //blank line 
  #define PMPRINTP(...)    //blank line
  #define PMPRINTPLN(...)  //blank line
  #define PMPRINTF(...)    //blank line
#endif

 
 class BBQPitmaster {
	 
	private:
	
		byte _id;				// PITMASTER ID
		float _set;             // SET-TEMPERATUR
		byte _active;           // IS PITMASTER ACTIVE (0:PITOFF, 1:MANUAL, 2:AUTO, 3:AUTOTUNE, 4:DUTYCYLCE)
		float _value;           // PITMASTER VALUE IN %
		uint16_t _dcmin;        // PITMASTER DUTY CYCLE LIMIT MIN
		uint16_t _dcmax;        // PITMASTER DUTY CYCLE LIMIT MIN
		byte _io;               // PITMASTER HARDWARE IO
    byte _dio;               // PITMASTER DEFAULT HARDWARE IO
		bool _event = false;            // SSR HIGH EVENT
		uint16_t _msec = 0;         // PITMASTER VALUE IN MILLISEC (SSR) / MICROSEC (SERVO)
		unsigned long _last;    // PITMASTER VALUE TIMER
		uint16_t _pause = 1000;        // PITMASTER PAUSE
		bool _resume;           // Continue after restart 
		long _timer0;           // PITMASTER TIMER VARIABLE (FAN) / (SERVO)
		float _esum = 0;            // PITMASTER I-PART DIFFERENZ SUM
		float _elast = 0;           // PITMASTER D-PART DIFFERENZ LAST
		
		DutyCycle	dutycycle;	// DUTYCYCLE OBJECT
		AutoTune	autotune;	// AUTOTUNE OBJECT
		OpenLid		opl;		// OPENLID OBJECT
		PID			*_pid;		// LINKED PID OBJECT
		ChannelData *_ch;		// LINKED CHANNEL OBJECT

	   
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		static inline float min(float a,float b)  {
			if(a < b) return a;
			return b;
		}

		static inline float max(float a,float b)  {
			if(a < b) return b;
			return a;
		}
		
		float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}
	   
	   
	public:
	
		BBQPitmaster() {}
	
		void open_lid_init() {

			if (_id == 0) opl.detection = true;
			else opl.detection = false;
			opl.detected = false;
			//opl.ref = {0.0, 0.0, 0.0, 0.0, 0.0};
			opl.temp = 0;
			opl.count = 0;
			opl.pause = 300;
			opl.fall = 97;
			opl.rise = 100;
		}

    void activIO() {
     pinMode(_io, OUTPUT);
     //digitalWrite(_dio, LOW);
     analogWrite(_io, LOW);
    }
		
		void setIO(byte _io) {
			this->_io = _io;
      //activIO();
		}

    void setDIO() {
      this->_io = this->_dio;
    }

    byte getIO() {
      return _io;
    }
	
		BBQPitmaster(byte _io, byte _id) {
			this->_dio = _io;                   // Set Default _io
      setDIO();
      activIO();
			this->_id = _id;
			open_lid_init();
			
			_resume = 1;   // später wieder raus
			
			//if (!_resume) _active = PITOFF; 
			//if (_active != MANUAL) _value = 0;
		}
		
		void setValue(float _value) {		// aufruf mit &
			this->_value = _value;			
		}
		
		float getValue() {
			return _value;
		}
		
		void setSoll(float _set) {		// aufruf mit &
			this->_set = _set;			
		}
		
		float getSoll() {
			return _set;
		}
		
		void setStatus(byte _active) {		// aufruf mit &
			this->_active = _active;	
      if (_active == PITOFF) {
        disableHeater();
        setDIO();		
      }
		}
		
		byte getStatus() {
			return _active;
		}
		
		void setChannel(ChannelData *_ch) {		// aufruf mit &
			this->_ch = _ch;			
		}
		
		byte getChannel_ID() {
			return _ch->id;
		}
		
		ChannelData* getChannel() {
			return _ch;
		}
		
		void setPID(PID *_pid) {		// aufruf mit &
			this->_pid = _pid;
		}
		
		byte getPID_ID() {
			return _pid->id;
		}
		
		PID* getPID() {
			return _pid;
		}
		
		void setResume(bool _resume) {		// aufruf mit &
			this->_resume = _resume;			
		}
		
		bool getResume() {
			return _resume;
		}
		
		void setAutotuneStop(byte _stop) {		// aufruf mit &
			autotune.stop = _stop;			
		}
		
		byte getAutotuneStatus() {
			return autotune.run;
		}
		
		void config() {}
			
		
		
		void reset() {
			
			_pid = NULL;
			_ch = NULL;
			_set = PITMASTERSETMIN;
			_active = PITOFF;
			// _resume = false;
			
			_event = false;
			_msec = 0;
			_pause = 1000;
			_esum = 0;
			_elast = 0;
			
		}

    byte getAktor() {

      switch (_active) {
        
        case DUTYCYCLE:
          return dutycycle.aktor;

        case AUTOTUNE:     
        case AUTO:
        case MANUAL:
          return _pid->aktor;

        case VOLTAGE:
          return FAN;
          
        default:    // falls plus wird value vorgegeben
          return NULL;
      }
    }
	
  
		// PID
		float PID_Regler(){ 

		// see: http://rn-wissen.de/wiki/index.php/Regelungstechnik

		float x = _ch->temp;         // IST
		float w = _set;             // SOLL
  
		// PID Parameter
		float kp, ki, kd;
		if (x > (_pid->pswitch * w)) {
			kp = _pid->Kp;
			ki = _pid->Ki;
			kd = _pid->Kd;
		} else {
			kp = _pid->Kp_a;
			ki = _pid->Ki_a;
			kd = _pid->Kd_a;
		}

		int diff;
		float e;

		// Abweichung bestimmen
		switch (_pid->aktor) {
			case SSR:           // SSR
				diff = (w -x)*100;
				e = diff/100.0;
				break;

			default:
				diff = (w -x)*10;
				e = diff/10.0;              // nur Temperaturunterschiede von >0.1°C beachten
		}
    
		                          
		// Proportional-Anteil
		float p_out = kp * e;                     
  
		// Differential-Anteil
		float edif = (e - _elast)/(_pause/1000.0);   
		_elast = e;
		float d_out = kd * edif;                  

		// Integral-Anteil
		// Anteil nur erweitert, falls Begrenzung nicht bereits erreicht
		if ((p_out + d_out) < PITMAX) {
			_esum += e * (_pause/1000.0);             
		}
		// ANTI-WIND-UP (sonst Verzögerung)
		// Limits an Ki anpassen: Ki*limit muss y_limit ergeben können
		if (_esum * ki > _pid->Ki_max) _esum = _pid->Ki_max/ki;
		else if (_esum * ki < _pid->Ki_min) _esum = _pid->Ki_min/ki;
		float i_out = ki * _esum;
                    
		// PID-Regler berechnen
		float y = p_out + i_out + d_out;  
		y = constrain(y,PITMIN,PITMAX);           // Auflösung am Ausgang ist begrenzt            
  
		PMPRINTLN("[PM]\tPID:" + String(y,1) + "\tp:" + String(p_out,1) + "\ti:" + String(i_out,2) + "\td:" + String(d_out,1));
  
		return y;
	}
	
	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Clear PID
	void clear_PID_Regler() {
		// Regler zurücksetzen
		_esum = 0;
		_elast = 0;
	}

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// TURN PITMASTER OFF
	void disableHeater() {
		// Anschlüsse ausschalten

		/*if (_pid->aktor == SSR) { 
			digitalWrite(_io, LOW); // SSR
		} else {
			analogWrite(_io, LOW); // FAN, DAMPER, SERVO
		}*/

    analogWrite(_io, LOW);

		_active = PITOFF;
		_value = 0;
		_event = false;
		_msec = 0;

		clear_PID_Regler();
	}
	
	
	
	
	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// STOP AUTOTUNE
	void stopautotune() {
		autotune.value = 0;
		autotune.run = 0;

		if (autotune.stop == 1) { // sauber beendet
			setconfig(ePIT,{});
			if (autotune.keepup) _active = AUTO;     // Pitmaster in AUTO fortsetzen
			else _active = PITOFF;
		} else _active = PITOFF;
  
		question.typ = TUNE;
		drawQuestion(autotune.stop);
		autotune.stop = 0;
	}
	
	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// START AUTOTUNE
	void startautotunePID(int over, long tlimit)  {
  
		autotune.keepup = false;              // wait for user
		autotune.overtemp = over;             // 40 K
		autotune.timelimit = tlimit;          // 120 min

		autotune.set = _set;     // SET TEMPERTURE
  
		for (int i = 0; i < 3; i++) {         // CLEAR VECTORS
			autotune.temp[i] = 0;
			autotune.time[i] = 0;  
		}
  
		disableHeater();                    // SWITCH OF HEATER
		_active = AUTOTUNE;                     
		autotune.run = 1;                     // AUTOTUNE INITALIZED
  
		question.typ = TUNE;                  // SHOW START ON OLED
		drawQuestion(0);  

		PMPRINTPLN("[AT]\t Start!");
	}
	

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// AUTOTUNE RUN
	float autotunePID() {

		float currentTemp = _ch->temp;
		unsigned long time = millis();

		// Startbedingungen herstellen  
		if (autotune.run == 1) {
			if (autotune.set - currentTemp < 0.1*autotune.set) {   // kleiner als Switch-Grenze
				autotune.value = 0;                                    // Aktor abkühlen
			// Phase A1
			} else  {
				autotune.value = PITMASTERMAXVALUE;                    // Aktor einschalten
				autotune.run = 2;
			}
    
		} else {

			// Phase A2
			// Start Steigung
			if (autotune.set - currentTemp < 0.1*autotune.set && autotune.temp[0] == 0) {
				autotune.temp[0] = currentTemp;
				autotune.time[0] = time;

			// Ende Steigung, Anfang Überschwinger
			} else if (currentTemp > autotune.set) {
				autotune.value = 0; // Pitmaster abschalten
				autotune.temp[1] = currentTemp;
				autotune.temp[2] = currentTemp;
				autotune.time[1] = time;

			// Während Überschwinger
			} else if (autotune.temp[1] > 0 && currentTemp > autotune.temp[2]) {
				autotune.temp[2] = currentTemp;

			// Ende Überschwinger  
			} else if (autotune.temp[1] > 0 && currentTemp < autotune.temp[2]) {
				autotune.time[2] = time;

				// Berechnung    
				uint16_t Xp = (autotune.temp[2] - autotune.temp[1]);
				uint16_t K = 1000 / (1.5 * Xp);                             // Kp = 100% / (1.5 * Xp)
    
				_pid->Kp = constrain(K, 0, 2000)/10.0;     // Kp > 200 ist Unsinn
    
				K = 1000 / (0.1*autotune.set);
				_pid->Kp_a = constrain(K, 0, _pid->Kp*10);
    
				uint16_t a = (autotune.time[1] - autotune.time[0]) / 1000; // Zeit in Sekunden
				a = a / (autotune.temp[1] - autotune.temp[0]); 
				K = _pid->Kp*100 / (Xp * a * 4);           // Ki = Kp / (Xp * s/K * 4)

				_pid->Ki = constrain(K, 0, 100)/100.0;            // Ki > 1 ist Unsinn

				_pid->Kd = 0;
				_pid->Ki_a = 0;
				_pid->Kd_a = 0;

				PMPRINTP("[AT]\tKp_a: ");
				PMPRINT(_pid->Kp_a);
				PMPRINTP(" Ki_a: ");
				PMPRINT(_pid->Ki_a);
				PMPRINTP(" Kd_a: ");
				PMPRINTLN(_pid->Kd_a);
				PMPRINTP("[AT]\tKp: ");
				PMPRINT(_pid->Kp);
				PMPRINTP(" Ki: ");
				PMPRINT(_pid->Ki);
				PMPRINTP(" Kd: ");
				PMPRINTLN(_pid->Kd);

				PMPRINTPLN("[AT]\tFinished!");
				disableHeater();
				autotune.stop = 1;
			}
		}
  
		if (currentTemp > (autotune.set + autotune.overtemp))  {   // FEHLER
			PMPRINTPLN("f:AT OVERTEMP");
			disableHeater();
			autotune.stop = 2;
			return 0;
		}
    
		if ((time - autotune.time[0]) > autotune.timelimit) {   // 20 Minutes
			PMPRINTPLN("f:AT TIMEOUT");
			disableHeater();
			autotune.stop = 3;
			return 0;
		}

		return autotune.value;       
	}

	
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Start Duty Cycle Test
	void DC_start(bool dc, byte aktor, int val) {

		if (_active != DUTYCYCLE) {
			dutycycle.dc = dc;
			dutycycle.aktor = aktor;
			dutycycle.value = val;
			dutycycle.timer = millis();
			
			_last = 0;	// Pitmaster direkt aktivieren

			//if (aktor == SERVO && sys.hwversion > 1) _io = PITMASTER2;  // Servo-Spezial
			// ausgelagert in Webhandler
			
			switch (_active) {
				case PITOFF: dutycycle.saved = PITOFF; break;
				case MANUAL: dutycycle.saved = _value; break;
				case AUTOTUNE: 
					dutycycle.saved = PITOFF; // autotune abbrechen
					autotune.stop = 2;
					break;
				case AUTO: dutycycle.saved = -1; break;
        case VOLTAGE: dutycycle.saved = PITOFF; break;  // ?
			}
			_active = DUTYCYCLE;
		}
	}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Stop Duty Cycle Test
	void DC_stop() {
  
		if (_active == DUTYCYCLE && (millis() - dutycycle.timer > 10000)) {
			if (dutycycle.saved == 0) {           // off
				_active = PITOFF;
			} else if (dutycycle.saved > 0) {
				_value = dutycycle.saved;  // manual
				_active = MANUAL;
			} else _active = AUTO;       // auto
			PMPRINTLN("[DC]\tTest finished");
		}
	}



	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Control - Pitmaster Pause
	void check_pit_pause() {

		int aktor;
		uint16_t dcmin, dcmax;
  
		if (_active == DUTYCYCLE) {
			aktor = dutycycle.aktor;
			dcmin = 0;
			dcmax = 1000;                               // 1. Nachkommastelle
		} else if (_active == VOLTAGE) {
      aktor = FAN;
      dcmin = 0;
      dcmax = 1000; 
		} else {
			aktor = _pid->aktor;
			dcmin = _pid->DCmin*10;    // 1. Nachkommastelle
			dcmax = _pid->DCmax*10;    // 1. Nachkommastelle
		}
   
		

		//int pause;		Warum war hier nicht gleich _pause?
		switch (aktor) {

			case SSR:  
				_pause = 2000;   // 1/2 Hz, Netzsynchron    // myPitmaster-Anpassung
				_dcmin = map(dcmin,0,1000,0,_pause);
				_dcmax = map(dcmax,0,1000,0,_pause);
				break;
			case DAMPER:   
			case FAN:  
				_pause = 1000;   // 1 Hz 
				_dcmin = map(dcmin,0,1000,0,1024);
				_dcmax = map(dcmax,0,1000,0,1024);
				break;   
			case SERVO:  
				_pause = 20;   // 50 Hz
				_dcmin = map(dcmin,0,1000,SERVOPULSMIN,SERVOPULSMAX);
				_dcmax = map(dcmax,0,1000,SERVOPULSMIN,SERVOPULSMAX);
				break;  
      //case SUPPLY:
        //_pause = 1000; 
        //break;
		}

	}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// myPitmaster
	int myPitmaster() {

		// veränderte Taktzeit durch Anpassung der PitmasterPause
		// Puffertemp < Ofentemp und Ofentemp > Grenze
		if (_ch->temp < ch[3].temp && ch[3].temp > _set)        // ch[3] = OFEN
			return 100;
		else
			return 0;
		}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Open Lid Detection
	void open_lid() {

		if (opl.detection && _active == AUTO) {
			opl.ref[0] = opl.ref[1];
			opl.ref[1] = opl.ref[2];
			opl.ref[2] = opl.ref[3];
			opl.ref[3] = opl.ref[4];
			opl.ref[4] = _ch->temp;
    
			float temp_ref = (opl.ref[0] + opl.ref[1] + opl.ref[2]) / 3;

			// erkennen ob Temperatur wieder eingependelt oder Timeout
    
			if (opl.detected) {  // Open Lid Detected
       
				opl.count = opl.count--;
    
				if (opl.count <= 0)  // Timeout
					opl.detected = false;
      
				else if (_ch->temp > (opl.temp * (opl.rise / 100)))    // Lid Closed
					opl.detected = false;
      
			} else if (_ch->temp < (temp_ref * (opl.fall / 100))) {    // Opened lid detected!
				// Wenn Temp innerhalb der letzten beiden Messzyklen den falling Wert unterschreitet
    
				opl.detected = true;
				opl.temp = opl.ref[0];  // war bsiher pit_now, das ist aber schon zu niedrig                    
				opl.count = opl.pause / (INTERVALSENSOR/1000);
			}	
    
		} else  {
			opl.detected = false;
		}
	}


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// Control - Manuell PWM
	void run() {

		// Stop Autotune
		if (autotune.stop > 0) stopautotune();

		// Stop Duty Cylce Test
		DC_stop();
  
		// ESP PWM funktioniert nur bis 10 Hz Trägerfrequenz stabil, daher eigene Taktung
		if (_active > 0) {

			// Check Pitmaster Pause
			check_pit_pause();
  
			// SSR: Ende eines HIGH-Intervalls, wird durch pit_event nur einmal pro Intervall durchlaufen
			if ((millis() - _last > _msec) && _event) {
				digitalWrite(_io, LOW);
				_event = false;
			}

			// neuen Stellwert bestimmen und ggf HIGH-Intervall einleiten
			if (millis() - _last > _pause) {
      
				_last = millis();
				byte aktor;

				// PITMASTER TYP
				switch (_active) {

					case DUTYCYCLE:
						aktor = dutycycle.aktor;
						// Startanlauf: bei Servo beide male zuerst in die Mitte, bei Fan nur unten
						if ((millis() - dutycycle.timer < 1000) && ((aktor == FAN && !dutycycle.dc) || aktor == SERVO)) {
							_value = 50;
						} else _value = dutycycle.value/10.0;
						_timer0 = 0;     // Überbrückung Anlauf-Prozess, siehe FAN
						break;

					case AUTOTUNE:
						aktor = _pid->aktor;
						_value = autotunePID();
						break;

					case AUTO:
						aktor = _pid->aktor;
						if (!opl.detected || aktor == SSR)
							_value = PID_Regler();      //myPitmaster();
						else _value = 0; 
						break;

					case MANUAL:    // falls manual wird value vorgegeben
						aktor = _pid->aktor;
						break;
						
					case VOLTAGE:    // falls plus wird value vorgegeben
						aktor = FAN;
						break;
				}
				//Serial.println(aktor);
				// PITMASTER AKTOR
				switch (aktor) {

					case SSR:  
            // PITMASTER 1 = SSR
						_msec = map(_value,0,100,_dcmin,_dcmax); 
						if (_msec > 0) digitalWrite(_io, HIGH);
						if (_msec < _pause) _event = true;  // außer bei 100%
						break;

					case DAMPER:
						// PITMASTER 1 = FAN
						// PITMASTER 2 = SERVO 
					case FAN:
            // PITMASTER 1 = FAN  
						if (_value == 0) {   
							analogWrite(_io,0);  // bei 0 soll der Lüfter auch stehen
							_timer0 = millis();  
						} else {
						// Anlaufhilfe: ein Zyklus auf 30% wenn von 0% kommend
							if (millis() - _timer0 < _pause*2 && _value < 30) { 
								analogWrite(_io,map(30,0,100,_dcmin,_dcmax));   // BOOST
							} else {
								analogWrite(_io,map(_value,0,100,_dcmin,_dcmax));
               //Serial.print(_io); Serial.print(":");
               //Serial.println(map(_value,0,100,_dcmin,_dcmax));
							}
						}
						break;
        
					case SERVO:   // Warnhinweis fürs Umschalten
            // PITMASTER 1 = VOLTAGE
            // PITMASTER 2 = SERVO  (gedrehte Pitmaster)
						_msec = mapfloat(_value,0,100,_dcmin,_dcmax);
						//Serial.println(_msec);
						_timer0 = micros();
						noInterrupts();
						digitalWrite(_io, HIGH);
						while (micros() - _timer0 < _msec) {}  //delayMicroseconds() ist zu ungenau
						digitalWrite(_io, LOW);
						interrupts();
						break;  

					//case SUPPLY:  
					//	analogWrite(_io,map(_value,0,100,0,1024));   // KONSTANTE VOLTAGE
					//	break;
				}
			}
		} else {    
			disableHeater();    // TURN OFF PITMASTER
			open_lid_init();    // TURN OFF OPEN LID DETECTION
		}
  
	}
  
 };
 


 
 
 
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
