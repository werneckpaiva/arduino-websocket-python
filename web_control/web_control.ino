#define LED 2

int ledsTimes[4] = {100, 100, 100, 100};
int ledsCounts[4] = {0, 0, 0, 0};
int ledsState[4] = {HIGH, HIGH, HIGH, HIGH};

void setup() {
  Serial.begin(9600);
  for (int i=0; i<4; i++) {
    pinMode(LED + i, OUTPUT);
  }
  reset();
}

void reset(){
  for (int i=0; i<4; i++) {
    ledsCounts[i]=0;
    ledsState[i]=HIGH;
  }
}

void readValues(){
  String value = "";
  int j=0;
  while (Serial.available() > 0) {
      delay(3);
      char c = Serial.read();
      if (c == ',') {
        ledsTimes[j] = value.toInt();
        value="";
        j++;
      } else {
        value = value + c;
      }
  }
  reset();
}

void printTimes(){
  for (int i=0; i<3; i++) {
    Serial.print(ledsTimes[i]);
    Serial.print(',');
  }
  Serial.println(ledsTimes[3]);
}

void loop() {  
  if (Serial.available() > 0) readValues();
  for (int i=0; i<4; i++) {
    if (ledsCounts[i] == ledsTimes[i]){
      ledsCounts[i] = 0;
      ledsState[i] = (ledsState[i]==HIGH)?LOW:HIGH;
    } else {
      ledsCounts[i] += 10;
    }
    digitalWrite(LED + i, ledsState[i]);    
  }
  delay(20);
}
