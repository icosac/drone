#define triggerPort 9
#define echoPort 10
#define SEND 12
#define ACTIVATE 11
#define BIT 16

int bin[BIT];


/////////////////////////BUG/////////////////////
//Sometimes it adds 0.01 or subs 0.01. Not big of a deal, but neither the best behaviour. 
void convert(double dist){
	for (int i=0; i<BIT; i++){ //Reset binary
		bin[i]=0;
	}
	dist*=100; 
	long dist_l=dist; //Tronco e converto in long
	Serial.println(dist_l);
	int i=0;
	while(dist_l>1 && i<BIT){
		bin[i]=dist_l%2;
		printf("%i   -    %i\n", dist_l, bin[i]);
		dist_l=(long) (dist_l/2);
		i++;
	}
	if (i<BIT){ //Controlla anche l'ultimo carattere
		if (dist_l==1){
			bin[i]=1;
		}
		else{
			bin[i]=0;
		}
		for (int a=BIT-1; a>=0; a--){
			Serial.print(bin[a]);
		}
		Serial.print("\n");
	}
	else{
		for (int a=0; a<BIT; a++){ //QUESTO SIGNIFICA ERRORE
			bin[a]=0;
		}
	}
}

void send(){
	digitalWrite(ACTIVATE, HIGH); //Setto pin attivo per dire che sto per mandare segnale
	delay(100); //Aspetto 1 millisecondo
	for (int i=0; i<BIT; i++){
		digitalWrite(SEND, (bin[i]==1 ? HIGH : LOW)); //Invio bit
		delay(10);
	}
	digitalWrite(ACTIVATE, LOW); //Chiudo
}

void setup() {
	pinMode(triggerPort, OUTPUT);
	pinMode(echoPort, INPUT);
	pinMode(SEND, OUTPUT);
	pinMode(ACTIVATE, OUTPUT);
	Serial.begin(9600);
	digitalWrite(ACTIVATE, LOW);
}

void loop() {
	//porta bassa l'uscita del trigger
	digitalWrite(triggerPort, LOW);
	//invia un impulso di 10microsec su trigger
	digitalWrite(triggerPort, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPort, LOW);

	double length = pulseIn(echoPort, HIGH);

	double distance = 0.034 * length / 2;

	Serial.print("distance: ");

	//dopo 38ms è fuori dalla portata del sensore
	if( length > 38000 ){
		Serial.println("out of range");
	}
	else{ 
		Serial.print(distance); 
		Serial.println(" cm");
	}

	convert(distance);
	send();

	//Aspetta 1000 millisecondi
	delay(1000);
}