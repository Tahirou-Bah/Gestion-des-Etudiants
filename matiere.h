#ifndef MATIERE_H
#define MATIERE_H

#include <windows.h>
#include "classe.h"

FILE *Tounni;

struct SeFaire
{
	//struct matiere ref1;
	struct classe code1;
};
struct SeFaire vari;

struct matiere
{
	int reference;
	char libelle[50]	;
	int coefficent;
	//struct classe cl;
};
struct matiere mati;

void MenuMatiere();
int TrouveMatiere(int num_Rech);
void AjouterMatiere();
void ModifierMatiere();
void AfficherMatiere();
void AfficherMatieres();
void SupprimerMatiere();
void RetourPrincipal();

void MenuNote();

#endif