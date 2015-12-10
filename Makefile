# Makefile:
#
#	Make the program on the Raspberry Pi
#
###############################################################################

#DEBUG	= -g -O0
DEBUG	= -O2
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -g -Wall -lm $(INCLUDE) -Winline -pipe 

LDFLAGS	= -L/usr/local/lib
LIBS    = -lm -lpthread -lwiringPi 

SRC	= $(wildcard *.c)

# May not need to  alter anything below this line
###############################################################################

OBJ	=	$(SRC:.c=.o)
BINS	=	$(SRC:.c=)


WaitingTime:	main.o smbus.o arduino.o 
	@echo [link]
	@$(CC) -o $@ main.o smbus.o arduino.o $(LDFLAGS) $(LIBS)

arduino.o: arduino.h

.c.o:	
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

.PHONEY:	clean
clean:
	rm -f $(OBJ) $(BINS) *~ core tags *.bak

.PHONEY:	tags
tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

.PHONEY:	depend
depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
