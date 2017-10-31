#include <Servo.h>
//dummy line
class Window {
public:

Servo servo;
int servoPin;
int pina;
int pinb;
int zeroPin;
int a;
int b;
int sT;

int position =0;
int target=0;
int fakePos=0;
int fakeTarget=0;
int aLast=1;
int bLast=1;
int incriment=0;
String address;
int cmdid=0;
int neutral=101;
int speed=20;
int maxPos=50;
int pTime=5000;

Window (int pin1,int pin2, int pin3, int pin4){
	servoPin = pin1;
	pina = pin2;
	pinb = pin3;
	zeroPin = pin4;
	pinMode(servoPin,OUTPUT);
	pinMode(pina,INPUT_PULLUP);
	pinMode(pinb,INPUT_PULLUP);
	pinMode(zeroPin,INPUT_PULLUP);
	address=String(servoPin)+",";
}

void setPosition (){
	if(target!=position){
		//Serial.println("setpos");
		incriment=0;
		if (target==0){
			calibrate();
		}else if (target<position && target>0){
			//Serial.println("incriment -1");
			incriment=-1;
			servo.attach(servoPin);
		}else if(target>position && target<=maxPos){
			//Serial.println("incriment 1");
			incriment=1;
			servo.attach(servoPin);
		}
		logger.d("newspeed:"+String(neutral+incriment*speed));
		servo.write(neutral+incriment*speed);
		fakePos=position*incriment;
		fakeTarget=target*incriment;
		track();
	}
}

boolean isZero(){
	//Serial.println(String(digitalRead(zeroPin)));
	if(digitalRead(zeroPin)==0){
		Serial.println("is zero");
		return true;
	}else{
		return false;
	}
}

void calibrate(){
	logger.d("calibrate");
	sT=millis();
	servo.attach(servoPin);
	servo.write(neutral-speed);
	while(millis()-sT<9000 && !isZero()){
		delay(5);
	}
	servo.write(neutral);
	servo.detach();
	logger.d("zero set");
	position=0;
}

void obloop(){
	setPosition();
}

void track(){
	logger.d("track");
	logger.d("p"+String(fakeTarget));
	sT=millis();
	while (millis()-sT<=pTime){ 
		a=digitalRead(pina);
		b=digitalRead(pinb); //fakeTarget<fakePos
		if(incriment!=1 && isZero()){
			logger.d("zero reached");
			break;
		}
		if(a!=aLast){
			logger.d(String(a));
			logger.d(String(b));
			if (b==aLast){
				position --;
				fakePos= fakePos-incriment;
			}else{
				position ++;
				fakePos= fakePos+incriment;
			}
			logger.d("position"+String(position));
			logger.d("p"+String(fakePos));
			aLast=a;
			if (fakeTarget<=fakePos){
				servo.write(neutral); //freeze
				servo.detach();
				status();
				logger.d("limit reached");
				break;
			}
		}
		delay(10);
	}
	servo.write(neutral);
	servo.detach();
	logger.d("out");	
}
void process (String t, int val1,int val2, int val3){
	//Serial.print("got new pos");
	if(t.equals("c")){
		target=val2;
		cmdid=val1;
		speed=val3;
	}else if(t.equals("s")){
		maxPos=val1;
		neutral=val2;
		status();
	}
	setPosition();
}



void status (){
	logger.m(address+String(cmdid)+","+String(position));
}
};

