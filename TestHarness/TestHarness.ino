// Simple waveform generator based upon blink

int interval = 2; // this is the time in milliseconds that we want our signal to be high and then low
                  // a value of 2 gives a waveform repeat of 4ms or 250hz
                  // TD5 Land Rover SLABS output is baseline 1hz when stationary, and vehicle speed * 2.2 in hz (8000 pulses per miles)

void setup() {
  // initialize digital pin 12 as an output.
  pinMode(12, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(12, HIGH);   // set the output high
  delay(interval);                       // wait for a second
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  delay(interval);                       // wait for a second
}
