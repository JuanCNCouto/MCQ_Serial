#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

int main()
{
	double aux=0.0, *Psi,Et[2],*dEt,*El,*dp,A,*dA,dx,dy,L=1.00;
	int i,j,N=100;	

	srand(time(NULL));

	dx= dy = (2*L)/N; // defini o valor da discretização do espaço

	printf("N= %d dx=dy = %g L= %g\n",N,dx,L);

	// cria as matrizes para realizar os calculos
	Psi= (double *)calloc((N*N),sizeof(double)); 
	El = (double*)calloc((N*N),sizeof(double));
	dp = (double *)calloc((N*N),sizeof(double));
	dEt= (double *)calloc((N*N),sizeof(double));
	dA= (double *)calloc((N*N),sizeof(double));

	printf("Passo 1 -criação de matrizes feito\n");

	DA(Psi,N); // atribui valores aleatorios para Psi
	
	printf("passo 2 - atribuição de valores a Psi- feito\n");
	A= Normalizacao(Psi,dA,dx,dy,N); // calcula o valor da constante de normalização e normaliza Psi

	printf("Passo 3 -Normalização feito\nA=%g\n",A);
	E_local(Psi,El,dx,dy,N); // calcula o valor da energia local para cada ponto da malha
	printf("passo 4- energia local calculado\n");
	Calc_DP(dp,Psi,A,N); // calcula a densidade de probabilidade 
	for(i=0;i<N*N;i++)
		aux= aux + dp[i]*dx*dy ;
	printf("aux=%g\n",aux);
	printf("passo 5 feito \n\n");
	Et[0]=E_Total(El,dEt,dp,dx,dy,N);

				// calcula o valor da energia total do sistema
	printf("energia total passo 1 = %g\n ", Et[0]);
	save(Psi,dp,El,dx,dy,0,N);
	printf("passo 6 feito\n\n");
	MCQ(Psi,dp,dEt,El,Et,A,dA,dx,dy,N);
       	// função onde realiza o metodo de monte carlo variacional
	printf("metodo acabou\n\n");
	save(Psi,dp,El,dx,dy,1,N);
	printf("energia final = %g",Et[1]);
	free(Psi);
	free(El);
	free(dp);
	free(dEt);
	free(dA);
}
