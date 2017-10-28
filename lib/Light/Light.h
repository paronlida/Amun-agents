class Light {
public:
int pin;
int level;
int frequency = 200;
String address;
String cmdid;
int val;


Light (int LightPin){
	pin = LightPin;
	address=String(pin)+",";
	analogWriteRange(100);
	analogWrite(pin,0);
	analogWriteFreq(frequency);
//to change frequency
}

void process (String incoming[]){

	cmdid=incoming[2];
	val=incoming[3].toInt();

	if (incoming[1].equals("c")){		
		if (val>level){
		while (val>level){
			level=level+1;
			analogWrite(pin,level);
			delay(26-(level/4));
		}
		}else if(val<level){
		while (val<level){
			level=level-1;
			analogWrite(pin,level);
			delay(26-(level/4));
		}
	}
	}
	if (incoming[1].equals("s")){
	if (val != frequency){
		frequency =val;
		analogWriteFreq(frequency);
		analogWrite(pin,level);
	}
	}
	status(cmdid);
}

void status (String cmdid){
	logger.m(address+String(cmdid)+","+String(level));
}
};

