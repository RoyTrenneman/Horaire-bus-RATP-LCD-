/*
Raspberry Pi arduino i2c communication code.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include "smbus.h" 
#define ARDUINO_I2C_ADDRESS 0x08


// Open a connection to the Arduino 
// Returns a file id
int arduino_i2c_Begin()
{
   int fd = 0;
   char *fileName = "/dev/i2c-1";
   
   // Open port for reading and writing
   if ((fd = open(fileName, O_RDWR | O_NONBLOCK )) < 0)
      exit(1);
   
   // Set the port options and set the address of the device
   if (ioctl(fd, I2C_SLAVE, ARDUINO_I2C_ADDRESS) < 0) {               
      //close(fd);
      exit(1);
   }
  
   return fd;
 
}

// Read two words from the BMP085 and supply it as a 16 bit integer
__s32 arduino_i2c_Read_Int(int fd, __u8 address)
{
   __s32 res = i2c_smbus_read_word_data(fd, address);
   if (res < 0) {
      //close(fd);
      exit(1);
   }

   // Convert result to 16 bits and swap bytes
   res = ((res<<8) & 0xFF00) | ((res>>8) & 0xFF);

   return res;
}

//Write a byte to the Arduino 
void arduino_i2c_Write_Byte(int fd, __u8 value)
{
   if (i2c_smbus_write_byte(fd, value) < 0) {
     //close(fd);
      exit(1);
   }
}

void arduino_send_word(int fd, __u8 command, __u8 value)
{
i2c_smbus_write_byte_data(fd , command, value);
}

void arduino_send_byte(int fd, __u8 value)
{
i2c_smbus_write_byte(fd, value & 0xFF);
}

