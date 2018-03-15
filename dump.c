/**
 * @file dump.c
 * @author Govindaraj VETRIVEL
 */


#include "musee.h"

void usage()
{
	printf("usage: ./dump\n");
	printf("usage: sans arguments\n");
}

int main(int argv, char * argc[])
{
	int debug,shmid,semid,i;
	mus * s;

	if(argv !=1)
	{
		usage();
		printf("%s inutile.\n",argc[1]);
		exit(1);
	}

	debug=getEnvDebug();
	
	shmid = recup_shm();
	s = shmat(shmid, 0, 0);
	semid=s->id_sema;

	if(debug>0)
	{
		printf("Segments De Mémoire Partagée:\n");
		printf("\t Capacité maximum: %d\n", s->capacite);
		printf("\t Capacité courante: %d\n", s->capacite_cur);
		printf("\t Musée ouvert: %d\n", s->file);
		printf("\t Taille de la file d'attente: %d\n", s->file_cur);
		printf("\t Taille  courante de la file d'attente: %d\n", s->ouvert);
		printf("\t Id de la Sémaphore: %d\n",s->id_sema );
		printf("\t Contrôleur active: %d\n", s->contro_act);
		fflush(stdout);

		printf("Sémaphore:\n");
		for(i=0;i<7;i++)
			printf("\t Valeur de la sémaphore %d: %d\n",i,semctl(semid,i,GETVAL,0));
		fflush(stdout);

	}


	return 0;
}

