#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

double E_Total(double *El,double *dEt, double *dp, double dx, double dy, int N)
{
	int i,j,index;
	double ene=0;

	for(j=0;j<N;j++)
	{
		for(i=0;i<N;i++)
		{
			index= i +j*N;

			dEt[index] = dp[index]*El[index]*dx*dy;
			ene = ene + dEt[index];
		}
	}
	return ene;
}
