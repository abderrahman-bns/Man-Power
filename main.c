#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Candidat.c"
#include "Offre.c"
#include "Recrutement.c"
#include "Date.c"
#include "Login.c"

char *saise(char *ss){
    char tmp[100];
    printf("%s",ss);
    gets(tmp);
    for (int i = 0; i < strlen(tmp); i++)
    {
        if (tmp[i]==' ')
        {
            tmp[i]='_';
        }
    }

    char *s=(char*)malloc(sizeof(char)*strlen(tmp));
    strcpy(s,tmp);
    if (strlen(s)<1)
        s=NULL;
    return s;
}

int saiseint(){
    int m;
    char tmp[100];
    gets(tmp);
    m=atoi(tmp);
    return m;
}


void tryagain(){
    printf("\n\t\tTaper un charactere pour essayer de nouveau ...\n");
    getchar();
}

COORD coord = {0, 0};

void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y; // X and Y coordinates
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void stop(){
    printf("\n\t\tTaper un charactere pour continuer ...\n");
    getchar();
}

void ecraseAll(){
    FILE *f1=fopen("bd/candidat.txt", "w");
    fclose(f1);
    FILE *f2=fopen("bd/offre.txt", "w");
    fclose(f2);
    FILE *f3=fopen("bd/recrutement.txt", "w");
    fclose(f3);
}


void saveAll(listecandidat *C,listeoffre *O,listerecrutement **R){
    ecraseAll();
    DeListeAFichierCandidat(C);
    DeListeAFichierOffre(O);
    DeListeAFichierRecrutement(R);
}

void getAll(listecandidat **C,listeoffre **O,listerecrutement **R){
    DeFichierAListeCandidat(C);
    DeFichierAlisteOffre(O);
    DeFichierAListeRecrutement(R);
}


void menu(listecandidat **C,listeoffre **O,listerecrutement **R);
void menurecrutement(listecandidat **C,listeoffre **O,listerecrutement **R);
void menuoffre(listecandidat **C,listeoffre **O,listerecrutement **R);
void menucandidat(listecandidat **C,listeoffre **O,listerecrutement **R);

void menucandidat(listecandidat **C,listeoffre **O,listerecrutement **R)
{
    int choix,code,nbe,e;
    char *n,*p,*d;
    do{
        system("cls");
gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2  MENU CANDIDAT ");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 1)  Ajouter candidat");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 2)  Modidfier candidat");
gotoxy(20,13);
printf("\xDB\xDB\xDB\xDB\xB2 3)  Supprimer candidat");
gotoxy(20,15);
printf("\xDB\xDB\xDB\xDB\xB2 4)  Rechercher candidat");
gotoxy(20,17);
printf("\xDB\xDB\xDB\xDB\xB2 5)  Afficher tous les candidats");
gotoxy(20,19);
printf("\xDB\xDB\xDB\xDB\xB2 6)  Afficher tous les offres susceptibles d interesser le candidat");
gotoxy(20,21);
printf("\xDB\xDB\xDB\xDB\xB2 7)  Afficher tous les candidats adequats a un offre ");
gotoxy(20,23);
printf("\xDB\xDB\xDB\xDB\xB2 0)  Retour au menu principal ");
gotoxy(20,25);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,26);
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
        switch (choix)
        {
            case 0:
                menu(C,O,R);
                break;
            case 1:
                printf("\n\t\t\t\tAjouter Candidat\n");
                printf("\n\t\t\tCode de candidat a ajouter : ");
                scanf("%d",&code);
                while (ExisteCandidat(*C,code)||code <=0)
                {
                    printf("\n\t\t\t\tCe code deja existe entre un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                getchar();
                n=saise("\n\t\t\tnom de candidat : ");
                p=saise("\n\t\t\tprenom de candidat : ");
                d=saise("\n\t\t\tdomaine de candidat : ");
                printf("\n\t\t\tEtat (1 Recrute / 0 Non recrute) : ");
                scanf("%d",&e);
                printf("\n\t\t\tNombre des annees experience de candidat : ");
                scanf("%d",&nbe);
                AjouterCandidat(C,CreerElementCandidat(CreerCandidat(code,n,p,d,e,nbe)));
                n=NULL;p=NULL;d=NULL;
                break;
            case 2:
                printf("\n\t\t\t\tModifier candidat \n\n");
                printf("\t\t\tNote : Ne rien taper pour ne pas modifier un champ \n\n");
                printf("\t\t\tEntrer le code de candidat a modifier : ");
                scanf("%d",&code);
                while(!ExisteCandidat(*C,code)||code <=0)
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                getchar();
                n=saise("\n\t\t\tnom de candidat : ");
                p=saise("\n\t\t\tprenom de candidat : ");
                d=saise("\n\t\t\tdomaine de candidat : ");
                printf("\n\t\t\tEtat (1 Recrute / 0 Non recrute) :");
                scanf("%d",&e);
                printf("\n\t\t\tNombre des annees experience de candidat : ");
                scanf("%d",&nbe);
                ModifierCandidat(*C,code,n,p,d,e,nbe);
                n=NULL;p=NULL;d=NULL;
                break;
            case 3:
                printf("\n\t\t\t\tSupprimer candidat \n\n");
                printf("\tEntrer le code de candidat a supprimer : ");
                scanf("%d",&code);
                while (!ExisteCandidat(*C,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                DeleteCandidat(C,code);
                break;
            case 4:
                printf("\n\t\t\t\tRechercher Candidat\n");
                printf("\n\t\t\tCode de candidat : ");
                scanf("%d",&code);
                while (!ExisteCandidat(*C,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                AfficherCandidat(GetCandidat(*C,code));
                getchar();
                stop();
                break;
            case 5:
                printf("\n\t\t\t\tAfficher tous les candidats \n\n");
                AfficherTousCandidats(*C);
                getchar();
                stop();
                break;
            case 6:
                printf("\n\t\t\t\tAfficher tous les offres susceptibles d interesser le candidat \n\n");
                printf("\t\t\tEntrer le code de candidat : ");
                scanf("%d",&code);
                while (!ExisteCandidat(*C,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                AfficherOffresCandidat(*O,GetCandidat(*C,code));;
                getchar();
                stop();
                break;
            case 7:
                printf("\n\t\t\t\tAfficher tous les candidats adequats a un offre \n\n");
                printf("\t\t\tEntrer le code de l offre : ");
                scanf("%d",&code);
                while(!ExisteOffre(*O,code)||code <=0)
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menucandidat(C,O,R);
                    }
                }
                AfficherCandidatsOffre(*C,GetOffre(*O,code));
                getchar();
                stop();
                break;
            default:
                printf("\n\t\t\tChoix invalid !\n");
                getchar();
                stop();
                break;
        }
    } while (choix!=0);
}

void menuoffre(listecandidat **C,listeoffre **O,listerecrutement **R)
{
    int choix,code,j,m,a, d;
    char *n=NULL,*p=NULL;
    do{
        system("cls");
gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2  MENU OFFRE ");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 1)  Ajouter offre ");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 2)  Modidfier offre ");
gotoxy(20,13);
printf("\xDB\xDB\xDB\xDB\xB2 3)  Supprimer offre ");
gotoxy(20,15);
printf("\xDB\xDB\xDB\xDB\xB2 4)  Rechercher offre ");
gotoxy(20,17);
printf("\xDB\xDB\xDB\xDB\xB2 5)  Afficher tous les offres ");
gotoxy(20,19);
printf("\xDB\xDB\xDB\xDB\xB2 6)  Afficher les offres selon critere ( entreprise / domaine ) ");
gotoxy(20,21);
printf("\xDB\xDB\xDB\xDB\xB2 7)  Afficher la liste des candidats potentiels pour un offre ( annee experience >= 2 ) ");
gotoxy(20,23);
printf("\xDB\xDB\xDB\xDB\xB2 0)  Retour au menu principal ");
gotoxy(20,25);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,26);
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
        switch (choix)
        {
            case 1:
                printf("\n\t\t\t\tAjouter Offre\n\n");
                printf("\t\t\tCode d Offre : ");
                scanf("%d",&code);
                while (ExisteOffre(*O,code)||code <=0)
                {
                    printf("\n\t\t\tCe code existe deja entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                getchar();
                n=saise("\n\t\t\tNom de l entreprise: ");
                p=saise("\n\t\t\tDomaine (demande) : ");
                printf("\n\t\t\tDisponibilite (1 = Disponible / 0 = Non disponible) :  ");
                scanf("%d",&d);
                printf("\n\t\t\tEntrer la date de fin de l offre : ");
                printf("\n\n\t\t\t\tJour : ");
                scanf("%d",&j);
                printf("\n\t\t\t\tMois : ");
                scanf("%d",&m);
                printf("\n\t\t\t\tAnnee : ");
                scanf("%d",&a);
                AjouterOffre(O,CreerElementOffre(CreerOffre(code,n,CreerDate(j,m,a),p,d)));
                n=NULL,p=NULL,d=NULL;
                getchar();
                stop();
                break;
            case 2:
                printf("\n\t\t\t\tModifier offre \n\n");
                printf("\t\t\tNote : Ne rien taper pour ne pas modifier un champ \n\n");
                printf("\t\t\tEntrer le code d offre a modifier : ");
                scanf("%d",&code);
                while(!ExisteOffre(*O,code)||code <=0)
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                getchar();
                n=saise("\n\t\t\tNom de l entreprise: ");
                p=saise("\n\t\t\tDomaine (demande) : ");
                printf("\n\t\t\tDisponibilite (1 = Disponible / 0 = Non disponible) :  ");
                scanf("%d",&d);
                printf("\n\t\t\tEntrer la date de fin de l offre : ");
                printf("\n\n\t\t\t\tJour : ");
                scanf("%d",&j);
                printf("\n\t\t\t\tMois : ");
                scanf("%d",&m);
                printf("\n\t\t\t\tAnnee : ");
                scanf("%d",&a);
                ModifierOffre(*O,code,j,m,a,n,p,d);
                n=NULL,p=NULL,d=NULL;
                getchar();
                stop();
                break;
            case 3:
                printf("\n\t\t\t\tSupprimer offre \n\n");
                printf("\t\t\tEntrer le code d offre a supprimer : ");
                scanf("%d",&code);
                while (!ExisteOffre(*O,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                DeleteOffre(*O,code);
                getchar();
                stop();
                break;
            case 4:
                printf("\n\t\t\t\tRechercher offre\n");
                printf("\n\t\t\tcode d offre recherche : ");
                scanf("%d",&code);
                while (!ExisteOffre(*O,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                AfficherOffre(GetOffre(*O,code));
                getchar();
                stop();
                break;
            case 5:
                printf("\n\t\t\t\tAfficher tous les offres \n\n");
                AfficherTousOffres(*O);
                getchar();
                stop();
                break;
            case 6:
                printf("\n\t\t\t\tAfficher tous les offres selon les criteres suivants (Non de l entreprise - Domaine) \n\n");
                getchar();
                n=saise("\n\t\t\tNom de l entreprise : ");
                p=saise("\n\t\t\tDomaine  : ");
                AfficherOffresCriteres(*O,n,p);
                getchar();
                stop();
                break;
            case 7:
                printf("\n\t\t\t\tAfficher tous les candidats potentiels pour un offre \n\n");
                printf("\t\t\tEntrer le code d offre : ");
                scanf("%d",&code);
                while (!ExisteOffre(*O,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                CandidatsPotenOffre(*C,GetOffre(*O,code));
                getchar();
                stop();
                break;
            case 0:
                menu(C,O,R);
                break;
            default:
                printf("\n\t\t\tChoix invalid !\n");
                getchar();
                stop();
                break;
        }
    } while (choix!=0);
}

void menurecrutement(listecandidat **C,listeoffre **O,listerecrutement **R)
{
    int choix,code,idc,ido,j,m,a;
    char *t;
    do{
    system("cls");
gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2  MENU RECRUTEMENT ");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 1)  Ajouter un recrutement ");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 2)  Annuler un recrutement ");
gotoxy(20,13);
printf("\xDB\xDB\xDB\xDB\xB2 3)  Afficher la liste des recrutements realises ");
gotoxy(20,15);
printf("\xDB\xDB\xDB\xDB\xB2 0)  Retour au menu principal ");
gotoxy(20,17);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,19);
        printf("\n\t\t\tVotre choix : ");
        scanf("%d",&choix);
        switch (choix)
        {
            case 0:
                menu(C,O,R);
                break;
            case 1:
                printf("\n\t\t\t\tAjouter Recrutement\n");
                printf("\n\t\t\tCode de recrutement a ajouter : ");
                scanf("%d",&code);
                while (ExisteRecrutement(*R,code)||code <=0)
                {
                    printf("\t\t\t\tCe code deja existe entre un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menurecrutement(C,O,R);
                    }
                }
                printf("\n\t\t\tCode de candidat a recrute : ");
                scanf("%d",&idc);
                printf("\n\t\t\tCode de l offre a recrute : ");
                scanf("%d",&ido);
                getchar();
                t=saise("\n\t\t\tType de contrat : ");
                printf("\n\t\t\tEntrer la date de fin de l offre : ");
                printf("\n\n\t\t\t\tJour : ");
                scanf("%d",&j);
                printf("\n\t\t\t\tMois : ");
                scanf("%d",&m);
                printf("\n\t\t\t\tAnnee : ");
                scanf("%d",&a);
                AjouterRecrutement(R,CreerElementRecrutement(CreerRecrutement(code,ido,idc,t,CreerDate(j,m,a))));
                ModifierCandidat(*C,idc,NULL,NULL,NULL,1,NULL);
                t=NULL;
                break;
            case 2:
                printf("\n\t\t\t\tSupprimer recrutement \n\n");
                printf("\t\t\tEntrer le code de recrutement a supprime : ");
                scanf("%d",&code);
                while (!ExisteOffre(*O,code))
                {
                    printf("\n\t\t\tCe code n'existe pas entrer un autre ou -1 pour annuller : ");
                    scanf("%d",&code);
                    if (code==-1)
                    {
                        menuoffre(C,O,R);
                    }
                }
                DeleteRecrutement(R,code);
                ModifierCandidat(*C,idc,NULL,NULL,NULL,0,NULL);
                getchar();
                stop();
                break;
            case 3:
                printf("\n\t\t\t\tAfficher la liste des recrutements realises \n\n");
                AfficherTousRecrutement(*R,*O,*C);
                getchar();
                stop();
                break;
            default:
                printf("\n\t\t\tChoix invalid !\n");
                getchar();
                stop();
        }getchar();
    } while (choix!=0);
}

void menu(listecandidat **C,listeoffre **O,listerecrutement **R)
{
    int choix ;
    do
    {
        system("cls");
gotoxy(20,5);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,7);
printf("\xDB\xDB\xDB\xDB\xB2  MENU PRINCIPALE ");
gotoxy(20,9);
printf("\xDB\xDB\xDB\xDB\xB2 1)  Gestion des candidats ");
gotoxy(20,11);
printf("\xDB\xDB\xDB\xDB\xB2 2)  Gestion des offres ");
gotoxy(20,13);
printf("\xDB\xDB\xDB\xDB\xB2 3)  Gestion des recrutements ");
gotoxy(20,15);
printf("\xDB\xDB\xDB\xDB\xB2 0)  Quitter ");
gotoxy(20,17);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(20,19);
        printf("\n\t\t\t\t\tVotre choix : ");
        scanf("%d",&choix);
        switch (choix)
        {
            case 0:
                saveAll(*C,*O,*R);
                exit(0);
            case 1:
                menucandidat(C,O,R);
                break;
            case 2:
                menuoffre(C,O,R);
                break;
            case 3:
                menurecrutement(C,O,R);
                break;
            default:
                printf("\n\t\t\tChoix invalid !\n");
                stop();
        }getchar();
    } while (choix!=0);
}

int main()
{
    char l[15],p[15];
    int essaie = 3;
    listecandidat *C=(listecandidat *)malloc(sizeof(listecandidat));
    C->first=NULL;
    C->last=NULL;
    listeoffre *O=(listeoffre *)malloc(sizeof(listeoffre));
    O->first=NULL;
    O->last=NULL;
    listerecrutement *R=(listerecrutement *)malloc(sizeof(listerecrutement));
    R->first=NULL;
    R->last=NULL;

    do{
    system("cls");
gotoxy(25,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(25,15);
printf("\xDB\xDB\xDB\xDB\xB2  Entrer Login : ");
scanf("%s",&l);
gotoxy(25,17);
printf("\xDB\xDB\xDB\xDB\xB2  Entrer Password : ");
scanf("%s",&p);
gotoxy(20,19);
    int Verfie = authentification(l,p);
    if (Verfie==1){
        getAll(&C,&O,&R);
        menu(&C,&O,&R);
    }else{
        essaie--;
gotoxy(25,10);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MANPOWER \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
gotoxy(25,15);
printf("\xDB\xDB\xDB\xDB\xB2  Login ou password erone ");
gotoxy(25,17);
printf("\xDB\xDB\xDB\xDB\xB2  il vous reste %d essaie \n\n\n",essaie);
        tryagain();
        getchar();
    }
    }while(essaie>0);

    if(essaie==0){
        system("cls");
        printf("\n\n\xDB\xDB\xDB\xDB\xB2  vous ne pouvez pas utiliser cette apllication :/");
        getchar();
    }
return 0;
}


