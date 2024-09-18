#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void MCQ(double *Psi, double *dp,double *dEt, double *El, double *Et, double A,double *dA,double dx,double dy, int N)
{

	double nPsi,auxA,ndp,auxE,nEl1[3],nEl2[3];
	int i[2],j[2],r,cont =1,c,index;
	long int tc=0;
	FILE *arq;
	i[0]= rand()%(N-2);
	j[0]=rand()%(N-2);
	
	do{
		if(cont>1) Et[0]=Et[1]; 
		//algoritmo de metropoles
		i[1]=( i[0] + (int) (( rand() -0.5)/2))%N; /* range entre [1,N-1] */
		j[1]=( j[0] + (int) (( rand() -0.5)/2)%N); // para os valores sorteados para o valor nas bordas nao serem alterados		   
		if( (j[1]>0) && (i[1]>0) && (i[1]<N-1) && (j[1]<N-1) ) // se os valores sorteados nao é a borda
		{
			auxE= Et[0];
			nPsi= rand()%1000+0.001; // Psi deve ser diferente zero fora das bordas pois se nao da ruim quando calcular a energia local El= H^Psi/Psii
			auxA= A - dA[i[1]+j[1]*N] + nPsi*nPsi*dx*dy; //valor provisorio da nova constante de normalização
			ndp= (nPsi*nPsi)/auxA; // valor novo da densidade de probabilidade no ponto alterado
			r= rand();	// terceiro numero aleatorio
			
			
			if( (ndp/dp[ i[1]+ j[1]*N ]) >= r) // condição de aceitação do novo valor
			{
				//calcula energia local e dEt, e calculo energia total - MODIFICADO
				index=0;
				for(c=i[1]-1; c <= i[1] +1 ;c++)
				{
					if(c!=0 && c!=(N-1))
					{

						nEl1[ index ] = H(Psi,c,j[1],dx,dy,N)/(Psi[c + j[1]*N]);
						auxE= auxE - dEt[ c + j[1]*N]; //E0 - old_dEt
						printf("auxE1= %g ",auxE);
						auxE = (c==i[1]) ? (auxE + ndp*nEl1[index]*dx*dy  ) : (dp[c +j[1]*N]*nEl1[index]*dx*dy ); // E0 + new_dEt
						printf("El= %g dEt= %g auxE2= %g\n",El[c+j[1]*N],dEt[c+j[1]*N],auxE);
					}
					index= index +1;
				}	
				index=0;
				for(c= j[1] -1;c<=j[1]+1 ;c++)
				{
					if(c!=0 && c!=(N-1))
					{
						nEl2[ index ] = H(Psi,i[1],c,dx,dy,N)/(Psi[ i[1] + c*N]);
						auxE= auxE - dEt[ i[1] + c*N];
						printf("auxE1= %g ",auxE);
						
						auxE = (c==j[1]) ? (auxE + ndp*nEl1[index]*dx*dy  ) : (dp[i[1] +c*N]*nEl1[index]*dx*dy );
						printf("El= %g dEt= %g auxE2= %g\n",El[c+j[1]*N],dEt[c+j[1]*N],auxE);
					}
					index= index +1;
				}
				//calcula nova energia total
				
				if(auxE<Et[0]) //se a energia diminuir, atualiza os valores
				{
					index=0;
					dp=ndp
					Psi[ i[1] + j[1]*N ] = nPsi;
					A= auxA;
					dp[ i[1] + j[1]*N ] = ndp;
					printf(" passo 3 -(x,y)= (%d,%d) t=%ld nPsi=%g ndp=%g auxA=%g\n",i[1],j[1],tc,nPsi,ndp,auxA);
					for(c=i[1]-1; c <= i[1] +1 ;c++)
					{
						if(c=!0 && c!=(N-1))
						{
							El[ c + j[1]*N ] =nEl1[index];
							dEt[ c + j[1]*N] = dp[c +j[1]*N]*El[c + j[1]*N]*dx*dy;
						}
						index=index+1;
					}
					index= 0;
					for(c=j[1]-1;c<j[1]+1;c++)
					{
						if(c!=0 && c!=(N-1))
						{
							El[ c + j[1]*N ] =nEl1[index];
							dEt[ c + j[1]*N] = dp[c +j[1]*N]*El[c + j[1]*N]*dx*dy;
						}
						index= index+1;
					}
					Et[1]= auxE;
					printf("cont = %d tc=%ld E[0]= %g E[1]= %g auxE = %g difE= %g\n",cont,tc,Et[0],Et[1],auxE,Et[0]-Et[1]);
				}
				i[0] = i[1]; // guarda a informação da posição
				j[0] = j[1]; // para realizar o alg de metropolis denovo
				cont = cont +1;
			}
			else if(i[1]<0 && j[1]<0)
			{
				i[0]=(-1)*i[1]%N;
				j[0]= (-1)*j[1]%N;
				printf("erro");
			
			}	

			tc=tc+1;
		}	
	}while(fabs(Et[0])-fabs(Et[1]) >0.1 || tc <1e+16 );
	printf("valor da energia total = %g\n",Et[1]);
	printf("dif das energias = %g\n",Et[1] - Et[0] );
	//fclose(arq);
}
