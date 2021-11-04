#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <windows.h>
#include "classe.h"

FILE *Pita;

// struct classe
// {
// 	int code;
// 	char nom[50]	;
// 	char niveau[50];
// 	//enum niveau mtb;
// };
// struct classe clas;



/* declaration d'une structure date_de_naissance */

struct datedenaissance 
{
	int mois;
	int annee;
	int jour;
};
struct datedenaissance;
	
/* declaration d'une structure etudiant pour gerer les info de l'etudiant */

struct etudiant 
{
	int identifiant;
	char nom[100];
	char prenom[100];
	char email[100];
	struct datedenaissance ttc; 
	struct classe cla;
};
struct etudiant etude;


void MenuEtudiant();
int  TrouveEtudiant(int code_etudiant);
void AjouterEtudiant();
void ModifierEtudiant();
void AfficherEtudiant();
void AfficherEtudiants();
void SupprimerEtudiant();
void MenuPrincipal();

void MenuNote();

#endif