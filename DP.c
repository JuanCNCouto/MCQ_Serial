#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void Calc_DP(double *dp,double *Psi, double A,int N)
{
	int i,j;

	for(i=1;i<N-1;i++)
		for(j=1;j<N-1;j++)
			dp[i+j*N] = (Psi[i+j*N]*Psi[i+j*N]);

}
