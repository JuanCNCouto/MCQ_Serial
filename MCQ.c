#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void MCQ(double *Psi, double *dp,double *dEt, double *El, double *Et, double A,double *dA,double dx,double dy, int N)
{

	double *nPsi,r,*ndA,*ndp,*ndEt,*nEl,auxA,auxE,difE=1,auxr;
	int i[2],j[2],cont =0,c,index,aux=0;
	long int tc=0;
	FILE *arq;
	i[0]= rand()%(N-2);
	j[0]=rand()%(N-2);
	arq=fopen("./saida/saida.txt","w");
	ndp= (double *)calloc((N*N),sizeof(double));
	nPsi=(double *)calloc((N*N),sizeof(double));
	ndEt= (double *)calloc((N*N),sizeof(double));
	nEl = (double *)calloc((N*N),sizeof(double));
	ndA = (double *)calloc((N*N),sizeof(double));
	for(index=0;index<N*N;index++)
	{
		nPsi[index]= Psi[index];
		ndp[index]= dp[index];
		ndEt[index]= dEt[index];
		nEl[index]= El[index];
		ndA[index]= dA[index];
	}
	while(aux==0){
		 
		//algoritmo de metropoles
		i[1]=( i[0] + (int) (( rand() -0.5)/2))%N; /* range entre [1,N-1] */
		j[1]=( j[0] + (int) (( rand() -0.5)/2))%N;	// para os valores sorteados para o valor nas bordas nao serem alterados
				   
		if( (j[1]>0) && (i[1]>0) && (i[1]<N-1) && (j[1]<N-1) ) // se os valores sorteados nao é a borda
		{
			auxr= rand()%1000;
			nPsi[i[1]+j[1]*N]= (auxr)/1000.0 ; // Psi deve ser diferente zero fora das bordas pois se nao da ruim quando calcular a energia local El= H^Psi/Psii
			auxA= Normalizacao(nPsi,ndA,dx,dy,N);
			Calc_DP(ndp,nPsi,A,N);
			auxr=rand()%1000;
			r= (auxr)/1000.0 ;
			
			if( (ndp[i[1]+j[1]*N] /dp[ i[1]+ j[1]*N ]) >= r ) // condição de aceitação do novo valor
			{
				
				E_local(nPsi,nEl,dx,dy,N);
				Et[1] = E_Total(nEl,ndEt,ndp,dx,dy,N);

				if(fabs(Et[1])<fabs(Et[0])) //se a energia diminuir, atualiza os valores
				{
					
					difE= fabs(Et[0])-fabs(Et[1]);
							
					i[0] = i[1]; // guarda a informação da posição
					j[0] = j[1]; // para realizar o alg de metropolis denovo
					for(index=0;index<N*N;index++)
					{
						Psi[index]=nPsi[index];
						dp[index]=ndp[index];
						El[index]=nEl[index];
						dEt[index]=ndEt[index];
					}
					if(cont%(N*N)==0)
						save(Psi,dp,El,dx,dy,cont,N);
					
					fprintf(arq,"%ld %d %g %g\n",tc,cont,Et[1],difE);
					Et[0]=Et[1];
					cont= cont +1;	
				}
				else{
					for(index=0;index<N*N;index++)
					{
						nPsi[index]=Psi[index];
						ndp[index]=dp[index];
						nEl[index]=El[index];
						ndEt[index]=dEt[index];
					}
				}
			}
			else if(i[1]<0 && j[1]<0)
			{
				i[0]=(-1)*i[1]%N;
				j[0]= (-1)*j[1]%N;
				printf("erro");
			
			}	

		}
		tc=tc+1;	
		if(difE < 1e-10 || cont > 1e+10 || tc >1e+15) aux=1;
	}
	fclose(arq);
	free(nPsi);
	free(nEl);
	free(ndp);
	free(ndEt);
	free(ndA);
	//fclose(arq);
}
