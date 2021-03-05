#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "prototype.h"

SDate *CreerDate(int J,int M,int A)
{
    SDate *N_Date=malloc(sizeof(SDate));
    N_Date->jour=J;
    N_Date->mois=M;
    N_Date->annee=A;
    return N_Date;
}


void AfficherDate(char *c,SDate *d)
{
    if (d==NULL) {
        return;
    }

    printf("%s : %d-%d-%d \n",c,d->jour,d->mois,d->annee);
}


void SupprimerDate(SDate **d){
    if ((*d)==NULL)
    {
        return;
    }
    free((*d));
    (*d)=NULL;
}
