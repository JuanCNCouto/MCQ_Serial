#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void DA(double *Psi, int N)
{
	int i,j;
	double aux;
	for(j=1;j<N-1;j++) //condição de dirichlet, nas bordas tem que ser zero
	{
		for(i=1;i<N-1;i++)
		{
			aux= rand()%1000;
			Psi[i+j*N]= (aux)/1000.0 ;
	
		}
	}
}
