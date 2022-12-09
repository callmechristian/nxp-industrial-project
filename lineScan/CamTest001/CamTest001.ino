// Arduino UNO

int PixelArray[128] ;                 // Pixel array.
int CLK = 12;                            // Set pin as CLK. 8 - 12
int SI  = 13;                            // Set pin as SI. 7 - 13
int i   =  0;                            // For pixel count.
int sensorValue = 0;             // sensor for saturation time.

void setup() {
  pinMode(CLK, OUTPUT);          // Set CLK as output.
  pinMode(SI, OUTPUT);           // Set SI as  output.
  Serial.begin(115200);
  
 digitalWrite(SI, HIGH);
 digitalWrite(CLK, HIGH);
 digitalWrite(SI, LOW);
 digitalWrite(CLK, LOW);
 
 for(i = 0; i < 128; i ++){
   digitalWrite(CLK, HIGH);
   digitalWrite(CLK, LOW);
 }

}


void loop() {
 sensorValue = analogRead(A0);   // Get value for saturation time.

 digitalWrite(SI, HIGH);
 digitalWrite(CLK, HIGH);
 digitalWrite(SI, LOW);
 digitalWrite(CLK, LOW); 
  

  for(i = 0; i < 128; i ++){
    delayMicroseconds(sensorValue);    //  saturation time
    PixelArray[i] = analogRead(A0);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }

  for(i = 0; i < 128; i ++){
    Serial.print(PixelArray[i]);
    Serial.print(",");
  }
  Serial.println(",");
  //delay(500);
  
  
}         // END
