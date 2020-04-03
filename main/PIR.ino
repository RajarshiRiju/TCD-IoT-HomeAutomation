#define PIR_SENSOR 14
#define IR_SENSOR 10

WidgetLED led1(V9);

int PIR() {
  int sensorval = digitalRead(PIR_SENSOR);
  int IRval = digitalRead(IR_SENSOR);
  Serial.print("PIR value : ");
  Serial.println(sensorval);
  if (sensorval == 1 && IRval == 1) {
     Blynk.virtualWrite(V5,"Movement Detected. Turning on light");
     digitalWrite(LIGHT, HIGH);
     led1.on();     
  }
  else {
    Blynk.virtualWrite(V5,"No movement detected.");
    digitalWrite(LIGHT, LOW);
    led1.off();
  }
  return sensorval;
}
