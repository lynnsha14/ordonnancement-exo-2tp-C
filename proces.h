#ifndef __QUEUE__H__
#define __QUEUE__H__

#define priorite_min 0 // Priorité minimum
#define priorite_max 5 // Priorité maximum
/*---------------------------------*/
typedef struct Processus
{
    char* nom;
    int priorite;
    double duree;
}Processus;


/***********************************/
typedef struct Ordonnanceur
{
    Processus donnee ;
    struct Ordonnanceur* next;               //liste chainee
}Ordonnanceur;

/*---------------------------------*/

static Ordonnanceur *first = NULL; // Tête de la file
static Ordonnanceur *last = NULL;  // queue de la file 

int file_vide(void);
void ajout_activite(Processus p);
void defiler_Ordonnanceur(void);
void clear_Ordonnanceur(void);
Processus tete_Ordonnanceur(void);
int step(void);
void run(void);


#endif
