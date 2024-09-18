#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

// f''(x) = f(x+h) -2f(x) + f(x-h) / dx²

double H(double *Psi, int i, int j , double dx, double dy,int N)
{
	double T, V;

	if(i>0 && i<N-1 && j>0 && j<N-1)
		T=(0.5)*((Psi[i+1+j*N] - 2*Psi[i+j*N] + Psi[i-1+j*N])/(dx*dx) +(Psi[i+(j+1)*N] -2*Psi[i+j*N] + Psi[i+(j-1)*N])/(dy*dy)); // energia cinetica
	
	V= (0.5)*(((i-N/2)*dx)*((i-N/2)*dx) + ((j-N/2)*dy)*((j-N/2)*dy));

	return (V-T);
}
