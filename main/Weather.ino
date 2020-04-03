const String endpoint = "https://prodapi.metweb.ie/weather/short/Dublin";

int Weather() {
  
  HTTPClient http;
  http.begin(endpoint); //Specify the URL
  int httpCode = http.GET();  //Make the request
  
  if (httpCode > 0) { //Check for the returning code
      char json[400];
      StaticJsonBuffer<400> JSONBuffer;                         //Memory pool

      String payload = http.getString();
      payload.toCharArray(json, 400);
      //Serial.println(httpCode);
      //Serial.println(payload);
      JsonObject& parsed = JSONBuffer.parseObject(json); //Parse message
      
      if (!parsed.success()) {   //Check for errors in parsing
        Serial.println("Parsing failed");
        return -1;
      }
      int temperature = parsed["temperature"];                    //Get value of sensor measurement
      String weather = parsed["weather"];
      float rainfall = parsed["rainfall"];
      int humidity = parsed["humidity"];
      int windspeed = parsed["windspeed"];
      
      Blynk.virtualWrite(V6, temperature);
      Blynk.virtualWrite(V7, weather);
      Blynk.virtualWrite(V10, "add", 1, "Windspeed", String(windspeed)+" Km/hr");
      Blynk.virtualWrite(V10, "add", 2, "Rainfall", String(rainfall)+" cm");
      Blynk.virtualWrite(V10, "add", 3, "Humidity", String(humidity)+"%");
      if (humidity > 95) 
        Blynk.virtualWrite(V8, "Humidity is high. Carry an umbrella while going out");
  }
  else {
    Serial.println("Error on HTTP request");
  }
  http.end(); //Free the resources
  return temperature;
}
