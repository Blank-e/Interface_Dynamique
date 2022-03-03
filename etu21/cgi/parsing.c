// includes
#include "parsing.h"

// detecte le type de formulaire (GET ou POST) et appel la fonction adaptée
void parse_formulaire(struct s_parametres* param){
	char* data=NULL;
	char* frm_method=NULL;

	// initialisation des valeurs a UNSET

	param->val_min=VAL_UNSET;
	param->val_max=VAL_UNSET;
	param->range_lum=VAL_UNSET;

	frm_method = getenv("REQUEST_METHOD");

	printf("REQUEST_METHOD : %s\n\n",frm_method);

	if(frm_method[0]=='G'){
		// GET
		param->frm_type=FRM_GET;
		parse_get(param);
	}else{
		if(frm_method[0]=='P'){
			// POST
			param->frm_type=FRM_POST;
			parse_post(param);
		}else{
			// ERREUR
			param=NULL;
		}
	}
}

// fonction qui parse une chaine de caractères et l'affecte dans la structure de parametres
void parse_param(struct s_parametres* param, char* data){

        char* chaine=NULL; // copie de la chaine pour parsing des delimiteurs
        char* param_chaine=NULL; // chaine complete pour un parametre
        char* param_nom=NULL; // nom du parametre
        char* param_valeur=NULL; // valeur du parametre

	param->query_string = strdup(data); // recopie la chaine originale en allouant la mémoire nécessaire 

	chaine = strdup(data);
	param->on_off = 0;

        // decouper la chaine en fonction des delimiteur entre parametres (&)
        while((param_chaine = strsep(&chaine, DELIM_PARAM)) != NULL){
                        // decouper la chaine lue en 2 morceau grace au délimiteur (=)
                        param_nom = strsep(&param_chaine, DELIM_AFF);
                        param_valeur = strsep(&param_chaine, DELIM_AFF);
                        //printf("Chaine complete : %s | nom param : %s | valeur param : %s \n\n",param_chaine, param_nom, param_valeur);
			if(strcmp(param_nom,"code_maison")==0)        	param->code_maison = param_valeur[0];
                        if(strcmp(param_nom,"choix_capteur")==0) 	param->choix_capteur = strdup(param_valeur);
                        if(strcmp(param_nom,"val_min")==0) 		sscanf(param_valeur,"%f",&param->val_min); 
                        if(strcmp(param_nom,"val_max")==0) 		sscanf(param_valeur,"%f",&param->val_max);
                        if(strcmp(param_nom,"range_lum")==0)            sscanf(param_valeur,"%d",&param->range_lum);
                        if(strcmp(param_nom,"unite")==0) 		param->unite = strdup(param_valeur);
                        if(strcmp(param_nom,"on_off")==0){
                                if(strcmp(param_valeur,"ON")==0 || strcmp(param_valeur,"On")==0 || strcmp(param_valeur,"on")==0){
                                        param->on_off = 1;
                                }else{
                                        param->on_off = 0;
                                }
                        }
                        if(strcmp(param_nom,"password")==0) 		sscanf(param_valeur,"%d",&param->password);
       }

}



// fonction qui parse le contenu envoyé par un formulaire GET et rempli les variables dans la structure param
void parse_get(struct s_parametres* param){
	// variables locales
	char* data=NULL; // chaine contenant la variable d'environnement avec les données du formulaire
	char* chaine=NULL; // copie de la chaine pour parsing des delimiteurs
	char* param_chaine=NULL; // chaine complete pour un parametre
	char* param_nom=NULL; // nom du parametre
	char* param_valeur=NULL; // valeur du parametre

	// lecture de la variable d'environnement contenant la chaine avec tous les paramètres du formulaire GET
	data = getenv("QUERY_STRING");

	if(data == NULL){
		// en cas d'erreur de lecture indiquer l'erreur et mettre param à NULL
                printf("ERREUR QUERY STRING MANQUANTE\n\n");
		param = NULL;
        }else{
                printf("QUERY_STRING lue : %s\n\n",data);

		param->frm_type=FRM_GET;
		param->query_string = strdup(data); // recopie la chaine originale en allouant la mémoire nécessaire 

		parse_param(param, data);

	}
}


// fonction pour le parsing de parametres en POST
void parse_post(struct s_parametres* param){
	char *lenstr;
	char input[MAXLEN], data[MAXLEN];
	long len=0;

	lenstr = getenv("CONTENT_LENGTH"); // lecture de la variable d'environnement indiquant la taille de la chaine à lire
	if(lenstr == NULL){
		// la variable d'environnement n'existe pas = pas de données envoyées
		printf("ERREUR, pas de données envoyées\n");
		return;
	}else{
		// tentative de lecture de la taille des données
		sscanf(lenstr,"%ld",&len);
		if(len==0 || len>MAXLEN){
			printf("ERREUR, taille des données envoyées incorrecte\n");
			return;
		}else{
			// il y a des données allouer un tableau pour le stockage
			printf("Taille des données : %ld \n", len);
			param->frm_type=FRM_POST;

			// lecture des données dans le flux d'input
			FILE *f;
			fgets(input, len+1, stdin);
			printf("Données lues : %s \n", input);

			parse_param(param, input);
		}
	}
}


