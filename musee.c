/**
 * @file musee.c
 * @author Govindaraj VETRIVEL
 */

#include "musee.h"


void raler(char *s)
{
	perror(s);
	exit(1);
}

int getEnvDebug()
{
	char *d;
	int r=0;
	d=getenv("DEBUG_MUSEE");

	if(d==NULL)
		return 0;
	else
		r=atoi(d);
	return r;
}

void affiche_debug(char * s)
{
	printf("%s\n",s );
	fflush(stdout);
}

int creer_shm(void)
{
	key_t k;
	int shmid;
	k = ftok("/dev",35);
	if((shmid=shmget(k,0,0))!=-1)
	{
		shmctl(shmid,IPC_RMID,NULL);
	}
	else if(errno!=ENOENT)
	{
		fprintf(stderr,"HEEEEELP !");
		exit(1);
	}
	shmid=shmget(k,sizeof(mus),IPC_CREAT|0666);
	return shmid;
}


int recup_shm(void)
{
	key_t k;
	int shmid;
	k = ftok("/dev",35);
	if((shmid=shmget(k,0,0))==-1)
	{
		perror("shmget");
		exit(1);
	}
	return shmid;
}
	

void supprimer_shm(int shmid)
{
	if(shmctl(shmid,0,IPC_RMID)==-1)
		raler("directeur_shmctl");
}

int init_semaphore()
{
	key_t k;
	int id;

	k=ftok("/etc/hostname",'G');
	if(k==-1)
		raler("ftok");
	if((id=semget(k,0,0))!=-1)
	{
		semctl(id,IPC_RMID,0);
	}
	id=semget(k,7,IPC_CREAT | 0666);
	if(id==-1)
		raler("init_sem : semget");
	return id;
}

void init_val_semaphore(int id, int c)
{
	if (semctl (id, 0, SETVAL , 0) ==  -1)
		raler ("directeur_setval_sem0");
	if (semctl (id, 1, SETVAL , c) ==  -1)
		raler ("directeur_setval_sem1");
	if (semctl (id, 2, SETVAL , 0) ==  -1)
		raler ("directeur_setval_sem2");
	if (semctl (id, 3, SETVAL , 1) ==  -1)
		raler ("directeur_setval_sem3");
	if (semctl (id, 4, SETVAL , 1) ==  -1)
		raler ("directeur_setval_sem4");
	if (semctl (id, 5, SETVAL , 0) ==  -1)
		raler ("directeur_setval_sem5");
	if (semctl (id, 6, SETVAL , 0) ==  -1)
		raler ("directeur_setval_sem6");
}


void  supprimer_semaphore(int id)
{
	if(semctl(id,0, IPC_RMID,NULL)==-1)
		raler("directeur_semctl");
}


void Po(int id)
{
	struct sembuf s[1] = { {0 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vo(int id)
{
	struct sembuf s[1] = { {0 , 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pe(int id)
{
	struct sembuf s[1] = { {1 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Ve(int id)
{
	struct sembuf s[1] = { {1 , 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pev(int id)
{
	struct sembuf s[1] = { {2 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vev(int id)
{
	struct sembuf s[1] = { {2 , 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pmfc(int id)
{
	struct sembuf s[1] = { {3 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vmfc(int id)
{
	struct sembuf s[1] = { {3, 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pmcc(int id)
{
	struct sembuf s[1] = { {4, -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vmcc(int id)
{
	struct sembuf s[1] = { {4, 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pva(int id)
{
	struct sembuf s[1] = { {5 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vva(int id)
{
	struct sembuf s[1] = { {5 , 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Pdv(int id)
{
	struct sembuf s[1] = { {6 , -1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}

void Vdv(int id)
{
	struct sembuf s[1] = { {6 , 1, 0} } ;
	if ( semop(id , s , 1) == -1)
		raler (" semop ") ;
}