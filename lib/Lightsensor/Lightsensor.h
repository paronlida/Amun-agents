class Lightsensor{
public:

int current;
int old;
String address="0,0,a";

Lightsensor(int id){
pinMode(A0, INPUT);
}

void sense(){
	int temp=0;
	int i=0;
	while (i<5){
		temp=temp+analogRead(A0);
		delay(10);
		i+=1;
	}
	current=map(temp/5,0,1024,0,1000);
	//Serial.println(current);
	if (abs(current-old)>1){
		old=current;
		send();
		//Serial.println(address+","+String(current));
	}
}

void send(){
	client.println(address+","+String(current));
}
};
