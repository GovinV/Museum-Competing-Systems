/**
 * @file controleur.c
 * @author Govindaraj VETRIVEL
 */

#include "musee.h"

void usage()
{
	printf("usage: ./controleur\n");
	printf("usage: sans arguments\n");
}

int main(int argv, char * argc[])
{
	int shmid,debug,semid;
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
	
	Po(semid);
	s->contro_act=1;
	if(debug>0)
		affiche_debug("Musée Ouvert\n");
	while(s->ouvert == 1) 
	{
		if(debug>1)
			affiche_debug("J'attends un visiteur\n");
		Pva(semid);
		if(debug>1)
			affiche_debug("J'attends une place dans le musée\n");		
		Pe(semid);
		if(s->ouvert == 1)
		{
			Pmcc(semid);
			if(s->capacite_cur < s->capacite)
			{
				s->capacite_cur++;
				Vmcc(semid);
				Vev(semid);					
				Pmfc(semid);
				s->file_cur--;
				Vmfc(semid);
				if(debug>0)
					affiche_debug("je laisse passer un visiteur\n");
			}
			else
				Vmcc(semid);

		}
	}
	if(debug>0)
		affiche_debug("Musée fermé\n");
	s->contro_act=0;	
	
	if(s->capacite_cur!=0)
		Pdv(semid);

	if(debug>0)
		affiche_debug("Fin de mon travail\n");
	
	return 0;
}