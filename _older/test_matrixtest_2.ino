/* ========================== INCLUDES ================================= */
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

/* ========================== NEOPIXELS SETTINGS ================================= */

#define NEOPIN 6
#define MATRIX_W 4
#define MATRIX_H 4

// neomatrix has the power and board in the bottom left. top / left is 00, and its setup in rows from left to right. 

// reference
//matrix.drawPixel(0,0,matrix.Color(255, 0, 0)); // one red pixel
//matrix.fillRect(0,1,3,2,blue);
//matrix.drawLine(0,0,4,0,matrix.Color(0,255,0));
//matrix.drawFastVLine(0,0,4,green);
//matrix.drawFastHLine(1,1,2,red);
//matrix.drawRect(1,2,2,2, blue);


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


const uint16_t green = matrix.Color(0,255,0);
const uint16_t red = matrix.Color(255,0,0);
const uint16_t blue = matrix.Color(0,0,255);
const uint16_t white = matrix.Color(255,255,255);

int randomX;
int randomY;


void setup()
{
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(60);
  matrix.fillScreen(white);

  randomX = random(0, 3);
  randomY = random(0, 3);

  //drawRandomShape(4,2,2,red);
}

void loop()
{

  //drawL(3,0,2,0,green);
  drawRect(0,0,2,2,red);
  //drawT(2,2,1,3,blue);
  

  matrix.show();
}

void drawRandomShape(int maxPixels, int x, int y, uint16_t color){

  matrix.drawPixel(x,y,color);
  maxPixels--;
  for (int i = 0; i < maxPixels; i++){
    matrix.drawPixel(rando(x),rando(y),color); // diagonal
  }


}

int rando(int x){
  if(rand()%2){
    x++;
  }else {
    x--;
  }
  return x;
}

void drawL(int c1, int c2, int c3, int c4, uint16_t color){
  // draw a line 3 squares down from origin, and one square H from end coor 
  // makes an L shape
  matrix.drawFastVLine(c1,c2,3,color);
  matrix.drawFastHLine(c3,c4,1,color);
}

void drawRect(int c1, int c2, int w, int h, uint16_t color){
  // draw a rectange and fill it
  matrix.fillRect(c1,c2,w,h,color);
}

void drawT(int c1, int c2, int c3, int c4, uint16_t color){
  matrix.drawFastVLine(c1,c2,1,color);
  matrix.drawFastHLine(c3,c4,3,color);
}

  /*matrix.drawPixel(0,1,matrix.Color(0, 255, 0)); // one g pixel
  matrix.drawPixel(0,2,matrix.Color(0, 0, 255)); // one b pixel
  matrix.drawPixel(0,3,matrix.Color(255, 0, 255)); // one purple*/
  /*matrix.fillScreen(matrix.Color(255,255,255)); // white
  
  matrix.drawPixel(1,0,matrix.Color(255, 0, 0)); // one red pixel
  matrix.drawPixel(0,1,matrix.Color(255, 0, 0)); // one red pixel
  matrix.drawPixel(1,1,matrix.Color(255, 0, 0)); // one red pixel*/