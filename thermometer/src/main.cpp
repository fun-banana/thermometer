#include <Arduino.h>
#include <TM1637Display.h>
#include <OneWire.h>
#include <DallasTemperature.h>  

#define DISPLAY_CLK 3
#define DISPLAY_DIO 2
#define TERMO_DATA 4

TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);
OneWire oneWire(TERMO_DATA);
DallasTemperature temperature_sensor(&oneWire);

int current_temperature = 0;

void updateTemperature(int temperature)
{
  if (current_temperature != temperature)
  {
    display.showNumberDec(temperature);
    current_temperature = temperature;
  }
}

void setup() 
{
  Serial.begin(9600);
  display.setBrightness(0x05);
  temperature_sensor.begin();
}

void loop() 
{
  temperature_sensor.requestTemperatures();
  updateTemperature(temperature_sensor.getTempCByIndex(0));
  Serial.println(current_temperature);
}