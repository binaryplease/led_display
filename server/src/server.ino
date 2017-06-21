// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 3

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(15, 9, PIN,
                NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
                NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
        matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

uint32_t my_tick;
int incomingByte = 0;   // for incoming serial data
int pass = 0;

void setup() {
        matrix.begin();
        matrix.setTextWrap(false);
        matrix.setBrightness(40);
        matrix.setTextColor(colors[0]);
        Serial.begin(115200);
        matrix.fillScreen(0);
        Serial.println("ready");
        my_tick = millis();


}


char buffer[100];
int len = 0;

void loop() {

        /*if((millis() - my_tick) >= 100) {*/
        /*my_tick = millis();*/

        while(Serial.available()) {
                char c = Serial.read();
                if(c == '\n') {
                        parseBuffer();
                        len=0;
                } else {
                        buffer[len++] = c;
                }
        }
        /*}*/
}
int x,y,r,g,b;

void parseBuffer() {
        matrix.setCursor(x, 0);
        // look for the next valid integer in the incoming serial stream:


        x = getValue(buffer, ':', 0).toInt();
        y = getValue(buffer, ':', 1).toInt();
        r = getValue(buffer, ':', 2).toInt();
        g = getValue(buffer, ':', 3).toInt();
        b = getValue(buffer, ':', 4).toInt();

        matrix.drawPixel(x, y, matrix.Color(r,g,b));
        matrix.show();
}


String getValue(String data, char separator, int index)
{
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;

        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i+1 : i;
                }
        }
        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
