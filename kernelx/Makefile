OBJS = \
	bio.o\
	console.o\
	exec.o\
	file.o\
	fs.o\
	ide.o\
	ioapic.o\
	kalloc.o\
	kbd.o\
	lapic.o\
	log.o\
	main.o\
	mp.o\
	picirq.o\
	pipe.o\
	proc.o\
	sleeplock.o\
	spinlock.o\
	string.o\
	swtch.o\
	syscall.o\
	sysfile.o\
	sysproc.o\
	trapasm.o\
	trap.o\
	uart.o\
	vectors.o\
	vm.o\

all: entryother initcode kernel
	mv entryother ..
	mv initcode ..
	mv kernel ..

%.o: %.S
	$(CC) $(CFLAGS) -nostdinc -I. -I../include -c $^

%.o: %.c
	$(CC) $(CFLAGS) -nostdinc -I. -I../include -c $^

tags: $(OBJS) entryother.S _init
	etags *.S *.c

vectors.S: vectors.pl
	./vectors.pl > vectors.S

entryother: entryother.S
	$(CC) $(CFLAGS) -fno-pic -nostdinc -I. -I../include -c entryother.S 
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7000 -o bootblockother.o entryother.o
	$(OBJCOPY) -S -O binary -j .text bootblockother.o entryother
	$(OBJDUMP) -S bootblockother.o > entryother.asm

initcode: initcode.S
	$(CC) $(CFLAGS) -nostdinc -I. -I../include -c initcode.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0 -o initcode.out initcode.o
	$(OBJCOPY) -S -O binary initcode.out initcode
	$(OBJDUMP) -S initcode.o > initcode.asm

kernel: $(OBJS) entry.o entryother initcode kernel.ld
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel entry.o $(OBJS) -b binary initcode entryother
	$(OBJDUMP) -S kernel > kernel.asm
	$(OBJDUMP) -t kernel | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > kernel.sym

clean:
	rm -f *.o *.d *.asm _* *.sym initcode.out vectors.S
