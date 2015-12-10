#include <Adafruit_RGBLCDShield.h>
#include <Wire.h>
#include <VirtualWire.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7
#define OFF 0x0

uint8_t min[VW_MAX_MESSAGE_LEN] ;
unsigned char old;

// RECEIVER CODE

void setup()
{
//LCD
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.setBacklight(TEAL);
Serial.begin(9600); // Debugging only

// RF433
pinMode(9, OUTPUT);
digitalWrite(9, HIGH);
// Initialise the IO and ISR
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000);  // Bits per sec
vw_set_rx_pin(2);
vw_rx_start();       // Start the receiver PLL running


}

void loop()
{

//////////////BUTTONS//////////////////

uint8_t buttons = lcd.readButtons();
  if (buttons) {
    if (buttons & BUTTON_UP) {
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_DOWN) {
      lcd.setBacklight(OFF);
    }
  }
/////////////RF433////////////////////

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

/////////////Bus min buf[1]////////////////
     
     if (old != buf[1])
      {
      lcd.clear();
      lcd.print("Prochain bus 187");
      lcd.setCursor(0,1);
      if (buf[1] == 200)
       {
       lcd.print("A l'arret");
       old = buf[1];
       }
       else if(buf[1] == 201)
       {
       lcd.print("A l'approche");
       old = buf[1];
       }
       else
       {
       lcd.print((buf[1]),DEC);
       Serial.println(buf[1], DEC);
       lcd.setCursor(3,1);
       lcd.print("min");
       old = buf[1];
       }
     }
    delay (10) ;
} 
