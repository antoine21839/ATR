#include "ATR.h"

NoeudATR * alloue_noeud_ATR(char c){
    NoeudATR * tmp = (NoeudATR *)malloc(sizeof(NoeudATR));
    if(tmp == NULL)
        return NULL;
    tmp->c = c;
    tmp->fg = NULL;
    tmp->fc = NULL;
    tmp->fd = NULL;
    return tmp;
}

void liberer_ATR(ATR a){
    /*
        Fonction qui efface l'ATR et libère l'espace mémoire allouée.
    */
    if(NULL == a)
        return;
    liberer_ATR(a->fg);
    liberer_ATR(a->fc);
    liberer_ATR(a->fd);
    free(a);
}

int inserer_dans_ATR(ATR *a, const char *mot){
    assert(NULL != a);
    assert(NULL != mot);
    if(NULL == *a){
        *a = alloue_noeud_ATR(*mot);
        if(NULL == *a){
            fprintf(stderr, "Erreur lors de l'ajout d'un noeud dans l'ATR !\n");
            return 0;
        }
    }
    if(*mot == '\0')
        return 1;
    if(*mot < (*a)->c)
        return inserer_dans_ATR(&((*a)->fg), mot);
    if(*mot == (*a)->c)
        return inserer_dans_ATR(&((*a)->fc), mot + 1);
    if(*mot > (*a)->c)
        return inserer_dans_ATR(&((*a)->fd), mot);
    return 0;
}

void supprimer_dans_ATR(ATR *a, const char *mot){
    /*
        Fonction qui supprime dans l'ATR une chaîne de caractères mot.
    */
    ATR tmp;
    if(*mot == '\0') {
        tmp = *a;
        *a = (*a)->fd;
        free(tmp);
        return;
    }
    if((*a)->c > *mot)
        supprimer_dans_ATR(&(*a)->fg, mot);
    else if((*a)->c == *mot)
        supprimer_dans_ATR(&(*a)->fc, mot + 1);
    else if((*a)->c < *mot)
        supprimer_dans_ATR(&(*a)->fd, mot);
    if('\0' != (*a)->c && NULL == (*a)->fc) {
        tmp = *a;
        *a = (*a)->fd;
        free(tmp);
    }
}

static void parcours_ATR_aux(ATR a, char *buffer, int index, void (*action)(const char *mot)){
    /*
        Fonction auxiliaire de la fonction afficher_ATR.
    */
    if(NULL == a)
        return;
    buffer[index] = a->c;
    if('\0' == a->c)
        action(buffer);
    parcours_ATR_aux(a->fg, buffer, index, action);
    parcours_ATR_aux(a->fc, buffer, index + 1, action);
    parcours_ATR_aux(a->fd, buffer, index, action);
}

void parcours_ATR(ATR a, void (*action)(const char *mot)){
    char buffer[TAILLE_BUFF];
    parcours_ATR_aux(a, buffer, 0, action);
}


int recherche_dans_ATR(ATR a, const char *mot){
    assert(NULL != mot);
    if (NULL == a)
        return 0;
    if(*mot == a->c){
        if('\0' == *mot)
            return 1;
        else
            return recherche_dans_ATR(a->fc, mot + 1);
    }
    if(*mot < a->c)
        return recherche_dans_ATR(a->fg, mot);
    if(*mot > a->c)
        return recherche_dans_ATR(a->fd, mot);
    return 0;
}

int extraire_fichier_vers_ATR(ATR *a, FILE *f){
    /*
        Fonction qui insère le contenu d'un fichier
        dans un ATR et retourne 1 si cela est
        correctement réalisé.
    */
    char mot[TAILLE_BUFF];
    assert(NULL != a);
    assert(NULL != f);
    while(fscanf(f, "%s", mot) == 1){
        if(inserer_dans_ATR(a, mot) == 0)
            return 0;
    }
    return 1;
}
