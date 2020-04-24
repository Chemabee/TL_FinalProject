%{
#include "calculadora.h"
#include <math.h>
int n_lineas;
%}

%option noyywrap

%x COM1 STR
 
digito [0-9]
entero {digito}+
real ({entero}*[.]{entero})|({entero}[.]{entero}*)
real_not_cientifica {real}[e][+-]?{entero}

%%
"#"                          BEGIN(COM1);
<COM1>\n                  {BEGIN(0);n_lineas++; return (yytext[0]);}
<COM1>. ;
["]						BEGIN(STR);
<STR>[^"]*					strcpy(yylval.c_cadena,yytext);return CADENA;
<STR>["]					BEGIN(0);

DEFINICIONES            {return DEFINICIONES;}
CONFIGURACION           {return CONFIGURACION;}
OBSTACULOS              {return OBSTACULOS;}
EJEMPLOS                {return EJEMPLOS;}

{entero}                    yylval.c_entero = atoi(yytext);return ENTERO;
{real}|{real_not_cientifica}		yylval.c_real = atof(yytext);return REAL;
\n				n_lineas++; return (yytext[0]);
[\t ]			;
escribir        strcpy(yylval.c_cadena, yytext);return ESCRIBIR;
true            yylval.c_bool = 1; return BOOL;
false           yylval.c_bool = 0; return BOOL;
[A-Za-z_][_A-Za-z0-9]*    strcpy(yylval.c_cadena, yytext);return VARIABLE;
[<][=]          return LE;
[>][=]          return GE;
[=][=]          return EQ;
[!][=]          return NE;
[|][|]          return OR;
[&][&]          return AND;
[!]             return NOT;
. 				return (yytext[0]);
%%

