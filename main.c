#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "etudiant.h"
#include "classe.h"
#include "matiere.h"

void MenuNote();
void AjoutNote();
void ModificationNote();
void ConsulteNote();
void SupprimeNote();
void RuckwegPrincipal();

struct noter
{
	struct etudiant etu;
	struct matiere mat;
	float noteCC;
	float noteDS;
	
};
struct noter note;


int main(int argc, char const *argv[])
{
	int choix;
	char rep;

	system("cls");
	system("color 01");

	ici:
		printf("\n");
		printf("\t+====================BIENVENUE=================+\n");
		printf("\t||                                            ||\n");
		printf("\t||    1) Gestion des etudiants                ||\n");
		printf("\t||    2) Gestion des classes                  ||\n");
		printf("\t||    3) Gestion des matieres                 ||\n");
		printf("\t||    4) Gestion des notes                    ||\n");
		printf("\t||    5) Quitter                              ||\n");
		printf("\t||                                            ||\n");
		printf("\t+==============================================+\n");


		printf("Entrez votre choix: ");
		scanf("%d",&choix);

	switch(choix)
	{
		case 1:
		{
			//printf("\nAffichage du menu etudiant\n");
			MenuEtudiant();
		}
		break;

		case 2:
		{
			//printf("\nAffichage du menu classe\n");
			MenuClasse();
		}
		break;

		case 3:
		{
			//printf("\nAffichage du menu matiere\n");
			MenuMatiere();
		}
		break;

		case 4:
		{
			//printf("\nAffichage du menu pour les notes\n");
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


	return 0;
}

void MenuNote()
{
	system("color 50");
	int desir;

	viens_ici:
		printf("+------------------------------------------------------+\n");
		printf("|---------------------|MENU_NOTE|----------------------|\n");
		printf("|------------------------------------------------------|\n");
		printf("|  1) Ajout des notes                                  |\n");
		printf("|  2) Modification des notes                           |\n");
		printf("|  3) Consulter les notes                              |\n");
		printf("|  4) Supression ses notes                             |\n");
		printf("|  5) Retour                                           |\n");
		printf("+------------------------FIN---------------------------+\n");	

		printf("Entrez votre choix: ");
		scanf("%d",&desir);

		switch(desir)
		{
			case 1:
			{
				AjoutNote();
			}
			break;

			case 2:
			{
				ModificationNote();
			}
			break;

			case 3:
			{
				ConsulteNote();
			}
			break;

			case 4:
			{
				SupprimeNote();
			}
			break;

			case 5:
				RuckwegPrincipal();
			break;
				
			default:
			{
				printf("\nChoix Indisponible\n");
				printf("Recommencer\n");
				goto viens_ici;
			}
		}
}


void AjoutNote()
{
	struct noter note;
	int choix1;

	printf("\t\t1: Pour un etudiant dans une matiere\n");
	printf("\t\t2: Pour tous les etudiants d'une classe dans une matiere\n");
	printf("\t\t9: Accueil\n");
	printf("Votre choix: ");
	scanf("%d",&choix1);

	switch(choix1)
	{
		case 1:
		{
			//int numero, refe;
			FILE *Centre;
			Centre = fopen("note.csv","a");

			printf("\nDonnez le numero de l'etudiant: ");
			scanf("%d",&note.etu.identifiant);

			if( TrouveEtudiant(note.etu.identifiant) == 1 )
			{
				printf("Donnez la refernce de la matiere: ");
				scanf("%d",&note.mat.reference);
				fflush(stdin);

				if( TrouveMatiere(note.mat.reference) == 1 )
				{
					printf("\nDonnez la notre CC : ");
					scanf("%f",&note.noteCC);
					fflush(stdin);

					printf("Donnez la note DS: ");
					scanf("%f",&note.noteDS);
					fflush(stdin);

					printf("Donnez le code de sa classe: ");
					scanf("%d",&note.etu.cla.code);

				}
				else
				{
					printf("\nCette matiere n'existe pas \n");
					break;
				}
			}
			else
			{
				printf("\nCet etudiant n'existe pas \n");
				break;
			}
			fprintf(Centre,"%d;%d;%.2f;%.2f;%d \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS,note.etu.cla.code);
			fclose(Centre);

			printf("L'ajout a bien reussie\n\n");
			MenuNote();
		}
		break;

		case 2:
		{
			int numero1;
			FILE *Centre;
			Centre = fopen("note.csv","a");

			printf("\nDonnez le code de l'classe: ");
			scanf("%d",&numero1);
			fflush(stdin);
			do
			{
				if( numero1 == note.etu.cla.code )
				{
					note.etu.cla.code = numero1;
					printf("\nDonnez le numero de l'etudiant: ");
					scanf("%d",&note.etu.identifiant);
					fflush(stdin);
					printf("Donnez la refernce de la matiere: ");
					scanf("%d",&note.mat.reference);
					fflush(stdin);

					printf("\nDonnez la notre CC : ");
					scanf("%f",&note.noteCC);
					fflush(stdin);
					printf("Donnez la note DS: ");
					scanf("%f",&note.noteDS);
					fflush(stdin);

					//fprintf(centre,"%d;%d;%.2f;%.2f \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS);
				}
				fprintf(Centre,"%d;%d;%.2f;%.2f;%d \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS,note.etu.cla.code);
			}
			while(!feof(Centre));
			fclose(Centre);

			printf("L'ajout a bien reussie\n\n");
			MenuNote();
		}
		break;

		case 9:
		{
			printf("\n");
			MenuNote();
		}
		break;

		default:
		{
			printf(":::Choix incorrecte:::\n");
			MenuNote();
		}
	}
}


void ModificationNote()
{
	struct noter note;
	int choix2;

	printf("\t\t1: Pour un etudiant dans une matiere\n");
	printf("\t\t2: Pour tous les etudiants d'une classe dans une matiere\n");
	printf("\t\t9: Accueil\n");
	printf("Votre choix: ");
	scanf("%d",&choix2);

	switch(choix2)
	{
		case 1:
		{
			int numero, refe;
			FILE *Centre, *CENTRE;
			Centre = fopen("note.csv","r");
			CENTRE = fopen("note1.csv","a");

			printf("\nDonnez le numero de l'etudiant afin de modifier sa note: ");
			scanf("%d",&numero);
			fflush(stdin);
			printf("Donnez la refernce de la matiere: ");
			scanf("%d",&refe);
			fflush(stdin);

			if( TrouveEtudiant(numero) == 1 && TrouveMatiere(refe) == 1)
			{
				do
				{
					fscanf(Centre,"%d;%d;%f;%f;%d \n",&note.etu.identifiant,&note.mat.reference,&note.noteCC,&note.noteDS,&note.etu.cla.code);
					if(numero == note.etu.identifiant)
					{
						printf("Donnez la nouvelle notre CC : ");
						scanf("%f",&note.noteCC);
						fflush(stdin);
						printf("Donnez la nouvelle note DS: ");
						scanf("%f",&note.noteDS);
						fflush(stdin);
					}
					fprintf(CENTRE,"%d;%d;%.2f;%.2f;%d \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS,note.etu.cla.code);
				}
				while(!feof(Centre));
			}
			fprintf(Centre,"%d;%d;%.2f;%.2f \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS);
			fclose(Centre);
			fclose(CENTRE);

			remove("note.csv");
			rename("note1.csv","note.csv");

			printf("L'ajout a bien reussie\n\n");
			MenuNote();
		}
		break;

		case 2:
		{

		}
		break;

		case 9:
		{
			printf("\n");
			MenuNote();
		}
		break;

		default:
		{
			printf(":::Choix incorrecte:::\n");
			MenuNote();
		}
	}
}

void ConsulteNote()
{
	struct noter note;
	int  choix3;

	printf("\t\t1: Pour un etudiant dans une matiere\n");
	printf("\t\t2: Pour les etudiants d'une classe dans une matiere\n");
	printf("\t\t9: Accueil\n");
	printf("Votre choix: ");
	scanf("%d",&choix3);

	switch(choix3)
	{
		case 1:
		{
			int val1, val2;
			FILE *Centre;
			Centre = fopen("note.csv","r");

			printf("\nDonnez le numero de l'etudiant pour voir ses notes: ");
			scanf("%d",&val1);
			fflush(stdin);
			printf("Donnez egalement la refernce de la matiere: ");
			scanf("%d",&val2);
			fflush(stdin);

			printf("\n+-------Information sur les notes d'un etudiant--------+\n");
			printf("|------------------------------------------------------|\n");
			printf("| Code_Etudiant| Code_Matiere | NoteCC | NoteDS        |\n");
			printf("|------------------------------------------------------|\n");

			do
			{
				fscanf(Centre,"%d;%d;%f;%f;%d \n",&note.etu.identifiant,&note.mat.reference,&note.noteCC,&note.noteDS,&note.etu.cla.code);
				if(note.etu.identifiant == val1 && note.mat.reference == val2)
				{
					printf("| %-16d",note.etu.identifiant);
					printf("%-15d",note.mat.reference);
					printf("%-12.2f",note.noteCC);
					printf("%-10.2f|\n",note.noteDS);
				}
			}
			while(!feof(Centre));
			printf("+------------------------------------------------------+\n\n");
			fclose(Centre);

			MenuNote();
		}
		break;

		case 2:
		{
			int val3;
			FILE *Centre;
			Centre = fopen("note.csv","r");

			printf("\nDonnez le code dee la classe pour voir les notes: ");
			scanf("%d",&val3);
			fflush(stdin);
			// printf("Donnez egalement la refernce de la matiere: ");
			// scanf("%d",&note.mat.reference);
			// fflush(stdin);

			printf("\n+----------Information sur les notes d'un etudiant--------------+\n");
			printf("|---------------------------------------------------------------|\n");
			printf("| Code_Etudiant| Code_Matiere | NoteCC | NoteDS   | Code_Classe |\n");
			printf("|---------------------------------------------------------------|\n");

			do
			{
				fscanf(Centre,"%d;%d;%f;%f;%d \n",&note.etu.identifiant,&note.mat.reference,&note.noteCC,&note.noteDS,&note.etu.cla.code);
				fflush(stdin);
				//fscanf(Pita,"%d;%[a-zA-Z];%[a-zA-Z ];%[a-zA-Z0-9@.];%2d/%2d/%4d;%d \n",&etude.identifiant,etude.nom,etude.prenom,etude.email,&etude.ttc.jour,&etude.ttc.mois,&etude.ttc.annee,&etude.cla.code);
				//fflush(stdin);
				if(val3 == note.etu.cla.code )
				{
					printf("| %-16d",note.etu.identifiant);
					printf("%-15d",note.mat.reference);
					printf("%-10.2f",note.noteCC);
					printf("%-13.2f",note.noteDS);
					printf("%-8d|\n",note.etu.cla.code);
				}
			}
			while(!feof(Centre));
			printf("+---------------------------------------------------------------+\n\n");
			fclose(Centre);

			MenuNote();
		}
		break;

		case 9:
		{
			printf("\n");
			MenuNote();
		}
		break;

		default:
		{
			printf(":::Choix incorrecte:::\n");
			MenuNote();
		}
	}
}

void SupprimeNote()
{
	struct noter note;
	int  choix4;

	printf("\t\t1: Pour un etudiant dans une matiere\n");
	printf("\t\t2: Pour tous les etudiants d'une classe dans une matiere\n");
	printf("\t\t9: Accueil\n");
	printf("Votre choix: ");
	scanf("%d",&choix4);

	switch(choix4)
	{
		case 1:
		{
			int leCode, laRef;
			FILE *Centre, *CENTRE;
			Centre = fopen("note.csv","r");
			CENTRE = fopen("note1.csv","a");

			printf("\nDonnez le numero de l'etudiant: ");
			scanf("%d",&leCode);
			fflush(stdin);
			printf("Donnez la refernce de la matiere: ");
			scanf("%d",&laRef);
			fflush(stdin);

			if( TrouveEtudiant(leCode) == 1 && TrouveMatiere(laRef) == 1 )
			{
				do
				{
					fscanf(Centre,"%d;%d;%f;%f;%d \n",&note.etu.identifiant,&note.mat.reference,&note.noteCC,&note.noteDS,&note.etu.cla.code);
					if( leCode != note.etu.identifiant)
					{
						fprintf(CENTRE,"%d;%d;%.2f;%.2f;%d \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS,note.etu.cla.code);
					}
				}
				while(!feof(Centre));
				fclose(CENTRE);
				fclose(Centre);

				remove("note.csv");
				rename("note1.csv","note.csv");

				printf("Suppression reussi\n\n");
				MenuNote();
			}
			else
			{
				printf("\nCe numero n'existe pas\n\n");
				MenuNote();
			}
		}
		break;

		case 2:
		{
			int laCode, laRefe;
			FILE *Centre, *CENTRE;
			Centre = fopen("note.csv","r");
			CENTRE = fopen("note1.csv","a");

			printf("\nDonnez le code etudiant: ");
			scanf("%d",&laCode);
			fflush(stdin);
			printf("Donnez la refernce de la matiere: ");
			scanf("%d",&laRefe);
			fflush(stdin);

			if( TrouveClasse(laCode) == 1 && TrouveMatiere(laRefe) == 1 )
			{
				do
				{
					fscanf(Centre,"%d;%d;%f;%f;%d \n",&note.etu.identifiant,&note.mat.reference,&note.noteCC,&note.noteDS,&note.etu.cla.code);
					if( laCode != note.etu.cla.code)
					{
						fprintf(CENTRE,"%d;%d;%.2f;%.2f;%d \n",note.etu.identifiant,note.mat.reference,note.noteCC,note.noteDS,note.etu.cla.code);
					}
				}
				while(!feof(Centre));
				fclose(CENTRE);
				fclose(Centre);

				remove("note.csv");
				rename("note1.csv","note.csv");

				printf("Suppression reussi\n\n");
				MenuNote();
			}
			else
			{
				printf("\nCe numero n'existe pas\n\n");
				MenuNote();
			}
		}
		break;

		case 9:
		{
			printf("\n");
			MenuNote();
		}
		break;

		default:
		{
			printf(":::Choix incorrecte:::\n");
			MenuNote();
		}
	}
}

/*----------------cette fonction reconduit au niveau du menu principal------*/
void RuckwegPrincipal()
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