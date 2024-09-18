#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

double Normalizacao(double *Psi,double *dA, double dx, double dy,int N)
{
	int i,j;
	double norm=0;
	for(j=1;j<N-1;j++)
	{
		for(i=1;i<N-1;i++)
		{
			dA[i+j*N] = Psi[i+j*N]*Psi[i+j*N]*dx*dy;
			norm = norm + dA[i+j*N]; //A²
	
		}
	}
	norm= sqrt(norm);
	for(i=0;i<N*N;i++) Psi[i] = Psi[i]/norm;
	return norm;
}
