#define FLAME_SENSOR 10

void Flame() {
  int sensorval = digitalRead(FLAME_SENSOR);
  
  Serial.print("Flame Value : "); 
  Serial.println(sensorval);
  if (sensorval == HIGH) 
    Blynk.notify("Fire Warning!!")
}
