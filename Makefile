
CFLAGS =test.c

obj-m := sample.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/bulid M=$(PWD) cleam
