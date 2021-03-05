#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structure.h"
#include "prototype.h"

//Cette fonction permet de chercher l�existence d�un candidat dans la liste des candidats, en
//le cherchant par son code. Il retourne 1 s�il existe et 0 sinon.
int ExisteCandidat(listecandidat *L,int code)
{
    for(elementcandidat *i = L->first; i!=NULL; i=i->next)
    {
        if (code==i->data->id) {
            return 1;
        }
    }
    return 0;
}


//Cette fonction permet de cr�er un candidat, en remplissant les donn�es de ce dernier (nom,
//pr�nom, domaine de sp�cialit�, nombre d�ann�e d�exp�rience). Il retourne le candidat cr��.
candidat *CreerCandidat(int id,char *nom,char *prenom,char *domaine,int etat,int nb_exp)
{
    candidat *nv=(candidat*)malloc(sizeof(candidat));
    nv->id=id;
    nv->nom=nom;
    nv->prenom=prenom;
    nv->domaine=domaine;
    nv->etat=etat;
    nv->nb_exp=nb_exp;
return nv;
}

//Cette fonction permet de cr�er un �l�ment candidat. Il retourne l��l�ment candidat.
elementcandidat *CreerElementCandidat(candidat *c)
{
    elementcandidat *newElement=(elementcandidat *)malloc(sizeof(elementcandidat));
    newElement->data=c;
    newElement->next=NULL;
    return newElement;
}

//Cette fonction permet de r�cup�rer un candidat de la liste des candidats, en le cherchant par
//son code. Il retourne le candidat cherch�.
candidat *GetCandidat(listecandidat *L,int code)
{
     elementcandidat *tmp=L->first;
    while(tmp!=NULL){
        if(tmp->data->id==code){
            return tmp->data;
        }
        tmp=tmp->next;
    }
    return NULL;
}

//Cette fonction permet d�ajouter l��l�ment candidat cr�� auparavant dans la liste des candidats
void AjouterCandidat(listecandidat **L,elementcandidat *newElement)
{
    if((*L)->first==NULL){
        (*L)->first=newElement;
        (*L)->last=newElement;
        return;
    }
    (*L)->last->next=newElement;
    (*L)->last=newElement;
}

//Cette fonction permet de modifier les donn�es d�un candidat de la liste des candidats, en le
//cherchant par son code. Il ne retourne rien.
void ModifierCandidat(listecandidat *l,int code,char *nom,char *prenom,char *domaine,int etat,int nb_exp)
{
    candidat *edit=GetCandidat(l,code);
    if (nom!=NULL)
        edit->nom=nom;
    if (prenom!=NULL)
        edit->prenom=prenom;
    if (domaine!=NULL)
        edit->domaine=domaine;
    if (etat!=NULL && (etat==1|| etat==0 ))
        edit->etat=etat;
    if (nb_exp!=NULL)
        edit->nb_exp=nb_exp;
}

//Cette fonction permet de supprimer un candidat de la liste des candidats, en le cherchant par
//son code. Il retourne -1 si la liste est vide rien, 1 si le candidat est trouv� et supprim� et 0 sinon.
int DeleteCandidat(listecandidat **l,int code)
{
    elementcandidat *p=(*l)->first;
    if (p==NULL) {
        return -1;
    }
    elementcandidat *pre=NULL;
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


//Cette fonction permet d�afficher les donn�es d�un candidat. Il ne retourne rien.
void AfficherCandidat(candidat *c)
{
    if(c==NULL)
        return;
    printf("\n\tID : %d \n",c->id);
    printf("\n\tNom : %s \n",c->nom);
    printf("\n\tPrenom : %s \n",c->prenom);
    printf("\n\tDomaine : %s \n",c->domaine);
    if(c->etat==1)
        printf("\n\tEtat : Recrute \n");
    if(c->etat==0)
        printf("\n\tEtat : Non recrute \n");
    printf("\n\tNombre d'annee d'experience : %d \n",c->nb_exp);
    printf("\n\t********************\t\n");
}

//Cette fonction permet d�afficher tous les candidats de la liste. Il ne retourne rien.
void AfficherTousCandidats(listecandidat *All)
{
    elementcandidat *L=All->first;
    while(L!=NULL){
        AfficherCandidat(L->data);
        L=L->next;
    }
}


//Cette fonction permet d�afficher tous les offres disponibles int�ressant un candidat non recrut�, en comparant le domaine de chaque offre disponible de la liste des offres avec le domaine
//du candidat. Il ne retourne rien.
void AfficherOffresCandidat(listeoffre *l,candidat *c)
{
    elementoffre *n=l->first;
    while(n!=NULL){
            if(strcmp(n->data->domaine, c->domaine)== 0 && n->data->dispo==1)
                AfficherOffre(n->data);
            n=n->next;
    }
}


//Cette fonction permet d�afficher tous les candidats non recrut�s et ad�quats � une offre,
//en comparant le domaine de de chaque candidat non recrut� de la liste des candidats avec le
//domaine de l�offre. Il ne retourne rien.
void AfficherCandidatsOffre(listecandidat *l,offre *o)
{
   elementcandidat *n=l->first;
    while(n!=NULL){
        if( strcmp(o->domaine,n->data->domaine)== 0 && n->data->etat == 0)
            AfficherCandidat(n->data);
        n=n->next;
    }
}

//Cette fonction permet de stocker tous les candidats de la liste dans un fichier.
void DeListeAFichierCandidat(listecandidat *L)
{
    if (L->first==NULL)
    {
        return;
    }
    FILE *f=fopen("bd/candidat.txt","w");

    elementcandidat *c=L->first;
    while (c)
    {
        fprintf(f,"%d-%s -%s -%s -%d -%d \n",c->data->id,c->data->nom,c->data->prenom,c->data->domaine,c->data->etat,c->data->nb_exp);
        c=c->next;
    }
    fclose(f);
}

//Cette fonction permet de r�cup�rer tous les candidats du fichier et les mettre dans une liste
//des candidats.
void DeFichierAListeCandidat(listecandidat **L)
{
    FILE * fc = fopen("bd/candidat.txt", "r");
	int code,e,exp;
    char nom[25],prenom[25],domaine[25],*n,*p,*d ;
	while(! feof(fc)){

		fscanf(fc,"%d-%s -%s -%s -%d -%d \n", &code,nom,prenom,domaine,&e,&exp);
        if (code>0)
        {
            n=(char*)malloc(sizeof(char)*strlen(nom));
            strcpy(n,nom);
            p=(char*)malloc(sizeof(char)*strlen(prenom));
            strcpy(p,prenom);
            d=(char*)malloc(sizeof(char)*strlen(domaine));
            strcpy(d,domaine);
            AjouterCandidat(L,CreerElementCandidat(CreerCandidat(code,n,p,d,e,exp)));
        }
	}
	fclose(fc);
}
