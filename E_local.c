#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void E_local(double *Psi,double *El,double dx,double dy, int N)
{
	int i,j;

	for(j=1;j<N;j++)
			for(i=1;i<N;i++)
				El[i+j*N]= H(Psi,i,j,dx,dy,N)/(Psi[i+j*N]+0.0001);
}
