#ifndef CONFIG_H
#define CONFIG_H

// includes
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// constantes
#define	PASSWORD 1234
#define MAX_FIC_NOM 1000

#define VAL_UNSET -1

//#define IP_SSH "172.17.12.143" 		// a modifier par l'IP du BEAGLE BONE reseau ETU
//#define IP_SSH "172.18.5.160"           // a modifier par l'IP du BEAGLE BONE reseau PROF
//#define LOGIN_SSH "etudiant"              	// a modifier par le login root du BEAGLE BONE
//#define COMMANDE_SSH "/home/etudiant/mon_appli" 	// a modifier par la commande a executer sur le BEAGLE BONE
//#define NB_COMMANDE_SSH 5 		// a modifier par le nombre de fois a executer la commande sur le BEAGLE BONE


// structures

struct s_parametres
{
	char* 		query_string;	// chaine de parametres envoyés par le formulaire
	int		frm_type;	// type de formulaire (GET ou POST)
	int		nb_param; 	// nombre de paramètres renseignés
	char*		choix_capteur;	// identifiant du capteur
	float		val_min;	// valeur minimale possible
	float		val_max;	// valeur maximale possible
	int		range_lum;	// valeur du slider de lumiere
	char*		unite;	 	// celcius farenheit
	bool		on_off; 	// capteur actif ou non
	int		password; 	// valeur numérique du mot de passe sur 4 digits
	char		code_maison;	// lettre indiquant le code maison A B C ou D
};

// prototypes

void afficher_parametres(struct s_parametres* param);
void traiter_parametres(struct s_parametres* param);
float generer_valeur_aleatoire(float v_min, float v_max);

//void commande_objet(char code_maison, int numero_objet, bool etat);

#endif
