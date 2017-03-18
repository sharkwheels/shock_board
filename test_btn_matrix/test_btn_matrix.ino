// Reed Switch Matrix Test courtesy of Jane H.

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#define NEOPIN 2
#define MATRIX_W 4
#define MATRIX_H 4

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, NEOPIN,
                            NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

// Array of pins for the rows
int rPins[] = {6,7};
int rPinsNo = sizeof(rPins) / sizeof(int);

// Array of pins for the columns
int cPins[] = {9,10};
int cPinsNo = sizeof(cPins) / sizeof(int);

// [rows][cols]
int prev[2][2] = {0};

// [ROW][COLUMN][CORRDINATE]
int buttonMap[2][2][2] = {
	{{0,0},{1,0}},
	{{0,1},{1,1}}
};

int ledPin = 13;
int roundBtn = 3;

int currentX = 0;
int currentY = 0;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Multiplexed Buttons Test");

	// Set the Row pin mode 
	// these are triggers, so set them as output
  Serial.println("Setting Row Pins...");
  for(int i = 0; i < rPinsNo; i++)
  {
  	pinMode(rPins[i], OUTPUT);
  	digitalWrite(rPins[i], LOW);
  	Serial.println(rPins[i]);
  }

  //Set the Column Pin Mode (Input)
  // sensing if trigger is high
  Serial.println("Setting Column Pins...");
  for(int i = 0; i < cPinsNo; i++)
  {
  	pinMode(cPins[i], INPUT);
  	Serial.println(cPins[i]);
  }

  pinMode(ledPin, OUTPUT);

  matrix.begin();
  matrix.setBrightness(60);
  matrix.fillScreen(matrix.Color(255, 255, 255));
  matrix.drawPixel(0,0,matrix.Color(0, 255, 0)); // one green pixel

  Serial.println("Setup Done");

}

void loop() 
{
	for(int rowPin = 0; rowPin < rPinsNo; rowPin++)
	{
		digitalWrite(rPins[rowPin], HIGH);

		for(int colPin = 0; colPin < cPinsNo; colPin++)
		{
			if(HIGH == digitalRead(cPins[colPin]))
			{
				//Serial.println(buttonMap[rowPin][colPin]);

				digitalWrite(ledPin, HIGH);
				// pull the current co-ordinate of the button pin 
				// that is registering: 0,0 - 0,1 - 0,2 etc
				currentX = buttonMap[rowPin][colPin][0];
				currentY = buttonMap[rowPin][colPin][1];

				// draw a red pixel at the given co-ordinate on the neomatrix
				matrix.drawPixel(currentX,currentY,matrix.Color(255, 0, 0)); // one red pixel

				// print that shit
				Serial.print("square: ");
				Serial.print(currentX);
				Serial.print(",");
				Serial.print(currentY);
				Serial.println();

				// delay
				delay(200); 
				
			}
			else {
				digitalWrite(ledPin, LOW);
			}
  	}

  	digitalWrite(rPins[rowPin], LOW);		
	}
matrix.show();
}

