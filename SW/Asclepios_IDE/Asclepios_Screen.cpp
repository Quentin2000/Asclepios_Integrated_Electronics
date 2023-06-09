#include "Asclepios_Screen.h"


void screen_setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}


void screen_update() {

  float o2 = O2_val;
  float hum = bme.humidity;
  float temp = bme.temperature;
  float pres = bme.pressure / 100.0;
  float gas = bme.gas_resistance / 1000.0;
  float alt = bme.readAltitude(SEALEVELPRESSURE_HPA);

  tft.setTextDatum(MC_DATUM);

  tft.drawString("O2", x_o2, 2*y_o2/8, Text_font);
  tft.drawString("Humidity", x_hum, 14*y_hum/20, Text_font);
  tft.drawString("Temperature", x_temp, 2*y_temp/8, Text_font);
  tft.drawString("Pressure", x_pres, 14*y_pres/20, Text_font);
  tft.drawString("Gas", x_gas, 2*y_gas/8, Text_font);
  tft.drawString("Altitude", x_alt, 14*y_alt/20, Text_font);
 
  // Set the padding to the maximum width that the digits could occupy
  // This ensures small numbers obliterate large ones on the screen
//  tft.setTextPadding( tft.textWidth("-88.88", Text_font) );
  tft.setTextPadding(0);

  if (init_loop) {
    tft.drawString(String(o2) + "%", x_o2, y_o2, Text_font);
    tft.drawString(String(hum) + "%", x_hum, y_hum, Text_font);
    tft.drawString(String(temp) + "*C", x_temp, y_temp, Text_font);
    tft.drawString(String(int(pres)) + "hPa", x_pres, y_pres, Text_font);
    tft.drawString(String(int(gas)) + "KOhm", x_gas, y_gas, Text_font);
    tft.drawString(String(alt) + "m", x_alt, y_alt, Text_font);
  }
  
  if ( abs(o2-old_o2)/old_o2*100 > screen_refresh_thresh ) {
    fillArc(x_o2, y_o2, 0, 120-120*(o2)/100, tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_o2, y_o2, 0, 120*(o2)/100, tft.width()/8, tft.width()/8, graph_thickness, o2_color(o2), init_loop, -1);
  }
  if ( abs(hum-old_hum)/old_hum*100 > screen_refresh_thresh ) {
    fillArc(x_hum, y_hum, 0, 120-120*(hum)/100, tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_hum, y_hum, 0, 120*(hum)/100, tft.width()/8, tft.width()/8, graph_thickness, hum_color(hum), init_loop, -1);
  }
  if ( (abs(temp-old_temp)/old_temp*100 > screen_refresh_thresh) || update_scales(temp, &max_temp, &min_temp) ) {
    fillArc(x_temp, y_temp, 0, 120-120*(temp-min_temp)/(max_temp-min_temp), tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_temp, y_temp, 0, 120*(temp-min_temp)/(max_temp-min_temp), tft.width()/8, tft.width()/8, graph_thickness, temp_color(temp), init_loop, -1);
  }
  if ( (abs(pres-old_pres)/old_pres*100 > screen_refresh_thresh) || update_scales(pres, &max_pres, &min_pres) ) {
    fillArc(x_pres, y_pres, 0, 120-60*pres/ATM, tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_pres, y_pres, 0, 60*pres/ATM, tft.width()/8, tft.width()/8, graph_thickness, pressure_color(pres), init_loop, -1);
  }
  if ( (abs(gas-old_gas)/old_gas*100 > screen_refresh_thresh) || update_scales(gas, &max_gas, &min_gas) ) {
    fillArc(x_gas, y_gas, 0, 120-120*gas/200, tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_gas, y_gas, 0, 120*gas/200, tft.width()/8, tft.width()/8, graph_thickness, color(0, 200, 0, brightness), init_loop, -1);
  }
  if ( (abs(alt-old_alt)/old_alt*100 > screen_refresh_thresh) || update_scales(alt, &max_alt, &min_alt) ) {
    fillArc(x_alt, y_alt, 180, 120-60*(alt-min_alt)/(max_alt-min_alt), tft.width()/8, tft.width()/8, graph_thickness, 0, 2, 1);
    fillArc(x_alt, y_alt, 180, 60*(alt-min_alt)/(max_alt-min_alt), tft.width()/8, tft.width()/8, graph_thickness, color(0, 0, 200, brightness), init_loop, -1);
  }

  check_ten(o2, old_o2, x_o2, y_o2);
  check_ten(hum, old_hum, x_hum, y_hum);
  check_ten(temp, old_temp, x_temp, y_temp);
  check_ten(pres, old_pres, x_pres, y_pres);
  check_ten(gas, old_gas, x_gas, y_gas);
  check_ten(alt, old_alt, x_alt, y_alt);

  tft.drawString(String(100), x_o2, y_o2 - tft.width()/24, Text_font - 1);
  tft.drawString(String(100), x_hum, y_hum - tft.width()/24, Text_font - 1);
  tft.drawString(String(max_temp), x_temp, y_temp - tft.width()/24, Text_font - 1);
  tft.drawString(String(max_pres), x_pres, y_pres - tft.width()/24, Text_font - 1);
  tft.drawString(String(max_gas), x_gas, y_gas - tft.width()/24, Text_font - 1);
  tft.drawString(String(max_alt), x_alt, y_alt - tft.width()/24, Text_font - 1);

  tft.drawString(String(o2) + "%", x_o2, y_o2, Text_font);
  tft.drawString(String(hum) + "%", x_hum, y_hum, Text_font);
  tft.drawString(String(temp) + "*C", x_temp, y_temp, Text_font);
  tft.drawString(String(int(pres)) + "hPa", x_pres, y_pres, Text_font);
  tft.drawString(String(int(gas)) + "KOhm", x_gas, y_gas, Text_font);
  tft.drawString(String(alt) + "m", x_alt, y_alt, Text_font);
  
  init_loop = 0;
  old_o2 = o2;
  old_hum = hum;
  old_temp = temp;
  old_pres = pres;
  old_gas = gas;
  old_alt = alt;
}


// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 3 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16 bit colour value
// clockwise = 1 if you want to display clockwise, -1 if counterclockwise

void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour, int init_loop, int clockwise)
{

  byte seg = 3; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 3; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((clockwise * (i + seg) - 90) * DEG2RAD);
    float sy2 = sin((clockwise * (i + seg) - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;

    if (init_loop == 1) {
      delay(1);
    } 
    else if (init_loop == 2) {
      delay(10);
    }
    else { }
  }
}

// Input: RGB channels of 256 values each
// Ouput: single byte color made of
// Red (top 5 bits of a 16 bit colour value)
// Green ( middle 6 bits)
// Blue (bottom 5 bits)
unsigned int color(byte red, byte green, byte blue, int brightness)
{
  blue =  (blue >> 3) * brightness / 100 ;
  green = (green >> 2) * brightness / 100 ;
  red =   (red >> 3) * brightness / 100 ;

  return (red << 11) + (green << 5) + blue;
}


unsigned int o2_color(float o2) {
  byte r = 0;
  byte g = 0;
  byte b = 0;
  if ( (min_O2 < o2) && (o2 < max_O2) ) {
    g = base_green;
  }
  else if (o2 < min_O2) {
    r = __min(abs(o2 - min_O2)*100, 255);
    g = __max(base_green - abs(o2 - min_O2)*100, 0);
  }
  else if (o2 > max_O2) {
    r = __min(abs(o2 - max_O2)*100, 255);
    g = __max(base_green - abs(o2 - max_O2)*100, 0);
  } 
  return color(r, g, b, brightness);
}

unsigned int hum_color(float humidity) {
  byte r = 0;
  byte g = 0;
  byte b = 0;
  if ( (min_hum < humidity) && (humidity < max_hum) ) {
    g = base_green;
  }
  else if (humidity < min_hum) {
    r = __min(abs(humidity - min_hum)*100, 255);
    g = __max(base_green - abs(humidity - min_hum)*100, 0);
  }
  else if (humidity > max_hum) {
    r = __min(abs(humidity - max_hum)*100, 255);
    g = __max(base_green - abs(humidity - max_hum)*100, 0);
  } 
  return color(r, g, b, brightness);
}

unsigned int temp_color(float temp) {
  byte r = 0;
  byte g = 0;
  byte b = 0;

//  r = __min(abs(temp - min_temp)/(max_temp - min_temp)*255, 255);
//  g = __min(255 - (abs(temp - (max_temp + min_temp)/2) / (max_temp - min_temp) * 255/2) , 255);
//  b = __min(abs(temp - max_temp)/(max_temp - min_temp)*255, 255);

  r = (PI/2-abs(atan2((temp-max_temp), 1.0)))/(PI/2)*255;
  g = (PI/2-abs(atan2((temp-(max_temp+min_temp)/2)/5, 1.0)))/(PI/2)*255;
  b = (PI/2-abs(atan2((temp-min_temp), 1.0)))/(PI/2)*255;

  return color(r, g, b, brightness);
}

unsigned int pressure_color(float pres) {
  byte r = 0;
  byte g = 0;
  byte b = 0;

//  r = __min(abs(pres - min_temp)/(max_pres - min_pres)*255, 255);
//  g = __min(255 - (abs(pres - (max_pres + min_pres)/2) / (max_pres - min_pres) * 255/2) , 255);
//  b = __min(abs(pres - max_pres)/(max_pres - min_pres)*255, 255);

  r = (PI/2-abs(atan2((pres-max_pres)/100, 1.0)))/(PI/2)*255;
  g = (PI/2-abs(atan2((pres-(max_pres+min_pres)/2)/100, 1.0)))/(PI/2)*255;
  b = (PI/2-abs(atan2((pres-min_pres)/100, 1.0)))/(PI/2)*255;
  
  return color(r, g, b, brightness);
}

bool update_scales(float val, float *max_val, float *min_val) {
  if ((val-(*min_val))/((*max_val)-(*min_val)) > 0.95) {
    *max_val = 2*(*max_val);
    return 1;
  }
  else if ((val-(*min_val))/((*max_val)/2-(*min_val)) < 0.80) {
    *max_val = (*max_val)/2;
    return 1;
  }
  return 0;
}

void check_ten(float val, float old_val, float x_pos, float y_pos) {
  if ( (val < 10 && old_val > 10)
    || (val < 100 && old_val > 100)
    || (val < 1000 && old_val > 1000)) {
    tft.fillCircle(x_pos, y_pos, tft.width()/10, color(0, 0, 0, 0));
  }
}
