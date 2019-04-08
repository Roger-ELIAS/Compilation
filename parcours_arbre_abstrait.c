#include <stdio.h>
#include "syntabs.h"
#include "util.h"
#include "tabsymboles.h"
#include "code3a.h"
#include <string.h>
#include <stdlib.h>

void parcours_n_prog(n_prog *n);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
void parcours_l_exp(n_l_exp *n);
operande* parcours_exp(n_exp *n);
operande* parcours_varExp(n_exp *n);
operande* parcours_opExp(n_exp *n);
operande* parcours_intExp(n_exp *n);
operande* parcours_lireExp(n_exp *n);
operande* parcours_appelExp(n_exp *n);
void parcours_l_dec(n_l_dec *n);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
operande* parcours_var(n_var *n);
operande* parcours_var_simple(n_var *n);
operande* parcours_var_indicee(n_var *n);
operande* parcours_appel(n_appel *n);
int nb_param(n_l_dec* liste);
int nb_argument(n_l_exp* liste);

extern int affichetab;
extern int portee;
extern int adresseLocaleCourante;
extern int adresseArgumentCourant;
extern code3a_ code3a;
int adresseGlobaleCourante = 0;

/*-------------------------------------------------------------------------*/

void parcours_n_prog(n_prog *n)
{
	code3a_init();
	portee = P_VARIABLE_GLOBALE;
	parcours_l_dec(n->variables);
	parcours_l_dec(n->fonctions); 
	 
	if(rechercheExecutable("main") == -1) {
	  erreur("Il n'y a pas de main");
	}
    if(tabsymboles.tab[rechercheExecutable("main")].complement !=  0) {
	  erreur("Main est une fonction sans argument");
	}
}

/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n)
{
  if(n){
  parcours_instr(n->tete);
  parcours_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) parcours_l_instr(n->u.liste);
    else if(n->type == affecteInst) parcours_instr_affect(n);
    else if(n->type == siInst) parcours_instr_si(n);
    else if(n->type == tantqueInst) parcours_instr_tantque(n);
    else if(n->type == appelInst) parcours_instr_appel(n);
    else if(n->type == retourInst) parcours_instr_retour(n);
    else if(n->type == ecrireInst) parcours_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n)
{  
  operande *si = code3a_new_etiquette_auto();
  operande *fin = code3a_new_etiquette_auto();
  
  operande *exp = parcours_exp(n->u.si_.test);
  
  code3a_ajoute_instruction(jump_if_equal,exp,code3a_new_constante(0),si,NULL);
 
  parcours_instr(n->u.si_.alors);
  
  if(n->u.si_.sinon){
	code3a_ajoute_instruction(jump, fin, NULL, NULL, NULL);
	code3a_ajoute_etiquette(si->u.oper_nom);
    parcours_instr(n->u.si_.sinon);
  }
  
  code3a_ajoute_etiquette(fin->u.oper_nom);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{
  operande* debut = code3a_new_etiquette_auto();
  operande* fin = code3a_new_etiquette_auto();
  
  code3a_ajoute_etiquette(debut->u.oper_nom);
  
  operande* tantque = parcours_exp(n->u.tantque_.test);

  code3a_ajoute_instruction(jump_if_equal, tantque, code3a_new_constante(0), fin, NULL);

  parcours_instr(n->u.tantque_.faire);

  code3a_ajoute_instruction(jump, debut, NULL, NULL, NULL);

  code3a_ajoute_etiquette(fin->u.oper_nom);
  }

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n)
{
  operande* var = parcours_var(n->u.affecte_.var);
  operande* exp = parcours_exp(n->u.affecte_.exp);
  
  if(var->u.oper_var.oper_indice != NULL && var->u.oper_var.oper_indice->oper_type == O_VARIABLE) {
    operande* tmp1 = code3a_new_temporaire();
    code3a_ajoute_instruction(assign, var->u.oper_var.oper_indice, NULL, tmp1, NULL);
    var->u.oper_var.oper_indice = tmp1;
  }
  if(exp->oper_type == O_VARIABLE && exp->u.oper_var.oper_indice != NULL && exp->u.oper_var.oper_indice->oper_type == O_VARIABLE) {
    operande* tmp2 = code3a_new_temporaire();
    code3a_ajoute_instruction(assign, exp->u.oper_var.oper_indice, NULL, tmp2, NULL);
    exp->u.oper_var.oper_indice = tmp2;
  }
  
  code3a_ajoute_instruction(assign, exp, NULL, var, NULL);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  parcours_appel(n->u.appel);
  code3a_ajoute_instruction(func_call, code3a_new_etiquette(n->u.appel->fonction), NULL, NULL, NULL);
}

/*-------------------------------------------------------------------------*/

int nb_argument(n_l_exp* liste){
	if(liste == NULL)
		return 0;

	if(liste->tete->type == varExp){
		operande* var = parcours_varExp(liste->tete);
		code3a_ajoute_instruction(func_param, var, NULL, NULL, NULL);
	}

	if(liste->tete->type == intExp){
		operande* intexp = parcours_intExp(liste->tete);
		code3a_ajoute_instruction(func_param, intexp, NULL, NULL, NULL);
	}
	if(liste->tete->type == opExp){
		operande* op = parcours_opExp(liste->tete);
		code3a_ajoute_instruction(func_param, op, NULL, NULL, NULL);
	}
	return nb_argument(liste->queue) + 1;
}

operande* parcours_appel(n_appel *n)
{
  code3a_ajoute_instruction(alloc, code3a_new_constante(1), NULL, NULL,"alloue de la place pour la valeur de retour");
  int nbargument = nb_argument(n->args);
  if (rechercheExecutable(n->fonction) == -1){
	erreur("fonction pas declare");
  }
  else if ( nbargument != tabsymboles.tab[rechercheExecutable(n->fonction)].complement){
	erreur("nb argument pas bon");		  
  }
  //parcours_l_exp(n->args);
  operande* etiquette = code3a_new_temporaire();
  return etiquette;
}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  operande* retour = parcours_exp(n->u.retour_.expression);
  code3a_ajoute_instruction(func_val_ret, retour, NULL, NULL, "sauvegarder la valeur de retour");
  code3a_ajoute_instruction(func_end, NULL, NULL, NULL, "terminer l'exécution de la fonction");
}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
  operande* ecrire = parcours_exp(n->u.ecrire_.expression);

  if(ecrire->oper_type == O_VARIABLE && ecrire->u.oper_var.oper_indice != NULL) {
    operande* temporaire = code3a_new_temporaire();
    code3a_ajoute_instruction(assign, ecrire->u.oper_var.oper_indice, NULL, temporaire, NULL);
    ecrire->u.oper_var.oper_indice = temporaire;
  }
  
  code3a_ajoute_instruction(sys_write, ecrire, NULL, NULL, NULL);  
}

/*-------------------------------------------------------------------------*/

void parcours_l_exp(n_l_exp *n)
{
  if(n){
    parcours_exp(n->tete);
    parcours_l_exp(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

operande* parcours_exp(n_exp *n)
{
  if(n->type == varExp) return parcours_varExp(n);
  else if(n->type == opExp) return parcours_opExp(n);
  else if(n->type == intExp) return parcours_intExp(n);
  else if(n->type == appelExp) return parcours_appelExp(n);
  else if(n->type == lireExp) return parcours_lireExp(n);
  return NULL;
}

/*-------------------------------------------------------------------------*/

operande* parcours_varExp(n_exp *n)
{
  return parcours_var(n->u.var);
}

/*-------------------------------------------------------------------------*/

operande* parcours_opExp(n_exp *n)
{	
  operande*  operande1 , *operande2;
  if( n->u.opExp_.op1 != NULL ) {
    operande1= parcours_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL ) {
    operande2 = parcours_exp(n->u.opExp_.op2);
  }
  
  if(operande1->oper_type == O_VARIABLE && operande1->u.oper_var.oper_indice != NULL && operande1->u.oper_var.oper_indice->oper_type == O_VARIABLE) {
    operande* tmp1 = code3a_new_temporaire();
    code3a_ajoute_instruction(assign, operande1->u.oper_var.oper_indice, NULL, tmp1, NULL);
    operande1->u.oper_var.oper_indice = tmp1;
  }
  if(operande2->oper_type == O_VARIABLE && operande2->u.oper_var.oper_indice != NULL && operande2->u.oper_var.oper_indice->oper_type == O_VARIABLE) {
    operande* tmp2 = code3a_new_temporaire();
    code3a_ajoute_instruction(assign, operande2->u.oper_var.oper_indice, NULL, tmp2, NULL);
    operande2->u.oper_var.oper_indice = tmp2;
  }

  
  operande* tempo;
  tempo = code3a_new_temporaire();
  
  if( (n->u.opExp_.op) == plus){
	  code3a_ajoute_instruction(arith_add, operande1, operande2, tempo, NULL);
	  return tempo;
   }
  else if( (n->u.opExp_.op) == moins){
	  code3a_ajoute_instruction(arith_sub, operande1, operande2, tempo, NULL);
	  return tempo;
  }
  else if( (n->u.opExp_.op) == fois){
	  code3a_ajoute_instruction(arith_mult, operande1, operande2, tempo, NULL);
	  return tempo;
  }
  else if( (n->u.opExp_.op) == divise){
	  code3a_ajoute_instruction(arith_div, operande1, operande2, tempo, NULL);
	  return tempo;
  }
  else if( (n->u.opExp_.op) == egal){
	  operande *fin = code3a_new_etiquette_auto();	
	  code3a_ajoute_instruction(assign, code3a_new_constante(-1), NULL, tempo, NULL);
	  code3a_ajoute_instruction(jump_if_equal,operande1,operande2,fin,NULL);
      code3a_ajoute_instruction(assign, code3a_new_constante(0), NULL, tempo, NULL);
      code3a_ajoute_etiquette(fin->u.oper_nom);
	  return tempo;
  }
  else if( (n->u.opExp_.op) == inferieur){  
	  operande *fin = code3a_new_etiquette_auto();	
	  code3a_ajoute_instruction(assign, code3a_new_constante(-1), NULL, tempo, NULL);
	  code3a_ajoute_instruction(jump_if_less,operande1,operande2,fin,NULL);
      code3a_ajoute_instruction(assign, code3a_new_constante(0), NULL, tempo, NULL);
      code3a_ajoute_etiquette(fin->u.oper_nom);
	  return tempo;
  }
  /*else if( (n->u.opExp_.op) == ou){
	  operande *debut = code3a_new_etiquette_auto();
	  operande *fin = code3a_new_etiquette_auto();
	  code3a_ajoute_instruction(assign, code3a_new_constante(-1), NULL, tempo, NULL);
	  code3a_ajoute_instruction(jump_if_less_or_equal,operande1,code3a_new_constante(-1),debut,NULL);
	  code3a_ajoute_instruction(jump_if_less_or_equal,operande2,code3a_new_constante(-1),debut,NULL);
      code3a_ajoute_instruction(assign, code3a_new_constante(0), NULL, tempo, NULL);
	  code3a_ajoute_instruction(jump,fin, NULL, NULL, NULL);
      code3a_ajoute_etiquette(debut->u.oper_nom);
	  code3a_ajoute_etiquette(fin->u.oper_nom);
  }
  else if( (n->u.opExp_.op) == et){
      operateur = jump_if_equal;
  }
  else if( (n->u.opExp_.op) == non){
      operateur = jump_if_equal;
  }*/
  
  return NULL;
}

/*-------------------------------------------------------------------------*/

operande* parcours_intExp(n_exp *n)
{
  return code3a_new_constante(n->u.entier);
}

/*-------------------------------------------------------------------------*/
operande* parcours_lireExp(n_exp *n)
{
  operande* temporaire = code3a_new_temporaire();
  code3a_ajoute_instruction(sys_read, NULL, NULL, temporaire, NULL);
  return temporaire;
}

/*-------------------------------------------------------------------------*/


operande* parcours_appelExp(n_exp *n)
{	
  operande* appel = parcours_appel(n->u.appel);
  char* nom = malloc(102*sizeof(char));
  sprintf (nom,"f%s",n->u.appel->fonction);
  code3a_ajoute_instruction(func_call, code3a_new_etiquette(nom), NULL, appel, NULL);
  return appel;
}

/*-------------------------------------------------------------------------*/

void parcours_l_dec(n_l_dec *n)
{
  if( n ){
    parcours_dec(n->tete);
    parcours_l_dec(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n)
{
  if(n){
    if(n->type == foncDec) {
      parcours_foncDec(n);
    }
    else if(n->type == varDec) {
      parcours_varDec(n);
    }
    else if(n->type == tabDec) { 
      parcours_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/
int nb_param(n_l_dec* liste){
	int n = 0;
	while(liste != NULL){
		n++;
		liste = liste->queue;
	}
	return n;
}

void parcours_foncDec(n_dec *n)
{
	if(rechercheDeclarative(n->nom) ==-1 ){
		int nbparam = nb_param (n->u.foncDec_.param);
		ajouteIdentificateur(n->nom,P_VARIABLE_GLOBALE,T_FONCTION,0, nbparam);
		entreeFonction();
		
		char* nom = malloc(102*sizeof(char));
		sprintf (nom,"f%s",n->nom);
		code3a_ajoute_etiquette(nom);
		
		code3a_ajoute_instruction(func_begin, NULL, NULL, NULL, NULL);
		parcours_l_dec(n->u.foncDec_.param);
		
		portee = P_VARIABLE_LOCALE;
		parcours_l_dec(n->u.foncDec_.variables);
		parcours_instr(n->u.foncDec_.corps);
		
		sortieFonction(affichetab);
		code3a_ajoute_instruction(func_end, NULL, NULL, NULL, NULL);
	}
	else 
		erreur("fonction deja declare");
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{
  if (rechercheDeclarative(n->nom) == -1) { 
    if (portee == P_VARIABLE_GLOBALE)
    {
		code3a_ajoute_instruction(alloc, code3a_new_constante(1), code3a_new_var(n->nom, portee, adresseGlobaleCourante), NULL, n->nom);
        ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseGlobaleCourante, 1);
        adresseGlobaleCourante = adresseGlobaleCourante +4 ;
    }
    else if (portee == P_VARIABLE_LOCALE)
    {
		code3a_ajoute_instruction(alloc, code3a_new_constante(1), code3a_new_var(n->nom, portee, adresseLocaleCourante), NULL, n->nom);
        ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
        adresseLocaleCourante = adresseLocaleCourante +4  ;
    }
    else if (portee == P_ARGUMENT)
    {
		ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 1);
		adresseArgumentCourant = adresseArgumentCourant +4;
    }
  }
  else erreur("Variable deja declaré");
}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n)
{
  int result = rechercheDeclarative(n->nom);
  if (result == -1) {
    if (portee != P_VARIABLE_GLOBALE) 
		erreur("Un tableau est toujours une variable globale");
    ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, adresseGlobaleCourante, n->u.tabDec_.taille);
    adresseGlobaleCourante += n->u.tabDec_.taille*4;
	code3a_ajoute_instruction(alloc, code3a_new_constante(n->u.tabDec_.taille), code3a_new_var(n->nom, portee, adresseGlobaleCourante), NULL, n->nom); 
  }
  else erreur("Tableau deja declaré");
}

/*-------------------------------------------------------------------------*/

operande* parcours_var(n_var *n)
{
  if(n->type == simple) {
    return parcours_var_simple(n);
	
  }
  else if(n->type == indicee) {
	return parcours_var_indicee(n);	
  }
  return NULL;
}

/*-------------------------------------------------------------------------*/

operande* parcours_var_simple(n_var *n)
{
  if (rechercheExecutable(n->nom) == -1) 
	  erreur("Variable non declaré");
  else if (tabsymboles.tab[rechercheExecutable(n->nom)].type == T_TABLEAU_ENTIER) 
	  erreur("Tableau non indicee");
  return code3a_new_var(n->nom, tabsymboles.tab[rechercheExecutable(n->nom)].portee, tabsymboles.tab[rechercheExecutable(n->nom)].adresse);
}

/*-------------------------------------------------------------------------*/

operande* parcours_var_indicee(n_var *n)
{
	
  if (rechercheExecutable(n->nom) == -1) 
	  erreur("Variable non declaré");
  else if (tabsymboles.tab[rechercheExecutable(n->nom)].type == T_ENTIER) {
	  erreur("la variable n'est pas un tableau");
  }
  return code3a_new_var_indicee(n->nom, tabsymboles.tab[rechercheExecutable(n->nom)].portee, tabsymboles.tab[rechercheExecutable(n->nom)].adresse, parcours_exp( n->u.indicee_.indice ));
}


