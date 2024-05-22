
all: bootblock

bootblock: bootasm.S bootmain.c
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -I. -c bootmain.c -I../include
	$(CC) $(CFLAGS) -fno-pic -nostdinc -I. -c bootasm.S -I../include
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	$(OBJDUMP) -S bootblock.o > bootblock.asm
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	mv bootblock ..

clean:
	rm -rf *.o *.asm *.d
