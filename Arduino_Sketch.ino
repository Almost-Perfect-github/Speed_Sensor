/* e3help.in
speed sensor using arduino and labview (VISA)
*/
int speedSensorpin = 2;  // The pin the encoder is connected           
unsigned int rpm;     // rpm reading
volatile byte pulses;  // number of pulses
unsigned long timeold; 
unsigned int pulsePerRotation = 3;

 void irspeed()
 {
    //Update count
      pulses++;    
 }

void setup()
 {
   Serial.begin(9600);
     //Use statusPin to flash along with interrupts
   pinMode(speedSensorpin, INPUT);
   
   //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
   //Triggers on FALLING (change from HIGH to LOW)
   attachInterrupt(0, irspeed, FALLING);
   // Initialize
   pulses = 0;
   rpm = 0;
   timeold = 0;

 }

 void loop()
 {
   if (millis() - timeold >= 1000){  //Uptade every one second
 
  
   detachInterrupt(0);

   rpm = (60 * 1000 / pulsePerRotation)/ (millis() - timeold)* pulses;
   timeold = millis();
   pulses = 0;
   
   //Write it out to serial port
   //Serial.print("RPM = ");
   Serial.println(rpm,DEC);
   //Restart the interrupt processing
   attachInterrupt(0, irspeed, FALLING);
   }
    //Serial.println(rpm,DEC);
  }
