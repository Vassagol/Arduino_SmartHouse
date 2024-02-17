#include "DHT.h"
#include "GyverOLED.h"
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

float temp_delta=0;
float hum_delta=0;
float h=0;
float t=0;
int it=0;

#define DHTPIN 2 
DHT dht(DHTPIN, DHT11);
void setup() 
{
  Serial.begin(9600);
  dht.begin();
  oled.init();
  oled.home();
  Wire.setClock(400000L);

}

void loop() 
{
  if (it<10)
  {
  delay(1000);
  measure();
  float_check();
  output();
  } else
  {
    delay(10000);
  measure();
  float_check();
  output();
  }
}
void measure()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
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

  oled.setCursorXY(0, 20);
  oled.print(t);
  oled.print("   ");
  oled.print(h);
  oled.print("%");
  oled.circle(33,22,1,OLED_FILL);


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
  temp_delta+=t;
  hum_delta+=h;
  it++;
  }
}