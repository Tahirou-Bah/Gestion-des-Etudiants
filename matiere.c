#include <stdio.h>
#include <stdlib.h>
#include "matiere.h"
#include "etudiant.h"
#include "classe.h"


void MenuMatiere()
{
	system("color 20");
	int choix;

	revien_la:
		printf("+------------------------------------------------------+\n");
		printf("|--------------------|MENU_MATIERE|--------------------|\n");
		printf("|------------------------------------------------------|\n");
		printf("|  1) Ajouter une matiere                              |\n");
		printf("|  2) Modifier une matiere                             |\n");
		printf("|  3) Retrouver une matiere                            |\n");
		printf("|  4) Afficher toutes les matieres                     |\n");
		printf("|  5) Supprimer un matiere                             |\n");
		printf("|  6) Retour                                           |\n");
		printf("+-----------------------FIN----------------------------+\n");	

		printf("Entrez votre choix: ");
		scanf("%d",&choix);

		switch(choix)
		{
			case 1:AjouterMatiere();
			break;

			case 2:ModifierMatiere();
			break;

			case 3:AfficherMatiere();
			break;

			case 4:AfficherMatieres();
			break;

			case 5:SupprimerMatiere();
			break;

			case 6:RetourPrincipal();
			break;

			default:
			{
				printf("\nChoix indisponible\n");
				printf("Recommencer\n");
				goto revien_la;
			}
		}
}
	

/*-------------------Fonction qui recherche-----------------------*/
int TrouveMatiere(int num_Rech)
{
	struct matiere mati;
	FILE *Tounni;
	Tounni = fopen("matiere.csv","r");
	do
	{
		fscanf(Tounni,"%d;%[a-zA-Z ];%d;%d \n",&mati.reference,mati.libelle,&mati.coefficent,&vari.code1.code);
		fflush(stdin);
		if (mati.reference == num_Rech)
		{
			fclose(Tounni);
			return 1;
		}
	}
	while(!feof(Tounni));

	fclose(Tounni);
	return -1;
}

/*------------------Fonction AjouterMatiere--------------------------*/
void AjouterMatiere()
{
	struct matiere mati;
	struct SeFaire vari;
	FILE *Tounni;
	int ref;

	Tounni = fopen("matiere.csv","a");

	printf("\nEntrer l'reference de la nouvelle matiere: ");
	scanf("%d",&ref);
	fflush(stdin);

	while(mati.reference == ref)
	{
		printf("\nCe numero existe deja");
		printf("\nDonnez un autre numero: ");
		scanf("%d",&ref);
		fflush(stdin);
	}

	mati.reference = ref;
		
	printf("\nEntrez le libelle de la matiere: ");
	gets(mati.libelle);
	fflush(stdin);

	printf("\nEntrez le coefficent de la matiere: ");
	scanf("%d",&mati.coefficent);
	fflush(stdin);

	printf("\nEntrez le code de la classe ou se deroule la matiere: ");
	scanf("%d",&vari.code1.code);
	fflush(stdin);


	fprintf(Tounni,"%d;%s;%d;%d \n",mati.reference,mati.libelle,mati.coefficent,vari.code1.code);
	fclose(Tounni);

	printf("L'ajout a bien reussie\n\n");
	MenuMatiere();
}

/*---------------------Procedure Modification--------------------------------*/
void ModifierMatiere()
{
	struct matiere mati;
	int referencio;
	char reponse;
	FILE *TOUNNI, *Tounni;

	printf("\nEntrez le numero de l'matiere a modifie: ");
	scanf("%d",&referencio);
	fflush(stdin);

	if(TrouveMatiere(referencio) == 1)
	{
		printf("\nVoulez-vous vraiment modfier cet matiere o/n? ");
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse == 'o' || reponse == 'O')
		{
			Tounni=fopen("matiere.csv","r");
			TOUNNI=fopen("matiere1.csv","a");
				
			do
			{
				fscanf(Tounni,"%d;%[a-zA-Z ];%d;%d \n",&mati.reference,mati.libelle,&mati.coefficent,&vari.code1.code);

				if(referencio == mati.reference)
				{
					printf("\nEntrez la nouvelle reference de la matiere: ");
					scanf("%d",&referencio);
					fflush(stdin);
					mati.reference = referencio;

					printf("\nEntrez le nouveau libelle de la matiere: ");
					gets(mati.libelle);
					fflush(stdin);

					printf("\nEntrez le nouveau coefficent de la matiere: ");
					scanf("%d",&mati.coefficent);
					fflush(stdin);

					printf("\nEntrez la nouvelle classe cible: ");
					scanf("%d",&vari.code1.code);
					fflush(stdin);
				}
				fprintf(TOUNNI,"%d;%s;%d;%d \n",mati.reference,mati.libelle,mati.coefficent,vari.code1.code);
			}
			while(!feof(Tounni));
			
			fclose(Tounni);
			fclose(TOUNNI);
			remove("matiere.csv");
			rename("matiere1.csv","matiere.csv");
				
			printf("\nModification reussie\n\n");
			MenuMatiere();
		}
		else
		{
			printf("\nLa modifiaction a ete annule\n\n");
			MenuMatiere();
		}
	}
	else
	{
		printf("\nCe numero n'existe pas du tout\n\n");
		MenuMatiere();
	}
}

/*------------procedure Recherche et Affichage----------------------------*/
void AfficherMatiere()
{
	struct matiere mati;
	int numro;

	printf("\nEntrez le numero de l'matiere a rechercher: ");
	scanf("%d",&numro);
	fflush(stdin);
	
	FILE *Tounni;
	Tounni=fopen("matiere.csv","r");

	printf("+---------------Information sur l'matiere-------------------+\n");
	printf("|-----------------------------------------------------------|\n");
	printf("| Reference | Libelle\t\t| Coefficent | Code_Classe  |\n");
	printf("|-----------------------------------------------------------|\n");
	do
	{
		fscanf(Tounni,"%d;%[a-zA-Z ];%d;%d \n",&mati.reference,mati.libelle,&mati.coefficent,&vari.code1.code);
		if( mati.reference == numro )
		{
			printf("|%-13d",mati.reference);
			printf("%s       ",mati.libelle);
			printf("%-14d",mati.coefficent);
			printf("%-8d|\n",vari.code1.code);
		}
	}
	while(!feof(Tounni));
	printf("+-----------------------------------------------------------+\n\n");
	fclose(Tounni);
	MenuMatiere();
}

/*-------------------------Procedure AfficherTout---------------------------------*/
void AfficherMatieres()
{
	struct matiere mati;
	FILE *Tounni;
	Tounni=fopen("matiere.csv","r");

	printf("\n\t\tLISTE DES MATIERES\n");
	printf("+--------------------------------------------------------------+\n");
	printf("|Reference |  Libelle \t\t|  Coefficient \t|  Code_Classe |\n");
	printf("|--------------------------------------------------------------|\n");

	do
	{
		fscanf(Tounni,"%d;%[a-zA-Z ];%d;%d \n",&mati.reference,mati.libelle,&mati.coefficent,&vari.code1.code);
		fflush(stdin);

		printf("|%-12d",mati.reference);
		printf("%-25s",mati.libelle);
		printf("%-15d",mati.coefficent);
		printf("%-10d\n",vari.code1.code);
		printf("---------------------------------------------------------------|\n\n");
		//printf("|%d\t\t%s\t\t%d\n",mati.reference,mati.libelle,mati.coefficent);
	}
	while(!feof(Tounni));
	fclose(Tounni);

	MenuMatiere();
}

/*-----------------------Procedure de Suppression-------------------------*/
void SupprimerMatiere()
{
	struct matiere mati;
	char reponse;
	int refer;


	FILE *TOUNNI, *Tounni;
	Tounni=fopen("matiere.csv","r");
	TOUNNI=fopen("matiere1.csv","a");

	printf("\nEntrez l'reference de l'matiere a Supprimer: ");
	scanf("%d",&refer);
	fflush(stdin);

	if(TrouveMatiere(refer) == 1)
	{ 
		printf("\nVoulez-vous vraiment le supprimer o/n?  ");
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse == 'o' || reponse == 'O')
		{
			do
			{
				fscanf(Tounni,"%d;%[a-zA-Z ];%d;%d \n",&mati.reference,mati.libelle,&mati.coefficent,&vari.code1.code);
				if(refer != mati.reference)
				{
					fprintf(TOUNNI,"%d;%s;%d;%d \n",mati.reference,mati.libelle,mati.coefficent,vari.code1.code);
				}
			}
			while(!feof(Tounni));
			fclose(TOUNNI);
			fclose(Tounni);

			remove("matiere.csv");
			rename("matiere1.csv","matiere.csv");
			printf("\nSuppression reussie\n\n");
			MenuMatiere();
		}
	}
	else
	{
		printf("\nCe numero n'existe pas\n\n");
		MenuMatiere();
	}
}

/*----------------cette fonction reconduit au niveau du menu principal------*/
void RetourPrincipal()
{
	system("color 01");
	int choix;
	char rep;

	system("cls");
	ici:
		printf("+===============MENU_PRINCIPAL===============+\n");
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
