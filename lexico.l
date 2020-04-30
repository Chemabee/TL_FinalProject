%{
#include "calculadora.h"
#include <math.h>
int n_lineas;
%}

%option noyywrap

%x COM1 COM2 STR
 
digito [0-9]
entero {digito}+
real ({entero}*[.]{entero})|({entero}[.]{entero}*)
real_not_cientifica {real}[e][+-]?{entero}
blank [\t ]
salto_linea \n
linea_vacia ^{blank}*{salto_linea}


%%
["]						            BEGIN(STR);
<STR>[^"]*					        strcpy(yylval.c_cadena,yytext);return CADENA;
<STR>["]					        BEGIN(0);

^{blank}*"#"                        BEGIN(COM1);
<COM1>"\n"            {BEGIN(0);n_lineas++;}
"#"                                 BEGIN(COM2);
<COM2>"\n"                    {BEGIN(0);n_lineas++;return(yytext[0]);}
<COM2,COM1>.    ;

escribir        strcpy(yylval.c_cadena, yytext);return ESCRIBIR;

entero          {return INT;}
real            {return FLOAT;}
cadena          {return STRING;}
posicion        {return POS;}

DEFINICIONES            {return DEFINICIONES;}
CONFIGURACION           {return CONFIGURACION;}
OBSTACULOS              {return OBSTACULOS;}
EJEMPLOS                {return EJEMPLOS;}

[Dd][Ii][Mm][Ee][Nn][Ss][Ii][Oo][Nn]    {return DIMENSION;}
[Ee][Nn][Tt][Rr][Aa][Dd][Aa]            {return ENTRADA;}
[Ss][Aa][Ll][Ii][Dd][Aa]                {return SALIDA;}
[Pp][Aa][Uu][Ss][Aa]                    {return PAUSA;}

obstaculo       {return OBSTACULO;}
norte           {return NORTE;}
sur             {return SUR;}
este            {return ESTE;}
oeste           {return OESTE;}

ejemplo         {return EJEMPLO;}
finejemplo      {return FINEJEMPLO;}

{entero}                    yylval.c_entero = atoi(yytext);return ENTERO;
{real}|{real_not_cientifica}		yylval.c_real = atof(yytext);return REAL;
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
{linea_vacia}   n_lineas++;
{salto_linea}   n_lineas++; return (yytext[0]);
{blank}  ;
. 				return (yytext[0]);
%%

