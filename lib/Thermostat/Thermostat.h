class Thermostat {
public:

int pin1;
int pin2
String stat;
String address;
String cmdid="0";

Relay (int pin_1, int pin_2){
	pin1 = pin_1;
	pin2 = pin_2;
	pinMode(pin1,OUTPUT);
	pinMode(pin1,OUTPUT);
	digitalWrite(pin,HIGH);
	stat="0";
	address=String(pin)+",";
}
	
void turnon(){
	for (i=0, i<30, i++){
		digitalWrite(pin1,LOW);
		delay(10);
		digitalWrite(pin2,LOW);
		delay(10);
		digitalWrite(pin1,High);
		delay(10);
		digitalWrite(pin2,High);
	}
}
void turnoff(){
	for (i=0, i<30, i++){
		digitalWrite(pin2,LOW);
		delay(10);
		digitalWrite(pin1,LOW);
		delay(10);
		digitalWrite(pin2,High);
		delay(10);
		digitalWrite(pin1,High);
	}
}
	
void process (String incoming[]){
	
	cmdid=incoming[1];
	stat=incoming[2];
	if (stat.equals("1")){
		turnon();
	}else if (stat.equals("0")){
		turnoff();
	}
	status();
}

void status (){
	logger.m(address+cmdid+","+stat);
}
};
