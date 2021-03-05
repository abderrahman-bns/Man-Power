#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "prototype.h"


SLogin *CreerLogin(char *log,char *pass)
{
    SLogin *L=(SLogin*)malloc(sizeof(SLogin));
    L->log=log;
    L->pass=pass;
    return L;
}

SElementLogin *CreerElementLogin(SLogin *Lg){
    SElementLogin *log=(SElementLogin*)malloc(sizeof(SElementLogin));
    log->Login=Lg;
    log->suivant=NULL;
    return log;
}

void AjouterLogin(ListeLogin *l,SElementLogin *log){
    log->suivant = l;
    l = log;
}

int authentification(char *auth_log,char *auth_pass)
{
    FILE *f= fopen("bd/login.txt","r");;
    int  V=0,c;
    ListeLogin *L=NULL;
    char *str=NULL;
    char *login = (char*)malloc(sizeof(char)*10);
    char *pass = (char*)malloc(sizeof(char)*10);
    str = (char*)malloc(sizeof(char)*80);
    if(f==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
    do{
        fscanf(f,"%s %s\0", login ,pass);
        SLogin *S_L = CreerLogin(login,pass);
        SElementLogin *EL = CreerElementLogin(S_L);
        AjouterLogin(L,EL);
        if (strcmp(auth_pass,pass)==0 && strcmp(auth_log,login)==0)
          {
              V= 1; break;
          }
    }while( (c = fgetc(f)) != EOF);
    fclose(f);
    return V;
}
