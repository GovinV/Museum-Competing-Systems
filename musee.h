/**
 * @file musee.h
 * @author Govindaraj VETRIVEL
 */

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#ifndef __MUSEE_H_
#define __MUSEE_H_


typedef struct s_mus
{
	int capacite;
	int capacite_cur;
	int file;
	int file_cur;
	int ouvert;
	int id_sema;
	int contro_act;
} mus;

/*
 * Sortir lors d'une ereur d'une primitive système
 */
void raler(char *s);

/*
 * Récupérer la variable d'environnement DEBUG_MUSEE si elle existe
 * Renvoie 0 si la variable n'existe pas
 */
int getEnvDebug();

/*
 * afficher un message puis utiliser fflush
 */
void affiche_debug(char * s);

/*
 * Crée le segment de mémoire partagée
 */
int creer_shm(void);


/*
 * Récupère l'identifiant du segment de mémoire partagée
 */
int recup_shm(void);

/*
 * Supprime le segment de mémoire partagée
 */
void supprimer_shm(int shmid);

/*
 * Crée l'ensemble de sémaphores
 */
int init_semaphore ();

/*
 * Initialise les valeurs des sémaphores
 */
void init_val_semaphore(int id, int c);

/*
 * Supprime l'ensemble de sémaphores
 */
void  supprimer_semaphore(int id);

/*
 * Fonctions P et V des différentes sémaphores
 * Décrites dans le rapport
 */

void Po(int id);

void Vo(int id);

void Pe(int id);

void Ve(int id);

void Pev(int id);

void Vev(int id);

void Pmfc(int id);

void Vmfc(int id);

void Pmcc(int id);

void Vmcc(int id);

void Pva(int id);

void Vva(int id);

void Pdv(int id);

void Vdv(int id);

#endif
