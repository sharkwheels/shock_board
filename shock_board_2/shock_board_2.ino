
/************

Alright so this shit ain't right either. But I guess welcome to my learning process?
I hate everything rn
*************/


/* ========================== INCLUDES ================================= */
#include "RGB.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

/* ========================== NEOPIXELS SETTINGS ================================= */
#define NEOPIN 6
#define MATRIX_W 4
#define MATRIX_H 4


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, NEOPIN,
  NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);


/* ========================== BOARD / GRID STUFF ================================= */

/* coordinates for a 4 x 4 grid
00,10,20,30
01,11,21,31
02,12,22,32
03,13,23,33,
04,14,24,34
*/

int board_full[4][4] = {};

// button pin
int BUTTON_PIN = 5;
// button state
bool oldState = HIGH;



/* ========================== SETUP AND LOOP ================================= */

void setup(){

  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  matrix.begin();
  matrix.setBrightness(60);
  matrix.fillScreen(matrix.Color(off.r,off.g,off.b));
  crossFade(off, white, 50, 5);
  drawBoard();
  
  //matrix.setPixelColor(random(0, 16);,0,255,0);  // OFFs I could have just done this? 0 - 16. :-/ merrrr. ok. hm.
}

void loop(){

  int location = random(0,16);
  bool newState = digitalRead(BUTTON_PIN);
  if (newState == LOW && oldState == HIGH) {
    delay(50);
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW){
      //matrix.setPixelColor(location,0,255,0);  // OFFs I could have just done this? 0 - 16. :-/ merrrr. ok. hm.
      //Serial.println(location);
      matrix.fillScreen(matrix.Color(white.r,white.g,white.b));
      drawBoard();
    }
  }
  oldState = newState;

  matrix.show();
}

/* ========================== FUNCTIONS ================================= */



void drawBoard() {
  int tester;
  for(int row = 0; row < MATRIX_W; row++) {
      tester = board_full[row][0];
    for(int column = 0; column < MATRIX_H; column++) {
     board_full[row][column] = random(0,2);
     //Serial.println(board_full[row][column]);
    //Serial.println(board_full[column][0]);
     if(board_full[row][column] == 1) {
       matrix.drawPixel(column, row, matrix.Color(red.r,red.g,red.b));
     } 
   }
  }
  //Serial.println(tester);
  //Serial.println("-----");
}

/* ========================== NEOPIXEL FUNCTIONS ================================= */

  /*int land[4][4] = {  
   {1, 1, 0, 0},
   {0, 1, 1, 0},
   {0, 1, 0, 1},
   {0, 0, 0, 1}
  };*/

// https://www.twilio.com/blog/2015/05/light-up-your-hackpack-with-the-adafruit-neomatrix-library.html

// Crossfade entire screen from startColor to endColor
void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}


