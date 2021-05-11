#include<IRremote.h>

#include <Servo.h>
#define pinServ4 9
Servo  serv4;
int motor4 = 0;

#define frente 2
#define re 3
#define receptor 11
float vaolr;
unsigned long int key_value = 0;

IRrecv recIR(receptor);
decode_results resultado;

void setup() {
  Serial.begin(9600);
  pinMode(frente, OUTPUT);
  pinMode(re, OUTPUT);
  recIR.enableIRIn();
  
  serv4.attach(pinServ4);
  serv4.write(45);
}

void loop() {
  if(recIR.decode(&resultado)){
    Serial.print("valor: ");
    Serial.println(resultado.value,HEX);

    serv4.write(motor4);

    if (resultado.value == 0XFFFFFFFF) resultado.value = key_value;

    switch(resultado.value){
      case 0xE0E020DF:
        Serial.println("1");
        break;
      case 0xE0E0A05F:
        Serial.println("2");
        digitalWrite(frente, LOW);
        Serial.println(digitalRead(frente));
        break;
      case 0xE0E0609F:
        Serial.println("3");
        break;
      case 0xE0E010EF:
        Serial.println("4");
      
        for (motor4 = 45; motor4 <= 90; motor4 += 1) {
          serv4.write(motor4);
          delay(5);
        }
      
        break;
      case 0xE0E0906F:
        Serial.println("5");
        digitalWrite(frente, HIGH);
        digitalWrite(re, HIGH);

        if (serv4.read() == 90){
          for (motor4; motor4 >= 45; motor4--) {
            serv4.write(motor4);
            delay(5);
          }
        }
        if (serv4.read() == 0){
          for (motor4; motor4 <= 45; motor4++) {
            serv4.write(motor4);
            delay(5);
          }
        }
        break;
      case 0xE0E050AF:
        Serial.println("6");

        for (motor4 = 45; motor4 >= 0; motor4--) {
          serv4.write(motor4);
          delay(5);
        }
        
        break;      
      case 0xE0E030CF:
        Serial.println("7");
        break;
      case 0xE0E0B04F:
        Serial.println("8");
        digitalWrite(re, LOW);
        break;
      case 0xE0E0708F:
        Serial.println("9");
        break;
    }
    key_value = resultado.value;

    
    recIR.resume();
  }
}
