#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t crimson = strip.Color(125,5,5);
uint32_t gold = strip.Color(215,150,15);
int buttonPin = 13;
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin, HIGH);
  strip.begin();
  strip.setBrightness(64);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  alternatingColorStatic(crimson, gold);
  if (digitalRead(buttonPin) == LOW){
    applause();
  }
  delay(100);
}

void alternatingColorStatic(uint32_t color1, uint32_t color2) {
  for (int i=0; i<strip.numPixels(); i++){
    if (i%2 == 0){
      strip.setPixelColor(i, color1);
    }
    else {
      strip.setPixelColor(i, color2);
    }
  }
  strip.show();
}

void off_all(){
  for (int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0);
  }
  strip.show();
}


void applause(){
 for (int i=0; i<30; i++){
   alternatingColorStatic(crimson,gold);
   delay(75);
   off_all();
   delay(75);
 }
}


