//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio,*fir;

int main() {

	
	unsigned char chi;
	int *io,*ir;
	long int k=3,s=1,nbg;
	register long int i,j;
	long int dimx,dimy,taille;
	char entree[35],sortie[35],chaine[10];

	printf("donner entree sans .pgm\n");
	scanf("%s",entree);
	strcat(entree,".pgm");

	printf("donner sortie sans .pgm\n");
	scanf("%s",sortie);
	strcat(sortie,".pgm");

	fio=fopen(entree,"rb");
	fir=fopen(sortie,"wb+");

	if(fio !=NULL) printf("ouverture du fichier in\n");
	if(fir !=NULL) printf("ouverture du fichier out\n");

	//lecture entete pgm
	fscanf(fio,"%s\n",chaine);
	fprintf(fir,"%s\n",chaine);

	i=0;
	while(i<1) 
	{
		chi=fgetc(fio);
		fputc(chi,fir);
		if(chi=='\n') i++;
	}

	fscanf(fio,"%ld %ld\n",&dimx,&dimy);
	fprintf(fir,"%ld %ld\n",dimx,dimy);

	fscanf(fio,"%d\n",&nbg);
	fprintf(fir,"%d\n",nbg);

	printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

	//allocation dynamique de m�moire des images io et ir
	io=(int *)malloc(dimx*dimy*sizeof(int));
	ir=(int *)malloc(dimx*dimy*sizeof(int));
	if(ir==NULL) printf("allocation ir impossible\n");

	taille=dimx*dimy;
	printf("taille=%ld\n",taille);

	//lecture des pixels
	for(i=0;i<dimy;i++)
		for(j=0;j<dimx;j++) 
		{
			chi=(unsigned char)fgetc(fio);
			io[i*dimx+j]=(int)chi;
		}


	///////////////////////////////////////////////////////////////////
	//TRAITEMENT
	for(i=0;i<dimy;i++)
		for(j=0;j<dimx;j++)
			ir[i*dimx+j]=255-io[i*dimx+j];
	//FIN TRAITEMENT
	///////////////////////////////////////////////////////////////////
	
	//Sauvegarde de l image r�sultat dans le fichier fir
	for(i=0;i<dimy;i++)
		for(j=0;j<dimx;j++)
			fputc((unsigned char)ir[i*dimx+j],fir);

	//lib�ration de de la m�moire des tableaux io et ir et fermeture des 2 fichiers fio et fir
	free(io); free(ir);
	fclose(fio); fclose(fir);
	return 0;
}
