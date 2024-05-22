ULIB = ulib.o usys.o printf.o umalloc.o

all: mkfs $(ULIB)
	mv mkfs ..
	mv ${ULIB} ..

%.o: %.c
	$(CC) $(CFLAGS) -nostdinc -I../include -c $^ -I../include

%.o: %.S
	$(CC) $(CFLAGS) -nostdinc -I../include -c $^ -I../include

mkfs: mkfs.c
	gcc -Werror -Wall -o mkfs mkfs.c

clean:
	rm -rf *.d
