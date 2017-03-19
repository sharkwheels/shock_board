// Reed Switch Matrix Test courtesy of Jane H.
// Still need to work in 2nd player

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#define NEOPIN 2
#define MATRIX_W 2
#define MATRIX_H 2

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_W, MATRIX_H, NEOPIN,
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

// Array of pins for the rows
int rPins[] = {6,7};
int rPinsNo = sizeof(rPins) / sizeof(int);

// Array of pins for the columns
int cPins[] = {9,10};
int cPinsNo = sizeof(cPins) / sizeof(int);

// [ROW][COLUMN][CORRDINATE]
int buttonMap[2][2][2] = {
	{{0,0},{0,1}},
	{{1,0},{1,1}}
};

// out and in pins
int resetBtn = 4;
int roundBtn = 3;

int ledPin = 13;
int p1Shock = 52;
int p2Shock = 53;

bool oldResetState = HIGH;
bool oldRoundState = HIGH;

// hold the current spot
int currentX = 0;
int currentY = 0;

int currentBoard[2][2] = {};
bool isP1Round = true;
int doNotShock = 0;

// board tests

	int boardOne[2][2] = {
		{0,0},
		{1,1},
	};

	int boardTwo[2][2] = {
		{1,0},
		{0,1}
	};

	int boardThree[2][2] = {
		{1,1},
		{0,1}
	};

void setup() 
{
	randomSeed(analogRead(A0));
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
  pinMode(p1Shock, OUTPUT);
  pinMode(p2Shock, OUTPUT);

  pinMode(resetBtn, INPUT_PULLUP);



  matrix.begin();
  matrix.setBrightness(60);
  matrix.fillScreen(matrix.Color(255, 255, 255));
  
  chooseBoard(random(1,4));
  Serial.println("Setup Done");

}

void loop() 
{
	// loop through all the pins
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
				currentX = buttonMap[rowPin][colPin][0];
				currentY = buttonMap[rowPin][colPin][1];
				int getPatternCode = currentBoard[currentX][currentY];
				Serial.println(getPatternCode);

				// if the button is new and has not been tripped (9)
				if(getPatternCode != 9)
				{
					if(isP1Round)
					{
						// if the stored pattern value is 1
						// shock player 1
						// turn the square red
						if(getPatternCode == 1)
						{
							digitalWrite(p1Shock, HIGH);
							delay(500);
							digitalWrite(p1Shock, LOW);
							matrix.drawPixel(currentX,currentY,matrix.Color(255,0,0)); 
						}else{
							// it is land
							// draw one blue pixel
							matrix.drawPixel(currentX,currentY,matrix.Color(0, 0, 255)); 
						}
						// set round to P2's turn
						isP1Round = false;
					}
					else
					{	
						
						// if the stored pattern value is 1
						// shock player 2
						// turn the square red
						if(getPatternCode == 1)
						{
							digitalWrite(p2Shock, HIGH);
							delay(500);
							digitalWrite(p2Shock, LOW);
							matrix.drawPixel(currentX,currentY,matrix.Color(255,0,0)); 
						} else{
							// it is land
							// draw one green pixel
							matrix.drawPixel(currentX,currentY,matrix.Color(0, 255, 0)); 
						}
						// set the round to P1's turn
						isP1Round = true;
					}
					// code the current square as taken 
					currentBoard[currentX][currentY] = 9;
				}
				delay(200); 
			}
			else 
			{
				digitalWrite(ledPin, LOW);
			}
  	}
  	digitalWrite(rPins[rowPin], LOW);		
	}

	// reset button
	bool newResetState = digitalRead(resetBtn);
  if (newResetState == LOW && oldResetState == HIGH) 
  {
  	resetEverything();
  	delay(50);
  }
	oldResetState = newResetState;

	matrix.show();
}

void resetEverything()
{
	matrix.fillScreen(matrix.Color(255, 255, 255));
  chooseBoard(random(1,4));
  currentY = 0;
  currentX = 0;

}

void chooseBoard(int command){
	if(command == 1)
	{
		boardPattern(boardOne);
	}
	else if(command == 2)
	{
		boardPattern(boardTwo);
	}
	else if(command == 3)
	{
		boardPattern(boardThree);

	}	
	Serial.print("board: ");
	Serial.print(command);
	Serial.println();
}

void boardPattern(int pattern[2][2])
{
	// assign chosen pattern as current pattern
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			currentBoard[i][j] = pattern[i][j];
		}
	}
	// 1 = sea (shock)
	// 0 = land (safe)
	/*for(int row = 0; row < rPinsNo; row++) 
	{
    for(int column = 0; column < cPinsNo; column++) 
    {
     if(pattern[row][column] == 1) 
     {
       matrix.drawPixel(row,column,matrix.Color(0255, 0, 0)); // one red pixel
     } 
   }
  }*/
	
}


