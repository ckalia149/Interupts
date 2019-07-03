volatile int state = LOW; //this is the variable that will be changed if an interrupt is detected
int inputPin = 4;       //Polling will check this pin
int i = 0;              //For loop counting variable
void setup()
{
  attachInterrupt(digitalPinToInterrupt(2), blink_interrupt,INPUT_PULLUP); //Interrupt 0 is mapped to pin 2, signal an interrupt on a change to pin 2
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(2, INPUT);
}

void loop()
{
  digitalRead(inputPin);
  // Poll state of pin 4, if it is hight print: "Polling Checked pin 4 found to be HIGH Start/Continue Program"
  if (digitalRead(inputPin)) {
    Serial.println("Polling Checked pin 4 found to be HIGH Start/Continue Program");
  }
  //  Delay for 0.5sec
  delay(500);
Serial.print("state: ");
Serial.println(state);
  if (state == HIGH) {
    for (i = 1; i <= 15; ++i) {
      Serial.print("count ");
      Serial.println(i);
      delay(500);
    }
  } else if (state == LOW) {
    Serial.println("Interrupt Detected stop counting");
  }

}
//   Setup for loop to count from 1 to 15
//     If your interrupt variable (state) is high print 1 to 15 with a 0.5sec delay between prints statements
//     If your interrupt variable (state) is LOW print: "Interrupt Detected stop counting" stop counting and wait for a change in the interrupt variable
//   After you have counted to 15 print: "Check polling" and poll pin 4, if it is hight repeat counting/interrupting.
//  If the polled pin is LOW print: "Polling LOW detected stop program" then wait until polling pin changes
void blink_interrupt()
{
  state = !state; //change the interrupt variable from LOW to HIGH or HIGH to LOW
}
