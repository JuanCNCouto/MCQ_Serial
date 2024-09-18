#include <stdio.h>
#include "bibliotecas.h"
#include "funcoes.h"

void save(double *Psi,double *dp, double *El,double dx,double dy, int k,int N) 
{
	  int i, j;
	  FILE *APsi,*Adp,*AEl;
	  char cPsi[100],cadp[100],cEl[100];
	  snprintf(cPsi, sizeof(cPsi), "./saida/Psi/Psi-%d.dat", k);
	  snprintf(cadp, sizeof(cadp), "./saida/dp/dp-%d.dat", k);
	  snprintf(cEl, sizeof(cEl), "./saida/El/El-%d.dat", k);
	  APsi= fopen(cPsi,"w");
	  Adp= fopen(cadp,"w");
	  AEl= fopen(cEl,"w");
	  for (j = 0; j < N; j++) {
		  for (i = 0; i < N; i++) {
			  fprintf(APsi, "%g %g %g\n ",(i-N/2)*dx,(j-N/2)*dy, Psi[i+j*N]);
			 // fprintf(APsi, \n);
			  fprintf(AEl, "%g %g %g\n ",(i-N/2)*dx,(j-N/2)*dy, El[i+j*N]);
			 // fprintf(AEl,\n);
			  fprintf(Adp, "%g %g %g\n ",(i-N/2)*dx,(j-N/2)*dy, dp[i+j*N]);
			 /* fprintf(Adp, n);*/
			}
	  }
	  fclose(APsi);
	  fclose(Adp);
	  fclose(AEl);
}
