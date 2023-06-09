#include "Asclepios_IDE.h"
#include "Asclepios_SD.h"
#include "Asclepios_Remote.h"
#include "Asclepios_O2.h"
#include "Asclepios_BME.h"
#include "Asclepios_Screen.h"

#define __min(a,b) ((a)<(b)?(a):(b)) 
#define __max(a,b) ((a)>(b)?(a):(b))

// WIFI Setup
char ssid [64];
char password [64];
String HOST_NAME = "http://172.20.10.4"; // Local Host's IP address to be changed 
// String PATH_NAME   = "/insert_temp.php";
// String queryString = "?temperature=30.5";

// UART1 (O2 sensor)
HardwareSerial Uart1(1);
float O2_val = 0.0; // [%] default value
float old_o2 = 0;    // [%]
float min_O2 = 19.5; // [%] according to safety regulations
float max_O2 = 23.5; // [%] according to safety regulations

// I2C1 (BME sensor)
Adafruit_BME680 bme; // I2C
float min_pres = 0.47*ATM; // [*C] according to safety regulations
float max_pres = 1.53*ATM; // [*C] according to safety regulations
float old_pres = 0;
float min_temp = -10.0; // [*C] according to safety regulations
float max_temp = 50.0; // [*C] according to safety regulations
float old_temp = 0;
float min_hum = 40.0; // [%] according to safety regulations
float max_hum = 70.0; // [%] according to safety regulations
float old_hum = 0;
float max_alt = 400; // [m] for display purposes
float min_alt = 0; // [m] for display purposes
float old_alt = 0;
float max_gas = 400; // [KOhm] for display purposes
float min_gas = 0; // [KOhm] for display purposes
float old_gas = 0;

// /!\ CAREFUL, DO NOT CHOOSE MAX_VAL = 2*MIN_VAL AS A DIVISION BY 0 ERROR WILL OCCUR SOMEHOW /!\

// SPI1 (SD card)
SPIClass * SPI1 = NULL;
uint8_t cardType = CARD_NONE;
uint16_t mission_log_nbr = 0;
char mission_log_file [64];

// SPI2 (Screen) (defined in the Arduino/libraries/TFT_eSPI/User_Setup.h file)
//#define SPI2_MISO   39
//#define SPI2_MOSI   41
//#define SPI2_SCLK   40
//#define SPI2_SS     42
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
float Text_font = 2.0;
uint16_t x_o2 = 1*tft.height()/6;
uint16_t y_o2 = 8*tft.width()/24;
uint16_t x_hum = 1*tft.height()/6;
uint16_t y_hum = 20*tft.width()/24;
uint16_t x_temp = 3*tft.height()/6;
uint16_t y_temp = 8*tft.width()/24;
uint16_t x_pres = 3*tft.height()/6;
uint16_t y_pres = 20*tft.width()/24;
uint16_t x_gas = 5*tft.height()/6;
uint16_t y_gas = 8*tft.width()/24;
uint16_t x_alt = 5*tft.height()/6;
uint16_t y_alt = 20*tft.width()/24;
byte base_green = 100; // over 256 values
int brightness = 100; // [%]
int graph_thickness = 5;
float screen_refresh_thresh = 1.0;
int init_loop = 1;


void setup() {
  
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("Welcome to the Asclepios 3.0 Onboard Computer!"));
  Serial.println();

  SD_setup();
  // remote_monitoring_setup();
  screen_setup();
  O2_setup();
  BME_setup();
}

void loop() {
  
  O2_acquisition();
  delay(1000);
  BME_acquisition();
  delay(10);
  screen_update();
  delay(10);
  SD_update();
  delay(10);
  // remote_monitoring_update();
  // delay(10);
}







