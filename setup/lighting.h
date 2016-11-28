#ifndef LIGHTING_H
#define LIGHTING_H

int move=1;       //  Move light
int light=1;      //  Lighting
// Light values
int one       =   1;  // Unit value
int distance  =   250;  // Light distance
int ball_inc  =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  20;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   100;  // Elevation of light

#endif
