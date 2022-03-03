#ifndef PARSING_H
#define PARSING_H

// includes
#include "config.h"

// constantes

#define	FRM_GET 1
#define	FRM_POST 2

#define DELIM_PARAM "&"
#define DELIM_AFF "="

#define MAXLEN 10000

// structures


// prototypes

void parse_formulaire(struct s_parametres* param);
void parse_param(struct s_parametres* param, char* data);
void parse_get(struct s_parametres* param);
void parse_post(struct s_parametres* param);

#endif
