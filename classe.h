#ifndef CLASSE_H
#define CLASSE_H

#include <windows.h>


// struct SeFaire
// {
// 	struct matiere act1;
// 	struct classe act2;
// };
// struct SeFaire vari;

// enum niveau
	// {
	// 	Licence=0,Master=1
	// };

struct classe
{
	int code;
	char nom[50]	;
	char niveau[50];
	//enum niveau mtb;
};
struct classe clas;



void MenuClasse();
int TrouveClasse(int code_classe);
void AjouterClasse();
void ModifierClasse();
void AfficherClasse();
void AfficherClasses();
void SupprimerClasse();
void ActionPrincipal();

void MenuNote();

#endif