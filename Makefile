MCU = atmega128
INCLUDE=-I/usr/avr/include
CC =avr-gcc
CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) -Os
LDFLAGS=-Wl,-gc-sections -Wl,-relax


all:main.hex


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<


main.elf: waitDelay.o printNumber.o main.o
	$(CC) $(CFLAGS) -o $@  $^

main.hex: main.elf
	 avr-objcopy -j .text -j .data -O ihex  $^  $@

.PHONY: clean

clean:
	rm -rf *.o main.elf main.hex

.PHONY: program

program: main.hex
	 sudo avrdude -c stk500v2 -p m128 -P avrdoper -U flash:w:main.hex:a
