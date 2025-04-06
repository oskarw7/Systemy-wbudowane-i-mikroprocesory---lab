#include <math.h> // ewentualnie cmath
#include <SPI.h>
#include "LCD.h"
#include "DEV_Config.h"
#include "ADXL345.h"

#define PI 3.14159265358979323846

ADXL345 accelerometer;

const int LINE_LENGTH = 22;
const int LINE_HEIGHT = 16;
const int START_Y = 22;


void setup() {
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);

  accelerometer.begin();
  accelerometer.setRange(ADXL345_RANGE_4G);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD.LCD_Init(Lcd_ScanDir);
  LCD.LCD_Show();
  delay(3000);
  LCD.LCD_Clear(BLACK);
  LCD.LCD_DisplayString(0, 6, "SWiM", &Font12, BLACK, YELLOW);

  Serial.begin(9600);
}

void dispAxis(int line, const char* label, int angle, float value) {
  char numbuffer[10];
  char linebuffer[LINE_LENGTH];

  dtostrf(value, 1, 2, numbuffer);
  snprintf(linebuffer, LINE_LENGTH, "%s: %d %-6s", label, angle, value);

  LCD.LCD_DisplayString(0, START_Y + line * LINE_HEIGHT, linebuffer, &Font12, BLACK, YELLOW);
}

void loop() {
  Vector filtered = accelerometer.lowPassFilter(accelerometer.readNormalize(), 0.15);

  float ax = filtered.XAxis;
  float ay = filtered.YAxis;
  float az = filtered.ZAxis;

  Serial.print ("ax = ");
  Serial.print(ax);
  Serial.print (", ay = ");
  Serial.print(ay);
  Serial.print (", az = ");
  Serial.print(az);

  float pitch = atan(ax/sqrt(ay*ay + az*az))*180/PI;
  float roll  = atan(ay/sqrt(ax*ax + az*az))*180/PI;
  float yaw   = atan(az/sqrt(ax*ax + az*az))*180/PI;

  Serial.print (", pitch = ");
  Serial.print(pitch);
  Serial.print (", roll = ");
  Serial.print(roll);
  Serial.print (", yaw = ");
  Serial.println(yaw);

  dispAxis(0,"x",(int)pitch, ax);
  dispAxis(1,"y",(int)roll, ay);
  dispAxis(2,"z",(int)yaw, az);

  delay(50);
}
