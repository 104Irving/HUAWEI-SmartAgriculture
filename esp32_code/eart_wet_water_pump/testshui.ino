#define SOIL_MOISTURE_PIN 34
#define PUMP_PIN 14
#define DRY 10//%
#define  MID 30//%
#define PUMP_DURATION 1000 // Pump duration in milliseconds

double moisturePercent=0;
double soilMoisture=0;

void setup() {
  pinMode(PUMP_PIN, OUTPUT);
  Serial.begin(115200);
  
}

void loop() {
   soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  Serial.println(soilMoisture);
  if(soilMoisture<1500)
  soilMoisture=1500;
  if(soilMoisture>4095)
   soilMoisture=4095;
 
  
   moisturePercent = (1 - ((soilMoisture - 1500) / 2595))*100;
  if (moisturePercent < DRY) {
    

    digitalWrite(PUMP_PIN, LOW); // Turn on the pump
    delay(PUMP_DURATION*2);
    digitalWrite(PUMP_PIN, HIGH); // Turn off the pump
      Serial.println("湿润程度: ");
      Serial.print(moisturePercent);
      Serial.println("%");

  }
else if (moisturePercent < MID) {
      digitalWrite(PUMP_PIN, LOW); // Turn on the pump
     delay(PUMP_DURATION);
      digitalWrite(PUMP_PIN, HIGH); // Turn off the pump
      Serial.println("湿润程度: ");
      Serial.print(moisturePercent);
      Serial.println("%");

  }

  else{
    digitalWrite(PUMP_PIN, HIGH); // Turn off the pump
    Serial.println("湿润程度: ");
    Serial.print(moisturePercent);
    Serial.println("%");
    delay(1000);
    }
  
}
