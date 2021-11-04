#include <stdio.h>
#include <stdlib.h>
#include "classe.h"
#include "etudiant.h"
#include "matiere.h"

void MenuClasse()
{
	system("color 60");
	int decision;
	
	revien_ici:
		printf("+-----------------------------------------------------+\n");
		printf("|------------------|MENU_CLASSE|----------------------|\n");
		printf("|-----------------------------------------------------|\n");
		printf("|  1) Ajouter une classe                              |\n");
		printf("|  2) Modifier une classe                             |\n");
		printf("|  3) Retrouver une classe                            |\n");
		printf("|  4) Afficher toutes les classes                     |\n");
		printf("|  5) Supprimer une classe                            |\n");
		printf("|  6) Retour                                          |\n");
		printf("+-----------------------------------------------------+\n");	

		printf("Entrez votre choix: ");
		scanf("%d",&decision);

		switch(decision)
		{
			case 1:AjouterClasse();
			break;

			case 2:ModifierClasse();
			break;

			case 3:AfficherClasse();
			break;

			case 4:AfficherClasses();
			break;

			case 5:SupprimerClasse();
			break;

			case 6:ActionPrincipal();
			break;

			default:
			{
				printf("\nChoix indisponible\n");
				printf("Recommencer\n");
				goto revien_ici;
			}
		}
}
	

/*-------------------Fonction qui recherche-----------------------*/
int TrouveClasse(int code_classe)
{
	struct classe clas;
	FILE *Timbi;
	Timbi=fopen("classe.csv","r");
	do
	{
		fscanf(Timbi,"%d;%[a-zA-Z0-9 ];%[a-zA-Z] \n",&clas.code,clas.nom,clas.niveau);
		fflush(stdin);
		if (clas.code == code_classe)
		{
			fclose(Timbi);
			return 1;
		}
	}
	while(!feof(Timbi));
	fclose(Timbi);
	return -1;
}
/*------------------Fonction AjouterEtudiant--------------------------*/
void AjouterClasse()
{
	struct classe clas;
	FILE *Timbi;
	int code;
	Timbi=fopen("classe.csv","a");
	printf("\nEntrer l'code du nouveau classe: ");
	fflush(stdin);
	scanf("%d",&code);
	fflush(stdin);

	while(TrouveClasse(code) == 1)
	{
		printf("\nCe numero existe deja");
		printf("\nDonnez un autre numero: ");
		scanf("%d",&code);
		fflush(stdin);
	}
	clas.code=code;
	fflush(stdin);

	printf("\nEntrez son nom: ");
	gets(clas.nom);
	fflush(stdin);

	printf("Classe disponible\n");
	printf("* Licence\n");
	printf("* Master\n");
	printf("Entrez son niveau: ");
	gets(clas.niveau);
	fflush(stdin);

	fprintf(Timbi,"%d;%s;%s \n",clas.code,clas.nom,clas.niveau);
	fclose(Timbi);

	printf("L'ajout a bien reussie\n\n");
	MenuClasse();
}

/*---------------------Procedure Modification--------------------------------*/
void ModifierClasse()
{
	struct classe clas;
	int code;
	char reponse;

	FILE *TIMBI, *Timbi;
	Timbi=fopen("classe.csv","r");
	TIMBI=fopen("classe1.csv","a");

	printf("\nEntrez le numero de l'classe a modifie: ");
	scanf("%d",&code);
	fflush(stdin);

	if(TrouveClasse(code) == 1)
	{
		printf("\nVoulez-vous vraiment modfier cette classe o/n? ");
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse == 'o' || reponse == 'O')
		{	
			do
			{
				fscanf(Timbi,"%d;%[a-zA-Z0-9 ];%[a-zA-Z]\n",&clas.code,clas.nom,clas.niveau);
				if(code == clas.code)
				{
					printf("Donnez le nouveau code de la classe: ");
					scanf("%d",&code);
					fflush(stdin);
					clas.code = code;

					printf("\nEntrez son nouveau nom: ");
					gets(clas.nom);
					fflush(stdin);

					printf("Classe disponible\n");
					printf("* Licence\n");
					printf("* Master\n");
					printf("Entrez son niveau: ");
					gets(clas.niveau);
					fflush(stdin);
				}
				fprintf(TIMBI,"%d;%s;%s \n",clas.code,clas.nom,clas.niveau);
			}
			while(!feof(Timbi));	
			fclose(Timbi);
			fclose(TIMBI);
			remove("classe.csv");
			rename("classe1.csv","classe.csv");
				
			printf("\nModification reussie\n\n");
			MenuClasse();
		}
		else
		{
			printf("\nLa modifiaction a ete annule\n\n");
			MenuClasse();
		}
	}
	else
	{
		printf("\nCe numero n'existe pas du tout\n\n");
		MenuClasse();
	}
}

/*------------procedure Recherche et Affichage----------------------------*/
void AfficherClasse()
{
	struct classe clas;
	int aide;
	printf("\nEntrez le numero de l'classe a rechercher: ");
	scanf("%d",&aide);
	FILE *Timbi;
	Timbi=fopen("classe.csv","r");
		
	printf("+-----------Information sur l'classe-----------+\n");
	printf("|----------------------------------------------|\n");
	printf("|Code\t|\tNom\t|\tNiveau\t       |\n");
	printf("|----------------------------------------------|\n");
	do
	{
		fscanf(Timbi,"%d;%[a-zA-Z0-9 ];%[a-zA-Z] \n",&clas.code,clas.nom,clas.niveau);
		if( clas.code == aide )
		{
			printf("|%-11d",clas.code);
			printf("%-19s",clas.nom);
			printf("%-16s|\n",clas.niveau);
		}
		// else
		// 	printf("Cette classe est deja absente\n");
	}
	while(!feof(Timbi));
	printf("+----------------------------------------------+\n\n");
	fclose(Timbi);
	MenuClasse();
}

/*-------------------------Procedure AfficherTout---------------------------------*/
void AfficherClasses()
{
	struct classe clas;
	FILE *Timbi;
	Timbi=fopen("classe.csv","r");
	printf("\nLISTE DES CLASSES \n");
	printf("\n+-----------Information sur l'classe-----------+\n");
	printf("|----------------------------------------------|\n");
	printf("|Code\t|\tNom\t|\tNiveau\t       |\n");
	printf("|----------------------------------------------|\n");
	do
	{
		fscanf(Timbi,"%d;%[a-zA-Z0-9 ];%[a-zA-Z] \n",&clas.code, clas.nom, clas.niveau);

		printf("|%-13d", clas.code);
		printf("%-17s",clas.nom);
		printf("%-16s|\n",clas.niveau);
		printf("+----------------------------------------------+\n");
	}
	while(!feof(Timbi));
	fclose(Timbi);
	printf("\n");
	MenuClasse();
}
/*-----------------------Procedure de Suppression-------------------------*/
void SupprimerClasse()
{
	struct classe clas;
	char reponse;
	int code;

	printf("\nEntrez l'code de l'classe a Supprimer: ");
	scanf("%d",&code);
	fflush(stdin);

	if(TrouveClasse(code) == 1)
	{
		printf("Voulez-vous vraiment le supprimer o/n ? ");
		fflush(stdin);
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse =='o' || reponse =='O')
		{
			FILE *TIMBI, *Timbi;
			Timbi=fopen("classe.csv","r");
			TIMBI=fopen("classe1.csv","a");

			do
			{
				fscanf(Timbi,"%d;%[a-zA-Z0-9 ];%[a-zA-Z] \n",&clas.code,clas.nom,clas.niveau);
				if(clas.code != code)
				{
					fprintf(TIMBI,"%d;%s;%s \n",clas.code,clas.nom,clas.niveau);
				}
			}
			while(!feof(Timbi));
			fclose(TIMBI);
			fclose(Timbi);

			remove("classe.csv");
			rename("classe1.csv","classe.csv");
			printf("\nSuppression reussie\n\n");
			MenuClasse();
		}

	}
	else
	{
		printf("\nCe numero n'existe pas\n");
	}
}

/*----------------cette fonction reconduit au niveau du menu principal------*/
void ActionPrincipal()
{
	system("color 01");
	int choix;
	char rep;

	system("cls");
	ici:
		printf("+================MENU_PRINCIPAL==============+\n");
		printf("|                                            |\n");
		printf("|    1) Gestion des etudiants                |\n");
		printf("|    2) Gestion des classes                  |\n");
		printf("|    3) Gestion des matieres                 |\n");
		printf("|    4) Gestion des notes                    |\n");
		printf("|    5) Quitter                              |\n");
		printf("|                                            |\n");
		printf("+============================================+\n");


		printf("Entrez votre choix: ");
		scanf("%d",&choix);

	switch(choix)
	{
		case 1:
		{
			// printf("\nAffichage du menu etudiant\n");
			MenuEtudiant();
		}
		break;

		case 2:
		{
			// printf("\nAffichage du menu classe\n");
			MenuClasse();
		}
		break;

		case 3:
		{
			// printf("\nAffichage du menu matiere\n");
			MenuMatiere();
		}
		break;

		case 4:
		{
			// printf("\nAffichage du menu pour les notes\n");
			MenuNote();
		}
		break;

		case 5:
			printf("\nFin Du Programme\n");
		break;

		default:
		{
			printf("\nVotre choix n'existe pas\n");
			printf("Voulez-vous recommencer: ");
			fflush(stdin);
			scanf("%c",&rep);

			if ( rep == 'o' || rep == 'O')
			{
				goto ici;
			}
			else
				exit(1);
		}
	}
}
