#include <stdio.h>
#include <stdlib.h>
#include "etudiant.h"
#include "classe.h"
#include "matiere.h"
	
// // /* declaration d'une structure etudiant pour gerer les info de l'etudiant */

void MenuEtudiant()
{
	system("color 40");
	int choix;

	viens_ici:
		printf("+------------------------------------------------------+\n");
		printf("|------------------|MENU_ETUDIANT|---------------------|\n");
		printf("|------------------------------------------------------|\n");
		printf("|  1) Ajouter un etudiant                              |\n");
		printf("|  2) Modifier un etudiant                             |\n");
		printf("|  3) Retrouver un etudiant                            |\n");
		printf("|  4) Afficher les etudiants                           |\n");
		printf("|  5) Supprimer un etudiant                            |\n");
		printf("|  6) Retour                                           |\n");
		printf("+------------------------FIN---------------------------+\n");	

		printf("Entrez votre choix: ");
		scanf("%d",&choix);

		switch(choix)
		{
			case 1:AjouterEtudiant();
			break;

			case 2:ModifierEtudiant();
			break;

			case 3:AfficherEtudiant();
			break;

			case 4:AfficherEtudiants();
			break;

			case 5:SupprimerEtudiant();
			break;

			case 6:MenuPrincipal();
			break;

			default:
			{
				printf("\nChoix Indisponible\n");
				printf("Recommencer\n");
				goto viens_ici;
			}
		}
}
	

/*-------------------Fonction qui recherche-----------------------*/
int TrouveEtudiant(int code_etudiant)
{
	struct etudiant etude;
	FILE *Pita;
	Pita=fopen("etudiant.csv","r");
	do
	{
		fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
		fflush(stdin);
		if (etude.identifiant == code_etudiant)
		{
			fclose(Pita);
			return 1;
		}
	}
	while(!feof(Pita));
	
	fclose(Pita);
	return -1;
}

/*------------------Fonction AjouterEtudiant--------------------------*/
void AjouterEtudiant()
{
	struct etudiant etude;
	FILE *Pita;
	int identi;
	Pita=fopen("etudiant.csv","a");
	fflush(stdin);

	printf("\nEntrer l'identifiant du nouveau etudiant: ");
	scanf("%d",&identi);
	fflush(stdin);

	while(TrouveEtudiant(identi) == 1)
	{
		printf("\nCe numero existe deja");
		printf("\nDonnez un autre numero: ");
		scanf("%d",&identi);
		fflush(stdin);
	}
	etude.identifiant = identi;
	fflush(stdin);

	printf("\nEntrez son nom: ");
	gets(etude.nom);
	fflush(stdin);

	printf("\nEntrez son prenom: ");
	gets(etude.prenom);
	fflush(stdin);
	
	printf("\nEntrez son email: ");
	gets(etude.email);
	fflush(stdin);

	printf("\nEntrez sa date de date_naissance sous format jj/jm/aa: ");
	do
	{
		scanf("%2d/%2d/%4d",&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee);
		fflush(stdin);
	}
	while(etude.ttc.jour > 31 && etude.ttc.mois > 12);

	printf("\nEntrez le code de sa classe: ");
	scanf("%d",&etude.cla.code);
	fflush(stdin);

	fprintf(Pita,"%d;%s;%s;%s;%d/%d/%d;%d \n",etude.identifiant,etude.nom,etude.prenom,etude.email,etude.ttc.jour,etude.ttc.mois,etude.ttc.annee,etude.cla.code);
	fclose(Pita);
	
	printf("L'ajout a bien reussie\n\n");
	MenuEtudiant();
}

/*---------------------Procedure Modification--------------------------------*/
void ModifierEtudiant()
{
	struct etudiant etude;
	int identifiant1;
	char reponse;

	FILE *Pita1, *Pita;
	Pita=fopen("etudiant.csv","r");
	Pita1=fopen("etudiant1.csv","a");

	printf("\nEntrez le numero de l'etudiant a modifie: ");
	scanf("%d",&identifiant1);
	fflush(stdin);

	if(TrouveEtudiant(identifiant1) == 1)
	{
		printf("\nVoulez-vous vraiment modfier cet etudiant o/n? ");
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse =='o' || reponse =='O')
		{		
			do
			{
				fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);

				if(identifiant1 == etude.identifiant)
				{
					printf("Donnez le nouveau identifiant de l'etudiant: ");
					scanf("%d",&identifiant1);
					fflush(stdin);
					etude.identifiant = identifiant1;

					printf("\nEntrez son nouveau nom: ");
					gets(etude.nom);
					fflush(stdin);

					printf("\nEntrez son nouveau prenom: ");
					gets(etude.prenom);
					fflush(stdin);

					printf("\nEntrez son nouveau email: ");
					gets(etude.email);
					fflush(stdin);

					printf("\nEntrez sa date de date_naissance sous format: jj/mm/aa: ");
					do
					{
						scanf("%2d/%2d/%4d",&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee);
						fflush(stdin);
					}
					while(etude.ttc.jour > 31 && etude.ttc.mois > 12);
					fflush(stdin);

					printf("\nEntrez son nouveau code de classe: ");
					scanf("%d",&etude.cla.code);
					fflush(stdin);

				}
				fprintf(Pita1,"%d;%s;%s;%s;%d/%d/%d;%d \n",etude.identifiant,etude.nom,etude.prenom,etude.email,etude.ttc.jour,etude.ttc.mois,etude.ttc.annee,etude.cla.code);
			}
			while(!feof(Pita));
				
			fclose(Pita);
			fclose(Pita1);
			remove("etudiant.csv");
			rename("etudiant1.csv","etudiant.csv");
			
			printf("\nModification reussie\n\n");
			MenuEtudiant();
		}
		else
		{
			printf("\nLa modifiaction a ete annule\n\n");
			MenuEtudiant();
		}
	}
	else
	{
		printf("\nCet identifiant n'existe pas du tout\n\n");
		MenuEtudiant();
	}
}

/*------------procedure Recherche et Affichage----------------------------*/
void AfficherEtudiant()
{
	struct etudiant etude;
	int NumR;
	printf("\nEntrez le numero de l'etudiant a rechercher: ");
	scanf("%d",&NumR);
	fflush(stdin);
	FILE *Pita;
	Pita=fopen("etudiant.csv","r");

	printf("\n+------------------------------------Informations sur l'etudiant---------------------------------------------+\n");
	printf("|------------------------------------------------------------------------------------------------------------|\n");
	printf("|Identifiant:|Nom:\t|Prenom:\t\t|Email:\t\t\t|Date_de_naissance: |Code_Classe     |\n");
	printf("|------------------------------------------------------------------------------------------------------------|\n");
	do
	{
		fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
		if( etude.identifiant == NumR)
		{
			printf("|%-13d",etude.identifiant);
			printf("%-11s",etude.nom);
			printf("%-24s",etude.prenom);
			printf("%-25s",etude.email);
			printf("%d/%d/%-20d",etude.ttc.jour,etude.ttc.mois,etude.ttc.annee);
			printf("%-10d|\n",etude.cla.code);
		}
	}while(!feof(Pita));
	printf("+------------------------------------------------------------------------------------------------------------+\n\n");
	fclose(Pita);
	MenuEtudiant();
}

/*-------------------------Procedure AfficherTout---------------------------------*/
void AfficherEtudiants()
{
	struct etudiant etude;
	int choi, codeClas;

	printf("\t\t1-Afficher les etudiants d'une meme clsse\n");
	printf("\t\t2-Afficher tous les etudiants\n");
	printf("Entrez votre choix: ");
	scanf("%d",&choi);
	fflush(stdin);

	FILE *Pita;
	Pita = fopen("etudiant.csv","r");

	switch(choi)
	{
		case 1:
		{
			printf("\nDonnez le code de la classe: ");
			scanf("%d",&codeClas);
			fflush(stdin);

			printf("\n\t\t\tLISTE DES ETUDIANTS\n");
			printf("+------------------------------------------------------------------------------------------------------------+\n");
			printf("|Identifiant:|Nom:\t|Prenom:\t\t|Email:\t\t\t|Date_de_naissance: |Code_Classe     |\n");
			printf("|------------------------------------------------------------------------------------------------------------|\n");
	
			do
			{
				fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
				fflush(stdin);
				if( codeClas == etude.cla.code )
				{
					printf("|%-13d",etude.identifiant);
					printf("%-11s",etude.nom);
					printf("%-24s",etude.prenom);
					printf("%-25s",etude.email);
					printf("%d/%d/%-20d",etude.ttc.jour,etude.ttc.mois,etude.ttc.annee);
					printf("%d\n",etude.cla.code);
					printf("+------------------------------------------------------------------------------------------------------------|\n\n");
				}
			}
			while(!feof(Pita));
			fclose(Pita);

			MenuEtudiant();
		}
		break;

		case 2:
		{
			printf("\n\t\t\tLISTE DES ETUDIANTS\n");
			printf("+------------------------------------------------------------------------------------------------------------+\n");
			printf("|Identifiant:|Nom:\t|Prenom:\t\t|Email:\t\t\t|Date_de_naissance: |Code_Classe     |\n");
			printf("|------------------------------------------------------------------------------------------------------------|\n");
	
			do
			{
				fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
				fflush(stdin);

				//printf("%d\t%s\t%s\t%s\t\t\t\t\t\t\t\t%d/%d/%d\t\t%d\n",etude.identifiant,etude.nom,etude.prenom,etude.email,etude.ttc.jour,etude.ttc.mois,etude.ttc.annee,etude.cla.code);
				printf("|%-13d",etude.identifiant);
				printf("%-11s",etude.nom);
				printf("%-24s",etude.prenom);
				printf("%-25s",etude.email);
				printf("%d/%d/%-20d",etude.ttc.jour,etude.ttc.mois,etude.ttc.annee);
				printf("%d\n",etude.cla.code);
				printf("+------------------------------------------------------------------------------------------------------------|\n\n");

			}
			while(!feof(Pita));
			fclose(Pita);

			//printf("+-------------------------------------------------------------------------------------------------------------|+\n\n");

			MenuEtudiant();
		}
		break;

		default:
		{
			printf("\n:::Choix incorrecte::::\n");
			MenuEtudiant();
		}
	}
}

/*-----------------------Procedure de Suppression-------------------------*/
void SupprimerEtudiant()
{
	struct etudiant etude;
	char reponse;
	int action;

	FILE *Pita1,*Pita;
	Pita=fopen("etudiant.csv","r");
	Pita1=fopen("etudiant1.csv","a");

	printf("\nEntrez l'identifiant de l'etudiant a Supprimer: ");
	scanf("%d",&action);
	fflush(stdin);

	if(TrouveEtudiant(action) == 1)
	{
		printf("\nVoulez-vous vraiment le supprimer o/n?  ");
		scanf("%c",&reponse);
		fflush(stdin);

		if(reponse == 'o' || reponse == 'O')
		{
			do
			{
				fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
				
				if(action != etude.identifiant)
				{
					fprintf(Pita1,"%d;%s;%s;%s;%d/%d/%d;%d \n",etude.identifiant,etude.nom,etude.prenom,etude.email,etude.ttc.jour,etude.ttc.mois,etude.ttc.annee,etude.cla.code);
				}
			}
			while(!feof(Pita));
			fclose(Pita1);
			fclose(Pita);

			remove("etudiant.csv");
			rename("etudiant1.csv","etudiant.csv");

			printf("Suppression reussie\n\n");
			MenuEtudiant();
		}

	}
	else
	{
		printf("\nCe numero n'existe pas\n\n");
		MenuEtudiant();
	}
}

/*----------------cette fonction reconduit au niveau du menu principal------*/
void MenuPrincipal()
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