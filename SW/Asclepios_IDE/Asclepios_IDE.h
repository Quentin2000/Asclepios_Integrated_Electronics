#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HardwareSerial.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

//#include <stdlib.h>

#define __min(a,b) ((a)<(b)?(a):(b)) 
#define __max(a,b) ((a)>(b)?(a):(b))

// WIFI Setup
extern char ssid [64];
extern char password [64];
extern String HOST_NAME; // Local Host's IP address to be changed 
// String PATH_NAME   = "/insert_temp.php";
// String queryString = "?temperature=30.5";

// UART1 (O2 sensor)
#define RX1 16
#define TX1 17
extern HardwareSerial Uart1;
extern float O2_val; // [%] default value
extern float old_o2;    // [%]
extern float min_O2; // [%] according to safety regulations
extern float max_O2; // [%] according to safety regulations

// I2C1 (BME sensor)
#define BME_SDA 5
#define BME_SCL 6
#define BME_ADDR 0x76
#define SEALEVELPRESSURE_HPA (1013.25)
extern Adafruit_BME680 bme; // I2C
#define ATM 1013.25 // 1 atm = 1013,25 hPa
extern float min_pres; // [*C] according to safety regulations
extern float max_pres; // [*C] according to safety regulations
extern float old_pres;
extern float min_temp; // [*C] according to safety regulations
extern float max_temp; // [*C] according to safety regulations
extern float old_temp;
extern float min_hum; // [%] according to safety regulations
extern float max_hum; // [%] according to safety regulations
extern float old_hum;
extern float max_alt; // [m] for display purposes
extern float min_alt; // [m] for display purposes
extern float old_alt;
extern float max_gas; // [KOhm] for display purposes
extern float min_gas; // [KOhm] for display purposes
extern float old_gas;

// /!\ CAREFUL, DO NOT CHOOSE MAX_VAL = 2*MIN_VAL AS A DIVISION BY 0 ERROR WILL OCCUR SOMEHOW /!\

// SPI1 (SD card)
#define SPI1_MISO   MISO  // 37
#define SPI1_MOSI   MOSI  // 35
#define SPI1_SCLK   SCK   // 36
#define SPI1_SS     SS    // 34
extern SPIClass * SPI1;
extern uint8_t cardType;
extern uint16_t mission_log_nbr;
extern char mission_log_file [64];

// SPI2 (Screen) (defined in the Arduino/libraries/TFT_eSPI/User_Setup.h file)
//#define SPI2_MISO   39
//#define SPI2_MOSI   41
//#define SPI2_SCLK   40
//#define SPI2_SS     42
extern TFT_eSPI tft;       // Invoke custom library
extern float Text_font;
extern uint16_t x_o2;
extern uint16_t y_o2;
extern uint16_t x_hum;
extern uint16_t y_hum;
extern uint16_t x_temp;
extern uint16_t y_temp;
extern uint16_t x_pres;
extern uint16_t y_pres;
extern uint16_t x_gas;
extern uint16_t y_gas;
extern uint16_t x_alt;
extern uint16_t y_alt;
#define DEG2RAD 0.0174532925
extern byte base_green; // over 256 values
extern int brightness; // [%]
extern int graph_thickness;
extern float screen_refresh_thresh;
extern int init_loop;
