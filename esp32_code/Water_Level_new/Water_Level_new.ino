//接5V！！！

int Value = 0;
int Max_Value = 2000;
int Min_Value = 1000;
int Difference_Value = Max_Value - Min_Value;
float Relative_Height = 0;
void setup() {

  Serial.begin(115200);

}

void loop() {
  Value = analogRead(35);
  if(Value>3000){
    Serial.println("高水位");
  }else if(Value >= 2300 && Value <= 3000){
     Serial.println("中水位");
  }else{
     Serial.println("低水位");
  }
  /*
  int x = Value;
  if(Value>Max_Value){
    Serial.println("Hi");
  }
  else if(Value >= Min_Value && Value <= Max_Value){
    //Relative_Height = (Value-Min_Value) / static_cast<float>(Difference_Value) * 40;
    Relative_Height = 2.1579001971154462e-10*x*x*x*x-0.0000012208735345987896*x*x*x+0.0024948646125112083*x*x-2.1353293910152713*x+645.5482933913077;
    Serial.print("相对水位："); 
    Serial.print(Relative_Height); 
    Serial.println("mm");
  }
  else{
    Serial.println("Lo");
  }
*/
  //Serial.println(analogRead(34));
  Serial.println(Value);

  delay(1000);
}
