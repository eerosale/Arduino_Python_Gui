
/* 
0 DESCRIPTION
 ====================
 Simple example of the Bounce library that switches the debug LED when a button is pressed.
 */
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring

/*This program waits for a momentary or limit switch to be hit which then 
enabled seeed studio relay shield to switch motor direction. Schematic for seeed studio
relay shield can be found at: http://i.imgur.com/RMCVR0u.jpg , the code was originally written
for an arduino mega however had to be switched to an arduino uno last minute hence the 
commented out code*/


#include <Bounce2.h>

#define BUTTON_PIN A4 //one momentary switch to pin 4
#define BUTTON_PINT A5 //another momentary switch to pin 5


int val; //value from GUI
byte mode = 0; //this is a state machine
unsigned char relayPin[4] = {4,5,6,7};
// Instantiate a Bounce object
Bounce debouncer = Bounce(); 
Bounce debouncer2 = Bounce();
/*int PIR = A13; //used a pir sensor from radioshack
int led = 50; //this is for a buzzer to indicate when a cycle finishes
int photo_res = A12; //for a photo resistor, didn't do anything yet
*/
void setup() {

    int i;
  for(i = 0; i < 4; i++)
  {
    pinMode(relayPin[i],OUTPUT);
  }
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(BUTTON_PINT, INPUT_PULLUP);
  /*pinMode(PIR, INPUT);
  pinMode(led, OUTPUT);
  pinMode(photo_res, INPUT_PULLUP);
  digitalWrite(PIR, LOW);
  digitalWrite(photo_res, LOW);*/
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer2.attach(BUTTON_PINT);
  debouncer.interval(5); // interval in ms
  
  Serial.begin(9600);
}
void loop() {

if (Serial.available()) 
 { // If data is available to read,
      val = Serial.read(); 
  switch (val)
  {
     case '0':         
          regular_cycle();
          break;
     case '1':
          super_cycle();
          break;
     /*case '2':
          dance_with_me();
         
          break;
     case '3':
          pos_me();
          break;
          */
  }
 }
}

int regular_cycle()
{   
    delay(500);
    //digitalWrite(led, LOW);
    byte mode = 0;
    digitalWrite(relayPin[1],LOW);
    digitalWrite(relayPin[2], LOW);
    digitalWrite(relayPin[3], LOW);
      
     delay(1000);
     digitalWrite(relayPin[1], HIGH);
     
  while(mode!=5){  
   debouncer.update();
  debouncer2.update(); 
  switch( mode )
 {
   case 0://------------------------ I'm off and in restmode
     
     if ( debouncer.read() == HIGH )
     { // switch relay ON
        digitalWrite(relayPin[1], LOW);
        digitalWrite(relayPin[2],HIGH);
        digitalWrite(relayPin[3], HIGH);
 
        delay(1000);
        digitalWrite(relayPin[1], HIGH);
       mode = 1;
     }
     break;
   case 1://------------------------ I'm in ON mode, w8 4 keyrelease
     if ( debouncer.read() == LOW )
      mode = 2;
     break;
   case 2://------------------------ I'm ON and in restmode
     if ( debouncer2.read() == HIGH)
     { // switch relay OFF
     
    // delay(500);
          digitalWrite(relayPin[1], LOW);
          digitalWrite(relayPin[2],LOW);
          digitalWrite(relayPin[3],LOW);
  
          delay(1000);
   digitalWrite(relayPin[1], HIGH);
  // delay(500);
       mode = 3;
     }
     break;
  case 3://------------------------ I'm in OFF mode, w8 4 keyrelease
    if ( debouncer2.read() == LOW)
    
      mode = 4;  
     break;
     
   case 4:
   if (debouncer.read() == HIGH)
   
   digitalWrite(relayPin[1], LOW);
    //digitalWrite(led, HIGH);
   //delay(500);
   //digitalWrite(led, LOW);
   mode = 5;
   break;
  
   
 }
}
}

int super_cycle()
{
    byte mode = 0;
    int count = 0;
    
    digitalWrite(relayPin[1],LOW);
    digitalWrite(relayPin[2], LOW);
    digitalWrite(relayPin[3], LOW);
      
     delay(1000);
     digitalWrite(relayPin[1], HIGH);
     
  while(count!=3){  
   debouncer.update();
  debouncer2.update(); 
  switch( mode )
 {
   case 0://------------------------ I'm off and in restmode
     
     if ( debouncer.read() == HIGH)
     { // switch relay ON
        digitalWrite(relayPin[1], LOW);
        digitalWrite(relayPin[2],HIGH);
        digitalWrite(relayPin[3], HIGH);
 
        delay(1000);
        digitalWrite(relayPin[1], HIGH);
       mode = 1;
     }
     break;
   case 1://------------------------ I'm in ON mode, w8 4 keyrelease
     if ( debouncer.read() == LOW )
      mode = 2;
     break;
   case 2://------------------------ I'm ON and in restmode
     if ( debouncer2.read() == HIGH)
     { // switch relay OFF
     
    // delay(500);
          digitalWrite(relayPin[1], LOW);
          digitalWrite(relayPin[2],LOW);
          digitalWrite(relayPin[3],LOW);
  
          delay(1000);
   digitalWrite(relayPin[1], HIGH);
  // delay(500);
       mode = 3;
       count = count + 1;
     }
     break;
  case 3://------------------------ I'm in OFF mode, w8 4 keyrelease
    if ( debouncer2.read() == LOW && count == 1){
    
      mode = 0;
     
 }
     else if (debouncer2.read() == LOW && count == 2)
     
     mode = 4;
     break;
     
   case 4:
   if (debouncer.read() == HIGH)
   {
   digitalWrite(relayPin[1], LOW);
      //digitalWrite(led, HIGH);
      //delay(500);
      //digitalWrite(led, LOW);
   count = count + 1;
   }
   break;
   
 }
}
}

/*int dance_with_me()
{

  int count = 0;
 while(count != 1)
{ 
  if(digitalRead(PIR) == HIGH)
  {
  digitalWrite(led, HIGH);
  regular_cycle();
  count = 1;
  }
  else if(digitalRead(PIR) == LOW)
  {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);

  }
  }
}

int pos_me()
  {//byte flag = 0;
  int count = 0;
  
 // digitalWrite(led, LOW);
 while(count != 1)
{ 
  if(analogRead(photo_res) > 700)
  {
 
  regular_cycle();
count = 1;
  }
  else if(analogRead(photo_res) < 700)
  {
  digitalWrite(relayPin[1], LOW);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  
  }
  }
}

*/


