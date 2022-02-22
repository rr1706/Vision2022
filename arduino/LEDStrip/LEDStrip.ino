#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel onboard = Adafruit_NeoPixel(1, 40, NEO_RGB + NEO_KHZ400);

void setup() {
    onboard.begin();
    onboard.setBrightness(255);
    onboard.show();
}

void loop() {
    int r, g, b = 0;
    
    for(r = 0; r <= 255; r++) {
        onboard.setPixelColor(0, onboard.Color(r, g, b)); 
        onboard.show();
    }
    for(g = 0; g <= 255; g++) {
        onboard.setPixelColor(0, onboard.Color(r, g, b)); 
        onboard.show();
    }
    for(b = 0; b <= 255; b++) {
        onboard.setPixelColor(0, onboard.Color(r, g, b)); 
        onboard.show();
    }
}
