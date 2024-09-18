C=gcc
CFLAGS= -I. -lm -O2 -fexpensive-optimizations -m64 -foptimize-register-move -funroll-loops -ffast-math -pg -g 
#CFLAGS= -I. -O3 -mtune=corei7-avx -pg -g  -lm
DEPS= DA.h DP.h E_Total.h E_local.h Ham.h MCQ.h Norm.h Salvar_matriz.h main.h
	 
Mcq : DA.o DP.o E_Total.o E_local.o Ham.o MCQ.o Norm.o Salvar_matriz.o main.o
		$(CC) $(CFLAGS) -o Mcq DA.o DP.o E_Total.o E_local.o Ham.o MCQ.o Norm.o Salvar_matriz.o main.o

.PHONY:clean

clean:
		rm -fr ./*.o ./Mcq
		rm -fr ./saida/Psi/*.dat
		rm -fr ./saida/El/*.dat
		rm -fr ./saida/dp/*.dat
		rm -fr ./saida/*.txt
