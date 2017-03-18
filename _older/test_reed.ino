
/*******************************
  reed switch board v0.5 test
  2016
  Nadine L + Lindy W

********************************/

/* ========================== INCLUDES ================================= */
#include <elapsedMillis.h>
#include <Adafruit_NeoPixel.h>

/* ========================== NEOPIXELS SETTINGS ================================= */

/*********
simple on and off
*********/

#define NUMPIXELS 7
#define PIXELPIN 6
#define BRIGHTNESS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

uint32_t color1 = strip.Color(182, 31, 40); //Red
uint32_t color2 = strip.Color(91, 44, 86); //Purple
uint32_t color3 = strip.Color(0, 100, 0); //Green
uint32_t color4 = strip.Color(0, 0, 100); //Blue
uint32_t color5 = strip.Color(255, 255, 255); //White
uint32_t color6 = strip.Color(0, 0, 0); //Off


/*======================== PIN & BOARD SETUP ================================== */

int board_squares = 81;       // the number of squares in the board
int land_max = 16;            // the MAX number of squares that can be land
int island_min = 4;           // the MIN number of squares an island can be



// Reed switches
const int REED_PIN = 12; 
const int REED_PIN_2 = 11;
const int REED_PIN_3 = 10;
const int REED_PIN_4 = 9;

const int green_led = 8;
const int red_led = 7;

// the current square
int current_square;

bool round_player2;
bool round_player1;
bool listen_mode;

/* ======================= SETUP AND MAIN ================================= */



void setup() 
{
  Serial.begin(9600);
  /* set all your pin outputs */
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(REED_PIN_2, INPUT_PULLUP);
  pinMode(REED_PIN_3, INPUT_PULLUP);
  pinMode(REED_PIN_4, INPUT_PULLUP);

  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);

  /** Set all the pixels to white, don't animate, just set it. **/
  strip.begin();
  for(int i=0;i<NUMPIXELS;i++){
    strip.setPixelColor(i, strip.Color(255,255,255)); 
    strip.show(); 
  }
  
  Serial.println("Setting states: listen, rounds"); 
  setup_listen = false;
  round_player1 = false;
  round_player2 = false;  
  Serial.println("Setup Complete");    

}

void loop() 
{   

  strip.setBrightness(60);

  if(listen_mode){
    // do the listen for input routine for the map
    // or do the random shit and reset everything

  }else{

    int prox1 = digitalRead(REED_PIN); 
    int prox2 = digitalRead(REED_PIN_2);
    int prox3 = digitalRead(REED_PIN_3);
    int prox4 = digitalRead(REED_PIN_4);

    if (prox1 == LOW) {
      current_square = 0;
      Serial.println("Switch 1 closed");
      strip.setPixelColor(current_square, color1); 
    } else if (prox2 == LOW) {
      current_square = 1;
      strip.setPixelColor(current_square, color2); 
      Serial.println("Switch 2 closed");
    } else if(prox3 == LOW){
      current_square = 2;
      strip.setPixelColor(current_square, color3); 
      Serial.println("Switch 3 closed");
    }else if(prox4 == LOW){
      current_square = 3;
      strip.setPixelColor(current_square, color4); 
      Serial.println("Switch 4 closed");
    } else {
      strip.setPixelColor(current_square, color5); 
    }
  }

  strip.show();
}

/* ======================= FUNCTIONS ================================= */





/*
//  Jewel.Update();
  //Jewel.begin();
  //Jewel.ColorSet(Jewel.Color(200,0,0));  // does not work
  //Jewel.ColorWipe(Jewel.Color(50,0,0),1); // works but the pixel pulses which I do not want

//Jewel.ColorSet(Jewel.Color(200,0,0)); 
    //Jewel.Color(50,0,0); 
 //Jewel.setPixelColor(2, Jewel.Color(0,0,200));
 //Jewel.setPixelColor(0, Jewel.Color(200,100,0));

void JewelComplete(){
  //Jewel.Reverse();
  //Jewel.setPixelColor(1, Jewel.Color(0,200,0));
}


// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };
 
// NeoPattern Class - derived from the Adafruit_NeoPixel class
class NeoPatterns : public Adafruit_NeoPixel
{
    public:
 
    // Member Variables:  
    pattern  ActivePattern;  // which pattern is running
    direction Direction;     // direction to run the pattern
    
    unsigned long Interval;   // milliseconds between updates
    unsigned long lastUpdate; // last update of position
    
    uint32_t Color1, Color2;  // What colors are in use
    uint16_t TotalSteps;  // total number of steps in the pattern
    uint16_t Index;  // current step within the pattern
    
    void (*OnComplete)();  // Callback on completion of pattern
    
    // Constructor - calls base-class constructor to initialize strip
    NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, void (*callback)())
    :Adafruit_NeoPixel(pixels, pin, type)
    {
        OnComplete = callback;
    }
    
    // Update the pattern
    void Update()
    {
        if((millis() - lastUpdate) > Interval) // time to update
        {
            lastUpdate = millis();
            switch(ActivePattern)
            {
                case RAINBOW_CYCLE:
                    RainbowCycleUpdate();
                    break;
                case THEATER_CHASE:
                    TheaterChaseUpdate();
                    break;
                case COLOR_WIPE:
                    ColorWipeUpdate();
                    break;
                case SCANNER:
                    ScannerUpdate();
                    break;
                case FADE:
                    FadeUpdate();
                    break;
                default:
                    break;
            }
        }
    }
  
    // Increment the Index and reset at the end
    void Increment()
    {
        if (Direction == FORWARD)
        {
           Index++;
           if (Index >= TotalSteps)
            {
                Index = 0;
                if (OnComplete != NULL)
                {
                    OnComplete(); // call the comlpetion callback
                }
            }
        }
        else // Direction == REVERSE
        {
            --Index;
            if (Index <= 0)
            {
                Index = TotalSteps-1;
                if (OnComplete != NULL)
                {
                    OnComplete(); // call the comlpetion callback
                }
            }
        }
    }
    
    // Reverse pattern direction
    void Reverse()
    {
        if (Direction == FORWARD)
        {
            Direction = REVERSE;
            Index = TotalSteps-1;
        }
        else
        {
            Direction = FORWARD;
            Index = 0;
        }
    }
    
    // Initialize for a RainbowCycle
    void RainbowCycle(uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = RAINBOW_CYCLE;
        Interval = interval;
        TotalSteps = 255;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Rainbow Cycle Pattern
    void RainbowCycleUpdate()
    {
        for(int i=0; i< numPixels(); i++)
        {
            setPixelColor(i, Wheel(((i * 256 / numPixels()) + Index) & 255));
        }
        show();
        Increment();
    }
 
    // Initialize for a Theater Chase
    void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = THEATER_CHASE;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
   }
    
    // Update the Theater Chase Pattern
    void TheaterChaseUpdate()
    {
        for(int i=0; i< numPixels(); i++)
        {
            if ((i + Index) % 3 == 0)
            {
                setPixelColor(i, Color1);
            }
            else
            {
                setPixelColor(i, Color2);
            }
        }
        show();
        Increment();
    }
 
    // Initialize for a ColorWipe
    void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = COLOR_WIPE;
        Interval = interval;
        TotalSteps = numPixels();
        Color1 = color;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Color Wipe Pattern
    void ColorWipeUpdate()
    {
        setPixelColor(Index, Color1);
        show();
        Increment();
    }
    
    // Initialize for a SCANNNER
    void Scanner(uint32_t color1, uint8_t interval)
    {
        ActivePattern = SCANNER;
        Interval = interval;
        TotalSteps = (numPixels() - 1) * 2;
        Color1 = color1;
        Index = 0;
    }
 
    // Update the Scanner Pattern
    void ScannerUpdate()
    { 
        for (int i = 0; i < numPixels(); i++)
        {
            if (i == Index)  // Scan Pixel to the right
            {
                 setPixelColor(i, Color1);
            }
            else if (i == TotalSteps - Index) // Scan Pixel to the left
            {
                 setPixelColor(i, Color1);
            }
            else // Fading tail
            {
                 setPixelColor(i, DimColor(getPixelColor(i)));
            }
        }
        show();
        Increment();
    }
    
    // Initialize for a Fade
    void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD)
    {
        ActivePattern = FADE;
        Interval = interval;
        TotalSteps = steps;
        Color1 = color1;
        Color2 = color2;
        Index = 0;
        Direction = dir;
    }
    
    // Update the Fade Pattern
    void FadeUpdate()
    {
        // Calculate linear interpolation between Color1 and Color2
        // Optimise order of operations to minimize truncation error
        uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
        uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
        uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
        
        ColorSet(Color(red, green, blue));
        show();
        Increment();
    }
   
    // Calculate 50% dimmed version of a color (used by ScannerUpdate)
    uint32_t DimColor(uint32_t color)
    {
        // Shift R, G and B components one bit to the right
        uint32_t dimColor = Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
        return dimColor;
    }
 
    // Set all pixels to a color (synchronously)
    void ColorSet(uint32_t color)
    {
        for (int i = 0; i < numPixels(); i++)
        {
            setPixelColor(i, color);
        }
        show();
    }
 
    // Returns the Red component of a 32-bit color
    uint8_t Red(uint32_t color)
    {
        return (color >> 16) & 0xFF;
    }
 
    // Returns the Green component of a 32-bit color
    uint8_t Green(uint32_t color)
    {
        return (color >> 8) & 0xFF;
    }
 
    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color)
    {
        return color & 0xFF;
    }
    
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos)
    {
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85)
        {
            return Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        else if(WheelPos < 170)
        {
            WheelPos -= 85;
            return Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        else
        {
            WheelPos -= 170;
            return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
    }
}; 



void JewelComplete();
NeoPatterns Jewel(4, 6, NEO_GRB + NEO_KHZ800, &JewelComplete);
int breatheSpeed = 100;

*/
