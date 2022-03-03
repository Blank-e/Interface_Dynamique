// includes
#include "config.h"
#include "parsing.h"

// fonction principale
int main(void){

	struct s_parametres* param; // structure contenant les parametres parses envoyes par le formulaires HTML
	param = malloc(sizeof(struct s_parametres));
	
	// creation d'une structure vide pour contenir les parametres
	// TODO
	
	printf("Content-Type: text/plain \n\n");
	printf("CGI C Capteur Configuration \n\n");

	// lecture des donnees du formulaire
	parse_formulaire(param);

	// affichage des donnees du formulaire
	afficher_parametres(param);

	// traitement des donnees du formulaire
	traiter_parametres(param);
	free(param);
	return EXIT_SUCCESS;
}

void afficher_parametres(struct s_parametres* param){
	if ((param->frm_type)==1){
		//printf("QUERY_STRING lue :%s\n\n",param->query_string);
		//printf("*** FORMULAIRE %s ***\n\n",param->frm_type);
		printf("Capteur : %s\n",param->choix_capteur);
		printf("Min/Max : %f / %f %s\n",param->val_min,param->val_max,param->unite);
		printf("Actif : %d\n",param->nb_param);
		
	}
	else{
		//printf("QUERY_STRING lue :%s\n\n",param->query_string);
		//printf("*** FORMULAIRE %s ***\n\n",param->frm_type);
		printf("Capteur : %s\n",param->choix_capteur);
		printf("Range lum : %d\n",param->range_lum);
		printf("Code maison : %c\n", param->code_maison);
		printf("Actif : %d\n",param->nb_param);

	}
}

float generer_valeur_aleatoire(float v_min, float v_max){
	// TODO
	float nbr_aleatoire;
	nbr_aleatoire=(rand()/(double)RAND_MAX)*(v_max-v_min)+v_min;

	return nbr_aleatoire;
}

/*
void commande_objet(char code_maison, int numero_objet, bool etat){
	// PAS DE BEAGLEBONE CETTE ANNEE
	// CETTE FONCTION N'EST PAS A CODER CETTE ANNEE
}
*/

void traiter_parametres(struct s_parametres* param){
	FILE* fichier= NULL;
	if((param->password)==PASSWORD){
		if ((param->frm_type)==1){
			printf("Mot de passe : OK");
			float nbr_aleatoire=generer_valeur_aleatoire(param->val_min,param->val_max);
			if (strcmp("temp1",param->choix_capteur)==0){
				fichier= fopen("../data/temp1.txt","w+");
				fprintf(fichier,"%.2f",nbr_aleatoire);
				fclose(fichier);
			}
			if (strcmp("temp2",param->choix_capteur)==0){
				fichier= fopen("../data/temp2.txt","w+");
				fprintf(fichier,"%.2f",nbr_aleatoire);
				fclose(fichier);
			}
			if (strcmp("temp3",param->choix_capteur)==0){
				fichier= fopen("../data/temp3.txt","w+");
				fprintf(fichier,"%.2f",nbr_aleatoire);
				fclose(fichier);
			}

			
		}
		else{
			if (strcmp("lum1",param->choix_capteur)==0){
				fichier= fopen("../data/lum1.txt","w+");
				fprintf(fichier,"%d",param->range_lum);
				fclose(fichier);
			}
			if (strcmp("lum2",param->choix_capteur)==0){
				fichier= fopen("../data/lum2.txt","w+");
				fprintf(fichier,"%d",param->range_lum);
				fclose(fichier);
			}
			if (strcmp("lum3",param->choix_capteur)==0){
				fichier= fopen("../data/lum3.txt","w+");
				fprintf(fichier,"%d",param->range_lum);
				fclose(fichier);
			}
		}
	}
	else{
		printf("Mot de passe : KO");
	}
}
