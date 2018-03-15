/**
 * @file directeur.c
 * @author Govindaraj VETRIVEL
 */

#include "musee.h"

void usage()
{
	printf("usage: ./directeur creer/ouvrir/fermer/supprimer\n");
	printf("usage: ./directeur creer capacite file\n");
	printf("usage: capacite et file étant positif\n");
	printf("usage: pas d'arguments en plus pour les trois autres\n");
}

int main(int argv, char * argc[])
{
	int r;
	char arg='a';
	int capacite;
	int file;
	int shmid;
	int semid;
	int debug;
	mus * s;
	
	if(argv < 2)
	{
		usage();
		exit(1);
	}
	if(argv==4)
	{
		r=strncmp(argc[1], "creer", 5);
		if(r==0)
		{
			if(argv!=4)
			{
				usage();
				exit(1);
			}
			arg='c';
		}
	}
	else if(argv==2)
	{
		r=strncmp(argc[1], "ouvrir", 6);
		if(r==0)
		{
			arg='o';
		}
		
		r=strncmp(argc[1], "fermer", 6);
		if(r==0)
		{
			arg='f';
		}
		
		r=strncmp(argc[1], "supprimer", 9);
		if(r==0)
		{
			arg='s';
		}
	}

	debug=getEnvDebug();

	switch(arg)
	{
		case 'c':
			capacite=atoi(argc[2]);
			file=atoi(argc[3]);
			if(capacite<=0 || file<0)
			{
				usage();
				exit(1);
			}

			if(debug>0)
				affiche_debug("Directeur crée le musée\n");

			shmid=creer_shm();
			s = shmat(shmid, NULL, 0);
			s->capacite=capacite;
			s->capacite_cur=0;
			s->file=file;
			s->file_cur=0;
			s->ouvert=0;//musee ferme
			s->contro_act=0;
			s->id_sema=init_semaphore();
			semid=s->id_sema;
			init_val_semaphore(semid,capacite);
			break;
		
		case 'o':
			if(debug>0)
				affiche_debug("Directeur ouvre le musée\n");
			shmid=recup_shm();
			s = shmat(shmid, NULL, 0);
			s->ouvert=1;/* Vouver(semid) */
			semid=s->id_sema;
			Vo(semid);
			if(debug>1)
				affiche_debug("On laisse le contrôleur travailler avec Vo\n");
			break;
			
		case 'f':
			if(debug>0)
				affiche_debug("Directeur ferme le musée\n");
			shmid=recup_shm();
			s = shmat(shmid, NULL, 0);
			s->ouvert=0;
			if(s->contro_act==1 && s->file_cur==0)
			{
				Vva(s->id_sema);
				if(debug>1)
					affiche_debug("On débloque le contrôleur avec Vva\n");
			}	
			if(s->contro_act==1 && s->file_cur==0 && s->capacite_cur==0)
			{
				Ve(s->id_sema);
				if(debug>1)
					affiche_debug("On débloque le contrôleur avec Vva\n");
			}	
			break;
		
		case 's':
			if(debug>0)
				affiche_debug("Directeur supprime le musée\n");
			shmid=recup_shm();
			s = shmat(shmid, NULL, 0);
			supprimer_semaphore(s->id_sema);
			supprimer_shm(shmid);
			break;
			
		default:
			usage();
			exit(1);
		
	}
	
	return 0;
}
	
	
	
	
