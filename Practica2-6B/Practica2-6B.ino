#include <Keypad.h>
#include <EEPROM.h>

#define passwordAddress 100

#define ledBlue 4
#define ledGreen 3
#define ledRed 2

const byte countRows = 3;
const byte countColumns = 3;

char keys[countRows][countColumns] = {
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'}
};

byte rowsPins[] = {10, 9, 8};
byte columnsPins[] = {7, 6, 5};

Keypad keypad = Keypad(makeKeymap(keys), rowsPins, columnsPins, countRows, countColumns);

char key;
char code[5];
int currentposition = 0;
int invalidcount = 0;

char addPassword[5] = "1234";
char password[5];

void setup() {
     //ubicacion de la eeprom, valor a guardar
  //EEPROM.put(passwordAddress, addPassword); 
  
  //ubicacion de la eeprom, se obtiene valor y se guarda en la variable password
  EEPROM.get(passwordAddress, password);


  Serial.begin(9600);
  
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  digitalWrite(ledBlue, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);

}

void loop() {

  key = keypad.getKey();

  if (key) {

    code[currentposition] = key;
    currentposition++;

    digitalWrite(ledBlue, HIGH);
    delay(250);
    digitalWrite(ledBlue, LOW);

    if (currentposition == 4)
    {
      if (!strcmp(code, password))
      {
        digitalWrite(ledGreen, HIGH);
        delay(1000);
        digitalWrite(ledGreen, LOW);

        currentposition = 0;

      }
      else {

        digitalWrite(ledRed, HIGH);
        delay(1000);
        digitalWrite(ledRed, LOW);

        currentposition = 0;
        invalidcount++;
        
      }
    }

    if (invalidcount == 3) {

      delay(500);

      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, HIGH);
      delay(2000);

      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, LOW);

      invalidcount = 0;
    }
  }

}
