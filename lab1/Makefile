NAME = toty-tran
CARTE = 502x

CROSS_COMPILE ?= bcm2708hardfp-

CFLAGS=-Wall -Wfatal-errors -O2
LDFLAGS=-static -L. -lgpio
LDFLAGS=-static  

all: lab1_ex1.x helloworld.x

helloworld.x: helloworld.c
	bcm2708hardfp-gcc -o $@ $< -O2 -static

copy: *.x
	scp $^ -P $(CARTE) pi@132.227.102.36:$(NAME)

%.x: %.c
	$(CROSS_COMPILE)gcc -o $@ $^ $(LDFLAGS)

libgpio.a: gpio_read.o gpio_config.o gpio_setup.o gpio_write.o
	$(CROSS_COMPILE)ar -rcs $@ $^

%.o: %.c
	$(CROSS_COMPILE)gcc -o $@ -c $(CFLAGS) $<

clean:
	rm -f *.o *.x *~

distclean: clean
	rm -f *.a

