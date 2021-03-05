#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Structure.h"
#include "Prototype.h"


//Cette fonction permet de chercher l’existence d’une offre dans la liste des offres, en le cherchant par le code. Il retourne 1 s’il existe et 0 sinon.
int ExisteOffre(listeoffre *L,int code)
{
    for(elementoffre *i = L->first; i!=NULL; i=i->next)
    {
        if (code==i->data->id) {
            return 1;
        }
    }
    return 0;
}

//Cette fonction permet de créer une offre, en remplissant les données de cette dernière (nom de l’entreprise, domaine demandé, date d’expiration, disponibilité)
offre *CreerOffre(int index,char *entreprise,SDate *d,char *DP,int Dispo)
{
    offre *Ofr=(offre*)malloc(sizeof(offre));
    Ofr->id=index;
    Ofr->entreprise=entreprise;
    Ofr->date=d;
    Ofr->domaine=DP;
    Ofr->dispo=Dispo;
return Ofr;
}

//Cette fonction permet de créer un élément offre. Il retourne l’élément offre.
elementoffre *CreerElementOffre(offre *o)
{
    elementoffre *newElement=(elementoffre *)malloc(sizeof(elementoffre));
    newElement->data=o;
    newElement->next=NULL;
    return newElement;
}

//Cette fonction permet de récupérer une offre de la liste des offres, en le cherchant par le code. Il retourne l’offre cherchée.
offre *GetOffre(listeoffre *L,int code)
{
     elementoffre *tmp=L->first;
    while(tmp!=NULL){
        if(tmp->data->id==code){
            return tmp->data;
        }
        tmp=tmp->next;
    }
    return NULL;
}

//fonction permet d’ajouter l’élément offre créer auparavant dans la liste des offres.
void AjouterOffre(listeoffre **L,elementoffre *newElement)
{
    if((*L)->first==NULL){
        (*L)->first=newElement;
        (*L)->last=newElement;
        return;
    }
    (*L)->last->next=newElement;
    (*L)->last=newElement;
}

//Cette fonction permet de modifier les données d’une offre de la liste des offres, en le cherchant par le code. Il ne retourne rien.
void ModifierOffre(listeoffre *L,int code,int J , int M , int A,char *entreprise_nom, char *DP,int Dispo)
{
    offre *edit=GetOffre(L,code);
    if (entreprise_nom!=NULL)
        edit->entreprise=entreprise_nom;
    if (DP!=NULL)
        edit->domaine=DP;
    if (J!=NULL)
        edit->date->jour=J;
    if (M!=NULL)
        edit->date->mois=M;
    if (A!=NULL)
        edit->date->annee=A;
    if (Dispo!=NULL && (Dispo == 1 || Dispo == 0 ))
        edit->dispo=Dispo;
}

//Cette fonction permet de supprimer une offre de la liste des offres, en le cherchant par son code. Il retourne -1 si la liste est vide rien, 1 si l’offre est trouvée et supprimée et 0 sinon.
int DeleteOffre(listeoffre **l,int code)
{
    elementoffre *p=(*l)->first;
    if (p==NULL) {
        return -1;
    }
    elementoffre *pre=NULL;
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

//Cette fonction permet d’afficher les données d’une offre. Il ne retourne rien.
void AfficherOffre(offre *o)
{
    if(o==NULL)
        return;
    else{
    printf("\n\tID : %d \n",o->id);
    printf("\n\tDomaine (demande) : %s\n", o->domaine);
    printf("\n\tNom de l'entreprise : %s\n", o->entreprise);
    if(o->dispo==1)
        printf("\n\tEtat : Disponible\n");
    if(o->dispo==0)
        printf("\n\tEtat : Non disponible\n");
    printf("\n\tLa date limite : %d/%d/%d \n",o->date->jour,o->date->mois,o->date->annee);
    printf("\n\t********************\n");

}
}

//Cette fonction permet d’afficher tous les offres de la liste. Il ne retourne rien.
void AfficherTousOffres(listeoffre *All)
{
    elementoffre *L=All->first;
    while(L!=NULL){
        AfficherOffre(L->data);
        L=L->next;
    }
}

//Cette fonction permet d’afficher tous les offres d’une entreprise dans un domaine précis, en comparant le domaine et le nom de l’entreprise de chaque offre de la liste des offres avec le domaine et le nom de l’entreprise recherchés. Il ne retourne rien.
void AfficherOffresCriteres(listeoffre *l, char *nom, char *specialite)
{
    elementoffre *n=l->first;
    while(n!=NULL){
            if(strcmp(n->data->entreprise, nom) == 0 && strcmp(n->data->domaine, specialite) == 0)
                AfficherOffre(n->data);
            n=n->next;
    }
}

//Cette fonction permet d’afficher tous les candidats non recrutés et adéquats à une offre et ayant le nombre d’année d’expérience supérieur e à 2 ans, en comparant le domaine de de chaque candidat non recruté de la liste des candidats avec le domaine de l’offre ainsi vérifier que ces candidats ont plus de 2 ans d’expérience. Il ne retourne rien.
void CandidatsPotenOffre(listecandidat *l,offre *o)
{
   elementcandidat *n=l->first;
    while(n!=NULL){
        if( strcmp(o->domaine,n->data->domaine)== 0 && n->data->etat == 0 && n->data->nb_exp >= 2)
            AfficherCandidat(n->data);
        n=n->next;
    }
}

//Cette fonction permet de stocker tous les offres de la liste dans un fichier.
void DeListeAFichierOffre(listeoffre *L)
{
   if (L->first==NULL)
    {
        return;
    }
    FILE *f=fopen("bd/offre.txt","w");

    elementoffre *c=L->first;
    while (c!=NULL)
    {
        fprintf(f,"%d-%s -%s -%d %d %d -%d \n",c->data->id,c->data->entreprise,
                c->data->domaine,c->data->date->jour,c->data->date->mois,
                c->data->date->annee,c->data->dispo);
        c=c->next;
    }
    fclose(f);
}

//Cette fonction permet de récupérer tous les offres du fichier et les mettre dans une liste des offres.
void DeFichierAlisteOffre(listeoffre **L){
    FILE * fc = fopen("bd/offre.txt", "r");
	int code,j,m,a,disp;
    char entreprise[25],domaine[25], *e,*d ;
	while(! feof(fc)){
		fscanf(fc,"%d-%s -%s -%d %d %d -%d \n", &code,entreprise,domaine,&j,&m,&a,&disp);
        if (code>0)
        {
            e=(char*)malloc(sizeof(char)*strlen(entreprise));
            strcpy(e,entreprise);
            d=(char*)malloc(sizeof(char)*strlen(domaine));
            strcpy(d,domaine);
            AjouterOffre(L,CreerElementOffre(CreerOffre(code,e,CreerDate(j,m,a),d,disp)));
        }
	}
	fclose(fc);
}
