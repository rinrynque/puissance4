#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#define PILE_FIXED_SIZE 1000

struct Pile
{
  int tab[PILE_FIXED_SIZE]; /*tableau de stockage*/
  int it; /*nombre d'elements dans la pile*/
};

typedef struct Pile Pile;

void p_init(Pile*);
Pile p_new(void);
int p_isEmpty(Pile*);
void p_push(Pile*, int);
int p_pop(Pile*);
int p_peak(Pile*);
void p_disp(Pile*);


#endif /* PILE_H_INCLUDED */
