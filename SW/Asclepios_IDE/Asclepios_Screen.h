#include "Asclepios_IDE.h"

#ifndef ASCLEPIOS_SCREEN_H
#define ASCLEPIOS_SCREEN_H


void screen_setup();
void screen_update();
void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour, int init_loop, int clockwise);
unsigned int color(byte red, byte green, byte blue, int brightness);
unsigned int o2_color(float o2);
unsigned int hum_color(float humidity);
unsigned int temp_color(float temp);
unsigned int pressure_color(float pres);
bool update_scales(float val, float *max_val, float *min_val);
void check_ten(float val, float old_val, float x_pos, float y_pos);


#endif // #define ASCLEPIOS_SCREEN_H