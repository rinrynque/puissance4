#include <stdio.h>
#include <stdlib.h>

#include "pile.h"

/* @requires : pile* à initialiser
*  @assigns : p->it
*  @ensures : initialise la pile*/
void p_init(Pile* p)
{
    p->it=0;
}


/* @requires :
*  @assigns : crée une variable
*  @ensures : retourne une pile vide*/
Pile p_new(void)
{
    Pile p;
    p_init(&p);
    return p;
}

/* @requires : pile* à tester
*  @assigns :
*  @ensures : retourne un booleen sur la vacuite de la pile*/
int p_isEmpty(Pile* p)
{
    return p->it==0;
}

/* @requires : pile*, élément
*  @assigns : p->tab
*  @ensures : push la pile*/
void p_push(Pile* p, int e)
{
    p->tab[(p->it)++]=e;
}


/* @requires : pile* non vide
*  @assigns : p->tab
*  @ensures : pop la pile*/
int p_pop(Pile* p)
{
    return p->tab[--(p->it)]; //le dernier element de la pile est dans la case it-1, et on décrémente it
}

/* @requires : pile* non vide
*  @assigns :
*  @ensures : peak la pile */
int p_peak(Pile* p)
{
    return p->tab[p->it-1];
}

/* @requires : pile*
*  @assigns :
*  @ensures : affiche la pile*/
void p_disp(Pile* p)
{
    printf("[");
    int i;
    for(i=0; i<p->it; i++)
    {
        printf(" %d ", p->tab[i]);
    }
    printf("]\n");
}

