#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "prototype.h"

//Cette fonction permet de chercher l’existence d’un recrutement dans la liste des recrutements, en le cherchant par son code. Il retourne 1 s’il existe et 0 sinon.
int ExisteRecrutement(listerecrutement *L,int code)
{
    for(elementrecrutement *i = L->first; i!=NULL; i=i->next)
    {
        if (code==i->data->id) {
            return 1;
        }
    }
    return 0;
}

//Cette fonction permet de récupérer un recrutement de la liste des recrutements, en le cherchant par le code. Il retourne le recrutement cherchée.
recrutement *GetRecrutement(listerecrutement *L,int code)
{
     elementrecrutement *tmp=L->first;
    while(tmp!=NULL){
        if(tmp->data->id==code){
            return tmp->data;
        }
        tmp=tmp->next;
    }
    return NULL;
}

//Cette fonction permet de créer un recrutement, en remplissant les données de ce dernière
//(id de l’entreprise, ide du candidat recruté , date de recrutement, type de contrat). Il retourne
//l’offre créée.
recrutement *CreerRecrutement(int rec_index,int offre_index,int ca_index,char *type_Contrat,SDate *d)
{
    recrutement *Rec=(recrutement*)malloc(sizeof(recrutement));
    Rec->id=rec_index;
    Rec->offreidid=offre_index;
    Rec->candidatid=ca_index;
    Rec->typecontrat=type_Contrat;
    Rec->daterecrut=d;
return Rec;
}

//Cette fonction permet de créer un recrutement. Il retourne l’élément recrutement.
elementrecrutement *CreerElementRecrutement(recrutement *Rec){
    elementrecrutement *newElement=(elementrecrutement*)malloc(sizeof(elementrecrutement));
    newElement->data=Rec;
    newElement->next=NULL;
    return newElement;
}

//Cette fonction permet de supprimer un recrutement de la liste des recrutements, en le cherchant par son code. Il retourne -1 si la liste est vide rien, 1 si l’offre est trouvée et supprimée et
//0 sinon.
int DeleteRecrutement(listerecrutement **l, int code)
{
    elementrecrutement *p=(*l)->first;
    if (p==NULL) {
        return -1;
    }
    elementrecrutement *pre=NULL;
    while(p!=NULL){
        if (p->data->id==code) {
            break;
        }
        pre=p;
        p=p->next;
    }
    if (p==(*l)->last) {
        (*l)->last=pre;
    }
    if (pre==NULL) {
        (*l)->first=p->next;
        free(p);
        return 1;
    }else
    {
        pre->next=p->next;
        free(p);
        return 1;
    }
    return 0;
}

//Cette fonction permet d’afficher les données recutement (nom du candidat recruté, nom de
//l’entreprise, type de contrat, date de recrutement ). Il ne retourne rien.
void AfficherRecutement(recrutement *r , listecandidat *lc , listeoffre *lo)
{
    if(r==NULL)
		return;
    candidat *c = GetCandidat(lc,r->candidatid);
    offre *o = GetOffre(lo, r->offreidid);
    printf("\n\tle code de recrutement : %d\n",r->id);
    printf("\n\tNom et prenom du candidat recrute : %s %s (code candidat : %d)\n",c->nom,c->prenom,c->id );
    printf("\n\tNom de l'entreprise d'accueil : %s (code offre : %d)\n", o->entreprise,o->id);
    printf("\n\tType du contrat : %s\n", r->typecontrat);
    AfficherDate("\n\tDate : ",r->daterecrut);
    printf("\n\n\t********************\n");
}

//Cette fonction permet d’afficher tous les recrutements de la liste. Il ne retourne rien.
void AfficherTousRecrutement(listerecrutement *All,listeoffre *o,listecandidat *c)
{
    elementrecrutement *L=All->first;
    while(L!=NULL){
        AfficherRecutement(L->data,c,o);
        L=L->next;
    }
}

//Cette fonction permet d’ajouter l’élément recrutement créé auparavant dans la liste des recrutements.
void AjouterRecrutement(listerecrutement **L,elementrecrutement *newElement)
{
    if((*L)->first==NULL){
        (*L)->first=newElement;
        (*L)->last=newElement;
        return;
    }
    (*L)->last->next=newElement;
    (*L)->last=newElement;
}


//Cette fonction permet de stocker tous les recrutements de la liste dans un fichier.
void DeListeAFichierRecrutement(listerecrutement *L)
{
   if (L->first==NULL)
    {
        return;
    }
    FILE *f=fopen("bd/recrutement.txt","w");
    elementrecrutement *c=L->first;
    while (c!=NULL)
    {
        fprintf(f,"%d -%d -%d -%s -%d %d %d \n",c->data->id,c->data->candidatid,
                c->data->offreidid,c->data->typecontrat,c->data->daterecrut->jour,c->data->daterecrut->mois,
                c->data->daterecrut->annee);
        c=c->next;
    }
    fclose(f);
}


//fonction permet de récupérer tous les recrutements du fichier et les mettre dans une liste des
//recrutements.
void DeFichierAListeRecrutement(listerecrutement **L)
{
    FILE * fc = fopen("bd/recrutement.txt", "r");
	int code,j,m,a,idc,ido;
    char *typec, *t ;
	while(! feof(fc)){
		fscanf(fc,"%d -%d -%d -%s -%d %d %d \n", &code,&idc,&ido,typec,&j,&m,&a);
        if (code>0)
        {
            t=(char*)malloc(sizeof(char)*strlen(typec));
            strcpy(t,typec);
            AjouterRecrutement(L,CreerElementRecrutement(CreerRecrutement(code,idc,ido,t,CreerDate(j,m,a))));
        }
	}
	fclose(fc);
}
