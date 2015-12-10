 /* TRANSMITTER CODE */

// LIB
#include <VirtualWire.h>
#include <Wire.h>

//Virtual REGISTER
#define BUSTIME 0xAA
#define RER 0XAB
 
//GLOBALES
volatile unsigned int x;
char msg[7];

void setup()
{
//I2C communication
Wire.begin(8);                // join i2c bus with address #8
Wire.onReceive(receiveEvent); // register event

//SERIAL PRINT
Serial.begin(9600);    // Debugging only
//Serial.println("setup");

// RF433
// Initialise the IO and ISR
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000);  // Bits per sec
vw_set_tx_pin(3);

}

void loop()
{
// Send msg[] through RF433
vw_send((uint8_t *)msg, strlen(msg));
vw_wait_tx(); // Wait until the whole message is gone
delay(100);
}

void receiveEvent(int howMany) {
int i ;
 if(Wire.available() && (howMany == 2)){
  x = Wire.read();
  if (x == BUSTIME){
  msg[1] = Wire.read();
  }
  else {
  int i = Wire.read(); // Dump buffer
  }
 }
  else { //loop for dumping buffer otherwize arduino will wait indefinitely
  while (0 < Wire.available()) {
  int i = Wire.read(); // Dump buffer
  //Serial.println("DUMPING BUFFER: ") ; //debugging only
  //Serial.print(howMany);     
  //Serial.println(" ") ;    
  //Serial.print(i, HEX);
  //Serial.println(" ") ;
  exit ;
  } 
 }
}
/* END TRANSMITTER CODE */

