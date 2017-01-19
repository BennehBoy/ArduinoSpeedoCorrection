//1986 Porsche 944 Turbo Speedometer Calibrator
//Public Domain
//raw 944 transmission sensor signal must be processed by external schmitt trigger
//Schmitt trigger should bypass filer and pull-up resistor
//Use LM2940-10 with decoupling caps per datasheet to power Arduino in automotive setting
//Arduino Pin 10 supplies modified signal for speedometer
//
//Modified to accept a digital signal on pin 3 rather than a ground based pulse - requires 10K pulldown
 
const int debounce = 2500;
const int speedometerPin = 10;                    
const int sensorPin = 3;                                     
int pulseState = HIGH;                                        
volatile unsigned long currentMicros = 0; 
volatile unsigned long previousMicros= 0;  
volatile unsigned long currentSpeed = 0;  
volatile unsigned long previousSpeed = 0;
volatile unsigned long interval = 0;                 
unsigned long modInterval = 0;                
float calFactor = 1.1;   // decrease to slow down speedometer                           
                                     // calFactor of 1 makes no change to speedometer
 
void setup()
{
  Serial.begin(115200);
pinMode (13, OUTPUT);                        
pinMode(speedometerPin, OUTPUT);    
pinMode(sensorPin, INPUT);                 
digitalWrite (sensorPin, LOW);             
attachInterrupt (1, iSr, RISING);        
}
 
void loop()
{
  noInterrupts();                                                 
  modInterval=interval;                                    
  interrupts();                                                      
  currentMicros = micros();                             
  if (currentMicros-previousSpeed<1000000) 
  {
   if (currentMicros - previousMicros>((modInterval/2)/calFactor))          
       { previousMicros = currentMicros;                                                    
        if (pulseState == LOW) pulseState = HIGH; else pulseState = LOW;
        digitalWrite(13, pulseState);         //to blink onboard LED  
        Serial.println(micros());                                                        
        digitalWrite(speedometerPin, pulseState);
        }                                  
   }
}
 
void iSr()
{
  currentSpeed=micros();                   
  if (digitalRead(sensorPin)==HIGH) 
     {
        if ((currentSpeed - previousSpeed) > debounce)  
           {
            interval = currentSpeed - previousSpeed;        
            previousSpeed=currentSpeed;
            //Serial.println(interval);                        
           }
      }
}
