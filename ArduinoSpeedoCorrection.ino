//ArduinoSpeedoCorrection by Ben Anderson
//Version 0.2
//
//Based upon 1986 Porsche 944 Turbo Speedometer Calibrator by Tom M'Guinness - http://members.rennlist.com/tom86951/Speedometer%20Calibrator%20Page1.html
//Public Domain
//Arduino Pin 10 supplies modified signal for speedometer
//
//Modified to accept a digital signal on pin 3 rather than a ground based pulse - requires 10K pulldown

const int debounce = 2500; // this may need to reduce for TD5 - there are some scenarios where a signal may only be 2.5ms
const int speedometerPin = 10;
const int sensorPin = 3;
int pulseState = HIGH;
volatile unsigned long currentMicros = 0; // we treat these as volatile because they can be changed by our interrupt
volatile unsigned long previousMicros = 0;
volatile unsigned long currentSpeed = 0;
volatile unsigned long previousSpeed = 0;
volatile unsigned long interval = 0;
volatile unsigned long oneHertz = 0;
unsigned long modInterval = 0;
float calFactor = 1.1;   // decrease to slow down speedometer  (use 1/ratio to get calfactors for speedup)
// calFactor of 1 makes no change to speedometer

void setup()
{
  Serial.begin(115200); //for debug - needs to be a high baud otherwise we delay the actuial signal measurement
  pinMode(speedometerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite (sensorPin, LOW); // pin 10 is pulled low by a 10k resistor.
  attachInterrupt (1, iSr, RISING); // when we detect a pulse call our interrupt code
}

void loop()
{
  noInterrupts();
  modInterval = interval;
  interrupts();
  currentMicros = micros();
  if (currentMicros - previousSpeed < 300000) // slowest moving signal from SLABS should be 454micros peak to peak, so if we are seeing much more than half of this then we must be stationary
  { // 1mph = 2.2hz ~230ms, so anything above this means we are stationary
    if (currentMicros - previousMicros > ((modInterval / 2) / calFactor)) //divided by 2 because modInterval is one whole wavelength, we need to do a high low transition for half the time each of this.
    { previousMicros = currentMicros;
      if (pulseState == LOW) pulseState = HIGH; else pulseState = LOW;
      Serial.println(micros()); //debug out
      digitalWrite(speedometerPin, pulseState); // output our corrected VSS
      oneHertz = currentMicros;
    }
  }

  if (currentMicros - oneHertz > 500000) { // if we are stationary output a 1hz signal
    if (pulseState == LOW) {
      pulseState = HIGH;
    } else {
      pulseState = LOW;
    }
    digitalWrite(speedometerPin, pulseState); // output our one hz VSS
    oneHertz = currentMicros;
  }

}

void iSr()
{
  currentSpeed = micros();
  if (digitalRead(sensorPin) == HIGH)
  {
    if ((currentSpeed - previousSpeed) > debounce)
    {
      interval = currentSpeed - previousSpeed; // work out the length of time our signal stays high
      previousSpeed = currentSpeed;
      //Serial.println(interval);
    }
  }
}
