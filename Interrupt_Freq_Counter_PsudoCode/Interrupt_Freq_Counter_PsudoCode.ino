const int inputPin = 2;        //the pin receiving the input signal to be measured
volatile int edge_counter = 0; //stores the number of incoming edges of the incoming signal (increamented by interrupt)
float counter_freq;            //stores the actual frequency of Timer0, set it at the start of setup()
float period;                  //stores the calculated period of the incoming signal                 //stores the difference in Timer0 counts between two rising edges of the input signal
long duration;
float frequency;               //stores the calculated frequency of the incoming signal

void setup()
{
  pinMode(inputPin, INPUT);
   //TCCR0B |= _BV(CS02); // Set or Clear bit CS02 of register TCCROB, the most signifigant bit of Timer0's prescaler. See page 110 of the datasheet. TCCR0B |= (_BV(CS02) sets CS02 to HIGH, TCCR0B &= ~(_BV(CS02) sets CS02 to LOW.
   //TCCR0B &= ~(_BV(CS01)); // Set or Clear bit CS01 of register TCCROB, Timer0's prescaler. See page 110 of the datasheet. TCCR0B |= (_BV(CS01) sets CS01 to HIGH, TCCR0B &= ~(_BV(CS01) sets CS01 to LOW.
 //  TCCR0B |= _BV(CS00); // Set or Clear bit CS00 of register TCCROB, the least signifigant bit of Timer0's prescaler. See page 110 of the datasheet. TCCR0B |= (_BV(CS00) sets CS00 to HIGH, TCCR0B &= ~(_BV(CS00) sets CS00 to LOW.
   //TCCR0B = TCCR0B & B11111000 | B00000001;
  counter_freq = 16000.0 / 64.0;
  Serial.begin(9600);
  attachInterrupt(0, freq_counter, RISING); // interrupt 0 is mapped to pin 2 on the Uno. Every rising edge of the incoming signal will now trigger an interrrupt
}

void loop()
{
  /*If all the data needed has been collected using your interrupt handler then
    calculate the period of the incoming signal using Timer0's frequency and the number of Timer0 counts that have happen during one period of the incoming signal
    calculate the incoming signals frequency and print it. (put in a delay so you can easily read Serial Monitor)
    reset edge_counter to zero. (Use edge_counter to determine if you want to start collecting data, end collecting data, or have already collected all the data you need)*/
  //  period is  duration/edgecouter
  //  freq is 1/period

  //Serial.print("edge counter ");
  // Serial.println(edge_counter);

  Serial.print("duration ");
  Serial.println(duration);
  period = (float)duration / (float)counter_freq;

  frequency = ((float)1 / period);
  Serial.print("frequency ");
  Serial.println(frequency);

  delay(200);
  if(edge_counter > 20){
  edge_counter = 0;
  }
}

void freq_counter()
{


  if (edge_counter == 0) {
    TCNT0 = 0;
  }
  else if (  edge_counter == 1) {
    duration = TCNT0;
  } else {
  }
  edge_counter++;
  /* If we want to start collecting data (check edge_counter) set Timer0 register, TCNT0, to zero. This allows the most counts to occur before a roll over occurs
    If the value of edge_counter tells you one period of the incoming signal has elapsed then record the number of Timer0 counts (register, TCNT0)
    At each interrup increase edge_counter, which counts how many rising edges have occurred. (remember edge_counter will continue to increase even after one period has been counted)*/
}
