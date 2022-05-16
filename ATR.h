#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define TAILLE_BUFF 256

typedef struct noeud{
    char c;
    struct noeud *fg;
    struct noeud *fc;
    struct noeud *fd;
}NoeudATR, *ATR;

NoeudATR * alloue_noeud_ATR(char c);
void liberer_ATR(ATR a);
int inserer_dans_ATR(ATR *a, const char *mot);
void supprimer_dans_ATR(ATR *a, const char *mot);
void parcours_ATR_aux(ATR a, char *buffer, int index, void (*action)(const char *mot));
void parcours_ATR(ATR a, void (*action)(const char *mot));
int recherche_dans_ATR(ATR a, const char *mot);
int extraire_fichier_vers_ATR(ATR *a, FILE *f);
