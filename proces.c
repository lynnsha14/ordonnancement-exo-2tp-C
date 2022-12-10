#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include "proces.h"

int file_vide(void)
{
    if(first == NULL && last == NULL)
         return 1;
    return 0;
}
/*------------------------*/
void ajout_activite(Processus p)
{ 
    // vérification si la variable priorité est compris entre les valeurs attendus.
     if (p.priorite < priorite_min || p.priorite > priorite_max)
     {
          printf("La priorité du processus est incorrecte\n");
	     exit(1);
     }

     Ordonnanceur *temp = first;
     Ordonnanceur *O =  malloc(sizeof(Ordonnanceur));
     O->donnee = p;
     O->next = NULL;

     if(file_vide())
     {
          first = O;
          last = O;
     }
     else
     {    // Si la priorité du processus est plus petit que celui de la tête de file
	     // on l'ajoute en tête de file.
          if(p.priorite < first->donnee.priorite)
          {
               O->next = first;
               first = O;
          }
          // Si la priorité du processus est plus grand que celui de la queue de file
		// on l'ajoute en queue de file.
          else if(p.priorite >= last->donnee.priorite)
          {
               last->next = O;
               last = O;
          }
          else
          {
               // Sinon, on parcours la liste jusqu'à trouver un processus de priorité
			// plus grande que celui du processus à ajouter.
			// Avec ces vérifications, les processus seront donc toujours triés par priorité.
			// Mais aussi par ordre d'appel si deux processus ont la même priorité.
               while (temp->next != NULL && temp->next->donnee.priorite <= p.priorite)
               {
                    temp = temp->next;
               }
               O->next = temp->next;
               temp->next = O;
               
          }
     }

}
/*------------------------*/

void defiler_Ordonnanceur()
{
	if(file_vide())
	{
		printf("La file est vide\n");
		exit(1);
	}
	// Comme l'ordonnanceur est trié par priorité, on supprime toujours le premier élément.
	Ordonnanceur *temp = first;
	if(first == last)
	{
		first = NULL;
		last = NULL;
	}
	else
	{
		first = first->next;
	}
	free(temp);
	}

/*------------------------*/
Processus tete_Ordonnanceur(){
	if(file_vide())
	{
		printf("La file est vide\n");
		exit(1);
	}
	return first->donnee;
}
/*------------------------*/

void clear_Ordonnanceur(void)
{
	// tant que la file n'est pas vide, on supprime le premier élément.
	while(!file_vide())
	{
		defiler_Ordonnanceur();
	}
}

/*-------------------------*/

int step()
{
    if(file_vide())
    {
		return 0;
    }
    else
    {
	// On execute le processus --> On affiche son contenue
	printf("Nom du processus : %s\n", tete_Ordonnanceur().nom );
	printf("Durée d'exécution du processus : %f\n", tete_Ordonnanceur().duree);
	printf("Priorité du processus : %d\n", tete_Ordonnanceur().priorite);
	printf("Exécution du processus en cours...\n\n");
	// Et on attend le temps de la durée d'éxecution du processus.
	sleep(tete_Ordonnanceur().duree);
	defiler_Ordonnanceur();
	return 1;
    }
}

/*---------------------------*/

void run()
{
if(file_vide())
{
	printf("Il n'y à aucun processus à éxecuter.\n");
	exit(1);
}
// On execute les processus tant qu'il y en a.
while(step());
printf("Tous les processus ont été exécutés\n");
}

//The end.