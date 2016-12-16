# -------------- #
# -- Makefile -- #
# -------------- #

OBJ    = main.o acceleroNR.o filterNR.o gauss.o noise.o nrutil.o random.o sampleNR.o test_acceleroNR.o
HEADER = def.h  acceleroNR.h filterNR.h gauss.h noise.h nrutil.h random.h sampleNR.h test_acceleroNR.h

#OPTION = -Wunused-parameter -W\\#pragma-messages 

OPTION = -Wno-unused-parameter -Wno-comment -std=c99

tp: $(OBJ) $(HEADER)
	gcc -o tp $(OBJ) -lm

filterNR.o: filterNR.c $(HEADER)
	gcc -c $(OPTION) filterNR.c

gauss.o: gauss.c $(HEADER)
	gcc -c $(OPTION) gauss.c

main.o: main.c $(HEADER)
	gcc -c $(OPTION) main.c

noise.o: noise.c $(HEADER)
	gcc -c $(OPTION) noise.c

nrutil.o: nrutil.c $(HEADER)
	gcc -c $(OPTION) nrutil.c

random.o: random.c $(HEADER)
	gcc -c $(OPTION) random.c

sampleNR.o: sampleNR.c $(HEADER)
	gcc -c $(OPTION) sampleNR.c

acceleroNR.o: acceleroNR.c $(HEADER)
	gcc -c $(OPTION) acceleroNR.c

test_acceleroNR.o: test_acceleroNR.c $(HEADER)
	gcc -c $(OPTION) test_acceleroNR.c

clean:
	rm -f $(OBJ)
	rm -f tp
