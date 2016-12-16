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
	gcc -c $(OPTION) filterNR.c -lm

gauss.o: gauss.c $(HEADER)
	gcc -c $(OPTION) gauss.c -lm

main.o: main.c $(HEADER)
	gcc -c $(OPTION) main.c -lm

noise.o: noise.c $(HEADER)
	gcc -c $(OPTION) noise.c -lm

nrutil.o: nrutil.c $(HEADER)
	gcc -c $(OPTION) nrutil.c -lm

random.o: random.c $(HEADER)
	gcc -c $(OPTION) random.c -lm

sampleNR.o: sampleNR.c $(HEADER)
	gcc -c $(OPTION) sampleNR.c -lm

acceleroNR.o: acceleroNR.c $(HEADER)
	gcc -c $(OPTION) acceleroNR.c -lm

test_acceleroNR.o: test_acceleroNR.c $(HEADER)
	gcc -c $(OPTION) test_acceleroNR.c -lm

clean:
	rm -f $(OBJ)
	rm -f tp
