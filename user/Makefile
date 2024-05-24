.PRECIOUS: %.o

UPROGS=\
	_cat\
	_echo\
	_forktest\
	_grep\
	_init\
	_kill\
	_ln\
	_ls\
	_mkdir\
	_rm\
	_sh\
	_stressfs\
	_usertests\
	_wc\
	_zombie\
	_sleep\
	_pingpong\
	_primes\

ULIB = ../ulib.o ../usys.o ../printf.o ../umalloc.o

all: $(UPROGS) _forktest 
	echo "This: " $(UPROGS)
	../mkfs fs.img $(UPROGS)
	mv fs.img ..

%.o: %.c
	$(CC) $(CFLAGS) -nostdinc -I. -c $^ -I../include

_%: %.o
	$(LD) $(LDFLAGS) -N -e main -Ttext 0 -o $@ $^ $(ULIB)
	$(OBJDUMP) -S $@ > $*.asm
	$(OBJDUMP) -t $@ | sed '1,/SYMBOL TABLE/d; s/ .* / /; /^$$/d' > $*.sym

_forktest: forktest.o
	$(LD) $(LDFLAGS) -N -e main -Ttext 0 -o _forktest forktest.o ../ulib.o ../usys.o
	$(OBJDUMP) -S _forktest > forktest.asm

clean:
	rm -f *.o *.d *.asm _* *.sym
