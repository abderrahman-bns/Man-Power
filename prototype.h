#ifndef PROTOTYPE_H
#define PROTOTYPE_H

///******************** date ********************///

SDate *CreerDate(int J,int M,int A);

void AfficherDate(char *c,SDate *d);

void SupprimerDate(SDate **d);

///******************** candidat ********************///

int ExisteCandidat(listecandidat *l,int code);

candidat *GetCandidat(listecandidat *L,int code);

candidat *CreerCandidat(int id,char *nom,char *prenom,char *domaine,int etat,int nb_exp);

elementcandidat *CreerElementCandidat(candidat *c);

void AjouterCandidat(listecandidat **L,elementcandidat *newElement);

void ModifierCandidat(listecandidat *l,int code,char *nom,char *prenom,char *domaine,int etat,int nb_exp);

int DeleteCandidat(listecandidat **l,int code);

void AfficherCandidat(candidat *c);

void AfficherTousCandidats(listecandidat *AllClient);

void AfficherOffresCandidat(listeoffre *l,candidat *c);

void AfficherCandidatsOffre(listecandidat *l,offre *o);

void DeListeAFichierCandidat(listecandidat *L);

void DeFichierAListeCandidat(listecandidat **L);

///******************** offre ********************///

int ExisteOffre(listeoffre *l,int code);

offre *CreerOffre(int index,char *entreprise,SDate *d,char *DP,int Dispo);

elementoffre *CreerElementOffre(offre *o);

offre *GetOffre(listeoffre *L,int code);

void AjouterOffre(listeoffre **l,elementoffre *newElement);

void ModifierOffre(listeoffre *L,int code,int J , int M , int A,char *entreprise_nom, char *DP,int Dispo);

int DeleteOffre(listeoffre **l,int code);

void AfficherOffre(offre *o);

void AfficherTousOffres(listeoffre *All);

void AfficherOffresCriteres(listeoffre *l, char *nom, char *specialite);

void CandidatsPotenOffre(listecandidat *l,offre *o);

void DeListeAFichierOffre(listeoffre *L);

void DeFichierAlisteOffre(listeoffre **L);

///******************** recrutement ********************///

int ExisteRecrutement(listerecrutement *L,int code);

recrutement *GetRecrutement(listerecrutement *L,int code);

recrutement *CreerRecrutement(int rec_index,int offre_index,int ca_index,char *type_Contrat,SDate *d);

elementrecrutement *CreerElementRecrutement(recrutement *Rec);

int DeleteRecrutement(listerecrutement **l, int code);

void AfficherRecutement(recrutement *r , listecandidat *lc , listeoffre *lo);

void AfficherTousRecrutement(listerecrutement *all,listeoffre *o,listecandidat *c);

void AjouterRecrutement(listerecrutement **L,elementrecrutement *newElement);

void DeListeAFichierRecrutement(listerecrutement *L);

void DeFichierAListeRecrutement(listerecrutement **L);

#endif /* PROTOTYPE_H */
