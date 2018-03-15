/**
 * @file visiteur.c
 * @author Govindaraj VETRIVEL
 */

#include "musee.h"

int debug;

void usage()
{
	affiche_debug("usage: ./visiteur temps\n");
	affiche_debug("usage: temps en milli-secondes et donc positif\n");	
}

void je_visite_mus(float tps)
{
	if(debug>0)
		affiche_debug("je commence la visite\n");
	sleep(tps);
	if(debug>1)
	{
		printf("Et je suis resté %f milli-secondes\n",tps);
		fflush(stdout);
	}
}


int main(int argv, char * argc[])
{
	int shmid,semid;
	mus * s;
	float temps;

	if(argv !=2)
	{
		usage();
		exit(1);
	}
	
	temps=atof(argc[1])/1000;
	if(temps<0)
	{
		usage();
		exit(1);
	}
	debug=getEnvDebug();

	shmid = recup_shm();
	s = shmat(shmid, 0, 0);
	semid=s->id_sema;
	
	Pmfc(semid);
	if(s->file_cur >= s->file)
	{
		Vmfc(semid);
		exit(0);
	}
	s->file_cur++;
	
	Vmfc(semid);
	Vva(semid);
	
	if(debug>0)
		affiche_debug("Visiteur attends devant le musée\n");
	Pev(semid);//puis-je entre dans le musee
	
	je_visite_mus(temps);
	if(debug>0)
		affiche_debug("je finis la visite\n");

	Pmcc(semid);
	s->capacite_cur--;
	if(s->capacite_cur==0 && s->contro_act==0)
	{
		Vdv(semid);
		Ve(semid);
	}	
	else
		Ve(semid);
	Vmcc(semid);
	return 0;
}