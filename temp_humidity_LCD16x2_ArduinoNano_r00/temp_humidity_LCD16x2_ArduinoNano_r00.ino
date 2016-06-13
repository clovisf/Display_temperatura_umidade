 #include <Wire.h>  
 #include <Artekit_SI7021.h>  
 #include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float temperaturaMaisBaixa = 100.0;
float temperaturaMaisAlta = 1.0; 
float humidadeMaisAlta = 0.0;
float humidadeMaisBaixa = 100.0;
   
 Artekit_SI7021 si7021;  

 byte topArrow[8] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
};

byte downArrow[8] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B00000,
};
   
 static void sensorRead()  
 {  
  float temperature;  
  float humidity;
      
  humidity = si7021.ReadHumidity();   
  temperature = si7021.ReadTemperature(true); 

   if (temperature >= temperaturaMaisAlta){
    temperaturaMaisAlta = temperature;
    }
   if (temperature <= temperaturaMaisBaixa){
    temperaturaMaisBaixa = temperature;
    }

    if (humidity >= humidadeMaisAlta){
    humidadeMaisAlta = humidity;
    }
   if (humidity <= humidadeMaisBaixa){
    humidadeMaisBaixa = humidity;
    }
    
  //Serial.print("RH: ");  
  //Serial.print(humidity);  
  //Serial.print("%\tTemperature: ");  
  //Serial.println(temperature);  
  
  lcd.setCursor(0, 0);
  lcd.print(temperature,1);
  lcd.setCursor(8, 0);
  lcd.print(temperaturaMaisAlta,0);
  lcd.setCursor(13, 0);
  lcd.print(temperaturaMaisBaixa,0);
  
  
  lcd.setCursor(0, 1);
  lcd.print(humidity,1);
  lcd.setCursor(8, 1);
  lcd.print(humidadeMaisAlta,0);
  lcd.setCursor(13, 1);
  lcd.print(humidadeMaisBaixa,0);
 }  
   
 void setup()  
 {  

  lcd.createChar(0, topArrow);
  lcd.createChar(1, downArrow);
  /* Start I2C */  
  Wire.begin();  
  /* Start serial */  
  Serial.begin(9600);  
  lcd.begin(16, 2);
  lcd.setCursor(4, 1);
  lcd.print("%");
  lcd.setCursor(5, 1);
  lcd.print("|");
  lcd.setCursor(4, 0);
  lcd.print("C");
  lcd.setCursor(5, 0);
  lcd.print("|");
  
  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  lcd.setCursor(12, 0);
  lcd.write(byte(1));
  lcd.setCursor(7, 1);  
  lcd.write(byte(0));
  lcd.setCursor(12, 1);
  lcd.write(byte(1)); 
  
  lcd.setCursor(10, 0);
  lcd.print("C");
  lcd.setCursor(15, 0);
  lcd.print("C");
  
  //lcd.setCursor(11, 0);
  //lcd.print("|");
  //lcd.setCursor(11, 1);
  //lcd.print("|");
    
  lcd.setCursor(10, 1);  
  lcd.print("%");
  lcd.setCursor(15, 1);
  lcd.print("%");  
  
 }  
   
 void loop()  
 {  
  static int counter = 0;  
  static bool heater = false;  
    
  sensorRead();  
     
  delay(1000);  
 }  
