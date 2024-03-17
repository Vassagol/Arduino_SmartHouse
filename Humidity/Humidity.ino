#include "GyverOLED.h"
#include <GyverBME280.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
GyverBME280 bme; 

float temp_delta=0;
float hum_delta=0;
float h=0;
float t=0;
float p=0;
float  pressure_delta=0;
int it=0;

#define DHTPIN 2 
void setup() 
{
  Serial.begin(9600);
  oled.init();
  oled.home();
  Wire.setClock(400000L);

if (!bme.begin(0x76)) Serial.println("Error!");
}

void loop() 
{
  delay((it < 10) ? 1000 : 10000);
  call();
  
}

void call()
{
  measure();
  float_check();
  output();
}

void measure()
{
  h = bme.readHumidity();
  t = bme.readTemperature();
  p = bme.readPressure();
  if (isnan(h) || isnan(t)) {
     oled.setCursorXY(20, 0);
  oled.print("Error");
    return;
  }
}

void output()
{
  oled.clear();
  oled.setScale(1);
  oled.circle(90,3,3,OLED_FILL);

  oled.setScale(2);
  oled.setCursorXY(0, 20);
  oled.print("p:");
  oled.print(pressure_delta/it);


  oled.setScale(2);
  oled.setCursorXY(0, 0);
  oled.print("t:");
  oled.print(temp_delta/it);

  oled.setCursorXY(0, 40);
  oled.print("Hum:");
  oled.print(hum_delta/it);
  oled.print("%");
}

void float_check()
{
   if(it>1000)
  {
    temp_delta=0;
    hum_delta=0;
    it=0;
  }
  else
  {
  pressure_delta+=p;
  temp_delta+=t;
  hum_delta+=h;
  it++;
  }
}