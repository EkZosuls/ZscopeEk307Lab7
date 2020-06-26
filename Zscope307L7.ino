/* Zscope307  a very very simple oscilloscope program to 
 *  acquire and display time varying signals with an 
 *  Arduino and computer.
 *  Samples an analog pin and also outputs a sqaure wave at an 
 *  integer fraction of the sample rate.
 *  Run this with the serial plotter or monitor to collect your
 *  data.
 *  
 *  Aleks Zosuls Boston University 2020
 */

bool outState = true; //the state of the digital square wave pin
float DCOffsetNull1 = 0; //tune this to subtract your rail splitter voltage
float DCOffsetNull2 = 2.4; //tune this to subtract your rail splitter voltage
float gain1 = 1;  //software gain, useful for calibration
float gain2 = 2;  //software gain, useful for calibration
int z = 0;  //square wave iterator
int samplePeriodms = 2; //time delay between samples in milliseconds. Note this method
//is not very accurate. Use interrupts for legit sample timing
int squareWaveOut = 8;  // pin that outputs a square wave
int squareHalfCycSamples = 250; //number of analog samples betwen
//square wave transistions
int anaInput1 = 0;  //the analog pin that is the scope input
int anaInput2 = 1;
int ch1Binary;
int ch2Binary;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(squareWaveOut,OUTPUT);
  Serial.println("ch1, ch2");

}

void loop() {

delay(samplePeriodms); //sample time delay. not very accurate at single 
//digit delays

//This is the square wave generator
++z;  //iterate each loop for square transition delay
if(z == squareHalfCycSamples){  //when we reach the max then change state
   outState = !outState; //toggle the state of the variable
  z = 0;    //reset half cycle counter
  digitalWrite(squareWaveOut,outState);
 
  }
// this line reads the ADC
ch1Binary = analogRead(anaInput1);
ch2Binary = analogRead(anaInput2);
// and calibrates to volts and prints to the serial port
Serial.print(gain1*(ch1Binary*0.00488)-DCOffsetNull1);
Serial.print(",");
Serial.println(gain2*(ch2Binary*0.00488)-DCOffsetNull2);
}
