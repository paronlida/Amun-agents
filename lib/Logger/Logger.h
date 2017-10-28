class Logger{
public:
const int de=1; //debug
const int in=2; //info
const int er=3; //error
const int me=4; //messaging 
int ser=1;
int cli=4;
Logger(int dum){}
	void m(String msg){
		if (cli<=me){
			client.println(msg);
		}
		if (ser<me){
			Serial.println(msg);
		}
	}
	void d(String msg){
		if (cli<=de){
			client.println(msg);
		}
		if (ser<=de){
			Serial.println(msg);
		}
	}
	void set(int ei, int zw){
		cli=ei;
		ser=zw;
	}
};