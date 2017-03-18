// Reed Switch Matrix Test courtesy of Jane H.

// Array of pins for the rows
int rPins[] = {6,7};
int rPinsNo = sizeof(rPins) / sizeof(int);

// Array of pins for the columns
int cPins[] = {9,10};
int cPinsNo = sizeof(cPins) / sizeof(int);

// [rows][cols]
int prev[2][2] = {0};

// [ROW][COLUMN]
int buttonMap[2][2] = {
	{1,2},
	{3,4}
};

int ledPin = 13;
int roundBtn = 3;
int currentSquare = 0;


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
				currentSquare = buttonMap[rowPin][colPin];
				Serial.print("square: ");
				Serial.println(currentSquare);
				delay(200); 
				
			}
			else {
				digitalWrite(ledPin, LOW);
			}
  	}

  	digitalWrite(rPins[rowPin], LOW);		
	}
}