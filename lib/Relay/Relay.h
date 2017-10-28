class Relay {
public:

int pin;
String stat;
String address;
String cmdid="0";

Relay (int pin1){
	pin = pin1;
	pinMode(pin,OUTPUT);
	digitalWrite(pin,HIGH);
	stat="0";
	address=String(pin)+",";
}

void process (String incoming[]){
	
	cmdid=incoming[1];
	stat=incoming[2];
	if (stat.equals("1")){
		digitalWrite(pin,LOW);
	}else if (stat.equals("0")){
		digitalWrite(pin,HIGH);
	}
	status();
}

void status (){
	logger.m(address+cmdid+","+stat);
}
};
