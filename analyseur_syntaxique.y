%{
#include<stdlib.h>
#include<stdio.h>
#define YYDEBUG 1
//#include"syntabs.h" // pour syntaxe abstraite
//extern n_prog *n;   // pour syntaxe abstraite
extern FILE *yyin;    // declare dans compilo
extern int yylineno;  // declare dans analyseur lexical
int yylex();          // declare dans analyseur lexical
int yyerror(char *s); // declare ci-dessous
int yydebug=1;
%}

%token POINT_VIRGULE 
%token PLUS 
%token MOINS 
%token FOIS 
%token DIVISE 
%token PARENTHESE_OUVRANTE 
%token PARENTHESE_FERMANTE 
%token CROCHET_OUVRANT 
%token CROCHET_FERMANT 
%token ACCOLADE_OUVRANTE 
%token ACCOLADE_FERMANTE 
%token EGAL 
%token INFERIEUR 
%token ET 
%token OU 
%token NON 
%token SI 
%token ALORS 
%token SINON 
%token TANTQUE 
%token FAIRE 
%token ENTIER 
%token RETOUR 
%token LIRE 
%token ECRIRE 
%token IDENTIF 
%token NOMBRE 
%token VIRGULE 


%start programme
%%

programme : ;
//TODO: compléter avec les productions de la grammaire
expression: expression OU e2 | e2;
e2: e2 ET e3 | e3;
e3: e3 EGAL e4 | e3 INFERIEUR e4 | e4;
e4: e4 PLUS e5 | e4 MOINS e5 | e5;
e5: e5 FOIS e6 | e5 DIVISE e6 | e6;
e6: NON e6 | e7;
e7: PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE | NOMBRE | appelfct | var | LIRE ;
var: IDENTIF | IDENTIF CROCHET_OUVRANT expression CROCHET_FERMANT;
appelfct: IDENTIF PARENTHESE_OUVRANTE liste_expression PARENTHESE_FERMANTE;
liste_expression: expression liste_expressionbis | ;
liste_expressionbis: VIRGULE expression liste_expressionbis | ;
instr: instrAffect | instrBloc | instrSi | instrTantque | instrAppel | instrRetour | instrEcriture | instrVide;
instrAffect: var EGAL expression POINT_VIRGULE;
instrBloc: ACCOLADE_OUVRANTE liste_instr ACCOLADE_FERMANTE;
liste_instr: instr liste_instr | ;
instrSi: SI expression ALORS listeinstrsi ;
listeinstrsi: instrBloc | instrBloc SINON instrBloc | instrBloc SINON instrSi;
instrTantque: TANTQUE expression FAIRE instrBloc;
instrAppel: appelfct POINT_VIRGULE;
instrRetour: RETOUR expression POINT_VIRGULE;
instrEcriture: ECRIRE PARENTHESE_OUVRANTE expression PARENTHESE_FERMANTE POINT_VIRGULE;
instrVide:;
%%

int yyerror(char *s) {
  fprintf(stderr, "erreur de syntaxe ligne %d\n", yylineno);
  fprintf(stderr, "%s\n", s);
  fclose(yyin);
  exit(1);
}
