#include <Arduino.h>
#include <spliner.h>
#include "MatrixMath.h"


void setup() {
    Serial.begin(9600);
    float arr[8]={0,3,
                  1,2,
                  2,-2,
                  3,1};
    Matrix input(4,2, arr);
    Spliner spline(input);
    float out = spline.calc_spline_for_x(2.5);
    Serial<<out;
}

void loop() {
// write your code here
}