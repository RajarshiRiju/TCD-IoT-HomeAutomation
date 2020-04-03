#define MQ2_SENSOR 33
#define MQ2_DELAY 500

int MQ2() {
  int sensorval = analogRead(MQ2_SENSOR);
  
  Serial.print("MQ2 Value : "); 
  Serial.println(sensorval);
//  if (sensorval > 1300) 
//    lcd.print(0,0,"Gas Level is high");
//  else
//    lcd.clear();
  delay(500);
  return sensorval;
}
