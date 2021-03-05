#ifndef STRUCRURE_h
#define STRUCRURE_h

typedef struct candidat
{
    int     id;
    char    *nom;
    char    *prenom;
    char    *domaine;
    int     etat; // 1 recruté / 0 non recruté
    int     nb_exp;
}candidat;


typedef struct elementcandidat
{
    candidat   *data;
    struct      elementcandidat   *next;
}elementcandidat;

typedef struct listecandidat
{
    elementcandidat *first;
    elementcandidat *last;
}listecandidat;

typedef struct _SDate
{
    int jour;
    int mois;
    int annee;
}SDate;


typedef struct offre
{
    int       id;
    char      *entreprise;
    SDate     *date;
    char      *domaine;
    int        dispo; // 1 disponible / 0 non disponible
}offre;


typedef struct elementoffre
{
    offre      *data;
    struct      elementoffre *next;
}elementoffre;

typedef struct listeoffre
{
    elementoffre *first;
    elementoffre *last;
}listeoffre;


typedef struct recrutement
{
    int         id;
    int         offreidid;
    int         candidatid;
    char        *typecontrat;
    SDate       *daterecrut;
}recrutement;


typedef struct elementrecrutement
{
    recrutement        *data;
    struct      recrutement *next;
}elementrecrutement;


typedef struct listerecrutement
{
    elementrecrutement *first;
    elementrecrutement *last;
}listerecrutement;


typedef struct _SLogin
{
    char      *log;
    char      *pass;
}SLogin;


typedef struct _SElementLogin
{
    SLogin        *Login;
    struct      SElementLogin *suivant;
}SElementLogin;


typedef struct SElementLogin* ListeLogin;


#endif /* STRUCRURE_h */


