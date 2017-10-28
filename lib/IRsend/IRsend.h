class IRsend {
public:

//---------TV---------------------------------------------------------
unsigned int p_h;
unsigned int s_h;
unsigned int p;
unsigned int s_0;
unsigned int s_1;
unsigned int f;
unsigned int nbits;
long lon1;//3024871168;57088 46155
long lon2;                   //1011010001001011 1101111100000000;00000000111110111101001000101101
//57088 45135
IRsend (int IRsendPin){
  IRpin = IRsendPin;
  pinMode(IRpin, OUTPUT);
}

void send(String obj,String code1, String code2){
	switch (obj.toInt()){
		case 1: 
			p_h = 9000; s_h = 4500; p = 550; s_0 = 550; s_1 = 1700; f = 40; nbits = 16; break;
	}
	lon1=atol(code1.c_str());
	lon2=atol(code2.c_str());
	enableIROut(f);
	mark(p_h);
  	space(s_h);
Serial.println(lon1);
	for (int i = 0; i < nbits; i++) {
		if (lon1 & 1) {
			mark(p);
			space(s_1);
			
		}else{
		mark(p);
		space(s_0);

		}
		lon1 >>= 1;
	}
	for (int i = 0; i < nbits; i++) {
		if (lon2 & 1) {
			mark(p);
			space(s_1);
			
		}else{
		mark(p);
		space(s_0);

		}
		lon2 >>= 1;
	}
	mark(p);
	space(0);
}


private:

  int halfPeriodicTime;
  int IRpin;

void mark(int time) {
  // Sends an IR mark for the specified number of microseconds.
  // The mark output is modulated at the PWM frequency.
  long beginning = micros();
  while(micros() - beginning < time){
    digitalWrite(IRpin, HIGH);
    delayMicroseconds(halfPeriodicTime);
    digitalWrite(IRpin, LOW);
    delayMicroseconds(halfPeriodicTime); //38 kHz -> T = 26.31 microsec (periodic time), half of it is 13
  }
}

/* Leave pin off for time (given in microseconds) */
void space(int time) {
  // Sends an IR space for the specified number of microseconds.
  // A space is no output, so the PWM output is disabled.
  digitalWrite(IRpin, LOW);
  if (time > 0) delayMicroseconds(time);
}

void enableIROut(int khz) {
  // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
  halfPeriodicTime = 500/khz; // T = 1/f but we need T/2 in microsecond and f is in kHz
}
};
