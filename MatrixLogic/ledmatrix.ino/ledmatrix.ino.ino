#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
/* ========================== NEOPIXELS SETTINGS ================================= */
#define NEOPIN 6
#define MATRIX_W 4
#define MATRIX_H 4
#define numOfShocks 6;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, NEOPIN,
                            NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

int board_full[4][4] = {};
// button pin
int BUTTON_PIN = 5;
// button state
bool oldState = HIGH;
/* ========================== SETUP AND LOOP ================================= */
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  matrix.begin();
  matrix.setBrightness(60);
  ///matrix.fillScreen(matrix.Color(off.r,off.g,off.b));
  //crossFade(off, white, 50, 5);
  //matrix.setPixelColor(random(0, 16);,0,255,0);  // OFFs I could have just done this? 0 - 16. :-/ merrrr. ok. hm.
}

void loop() {
  bool newState = digitalRead(BUTTON_PIN);
  if (newState == LOW && oldState == HIGH) {
    delay(50);
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      reset();
      seed();
    }
  }
  oldState = newState;
  matrix.show();
}
void seed() {
  //for(int i = 0; i <= 2; i++){
  int randRow = int(random(0, 4));
  int randCol = int(random(0, 4));
  // makeLine(randCol, randRow);
  // makeSquare(randCol, randRow);
  if (checkIfCool(randCol, randRow)) {
    makeElle(randCol, randRow);
  } else {
    // get new randoms
  }
  //   matrix.drawPixel(randCol, randRow, matrix.Color(255,0,0));
  Serial.print(randRow);
  Serial.print(" and " );
  Serial.println(randCol);
  //  }
}
void makeLine(int col, int row) {
  matrix.drawPixel(col, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col, row + 1, matrix.Color(255, 0, 0));
  storeIt(col, row);
  storeIt(col, row + 1);
}
void makeSquare(int col, int row) {
  matrix.drawPixel(col, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col, row + 1, matrix.Color(255, 0, 0));
  matrix.drawPixel(col + 1, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col + 1, row + 1, matrix.Color(255, 0, 0));
}
void makeElle(int col, int row) {
  matrix.drawPixel(col, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col + 1, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col + 2, row, matrix.Color(255, 0, 0));
  matrix.drawPixel(col, row + 1, matrix.Color(255, 0, 0));
}
boolean checkIfCool(int col, int row) {
  // if its not on the edge
  // if its not next to somethign else
  // if its not already taken
  if ( askIfTaken(col, row)) {
    return false;
  } else {
    return true;
  }
}
void storeIt(int col, int row) {
  board_full[row][col] = 1;
}
void reset() {
  matrix.fillScreen(matrix.Color(255, 0, 255));
  // for loop that goes through both and make it all 0;
  // pul from old draw board for loop
}

boolean askIfTaken(int row, int col) {
  if (board_full[row] == 1 && board_full[col] == 1) {
    return true;
  } else {
    return false;
  }
}
