/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "calculadora.y" /* yacc.c:339  */

#include <iostream>
#include <fstream>
#include <math.h>
#include "tabla.c"
#include "string.h"
#include <stdio.h>
#include <map> 
 

using namespace std;

bool real_final=false;
bool real=false;
bool error_mod=false;
bool error_log=false;
bool error_nodef = false;
bool error_bool_derecha = false;
bool cmp=false;
bool str = false;
bool error_str = false;
bool posVar = false;

bool errorFichero = false;

bool ejecutar = true;

bool bucle = false;

bool fileInicializado = false;
bool finEjemplo = false;

int dimension_glob = 10;
int posEntrada_glob[2] = {0, 0};
int posSalida_glob[2] = {9, 9};
float pausa_glob = 0.5;

int posActual[2] = {0, 0};

//Matriz de obstaculos
int i = 0;
int j = 0;
int matriz_obstaculos[10][10];

Tabla* tabla;
tipo_datoTS* var;

//Archivo final cpp
std::ofstream finalFile;

//elementos externos al analizador sintácticos por haber sido declarados en el analizador léxico      			
extern int n_lineas;
extern int yylex();
extern FILE* yyin, yyout;

struct dato_vector_bucle {
      //NORTE: 0; SUR: 1; ESTE: 2; OESTE: 3; OBSTACULO: 4; ESCRIBIR: 5
      int tipo_instruccion;

      /**
      * 0 = entero
      * 1 = real
      * 2 = logico (bool)
      * 3 = cadena de caracteres
      * 4 = posicion
      **/
      int tipo;
      tipo_valor dato;
};

struct vector_instruciones_bucle{
      map<int, dato_vector_bucle> instrucciones;
      int repeticiones;
} vect;


//definición de procedimientos auxiliares
void reset_flags(){
      real_final=false;
      real=false;
      error_mod=false;
      error_log=false;
      error_nodef = false;
      error_bool_derecha = false;
      cmp=false;
      str = false;
      error_str = false;
      posVar = false;
}

string check_tipo(){
      if(posVar) return "posicion";
      else if(cmp) return "logico";
      else if(real_final) return "real";
      else return "entero";
}
int check_tipo_num(){
      if(posVar) return 4;
      else if(str) return 3;
      else if(cmp) return 2;
      else if(real_final) return 1;
      else return 0;
}

void printVictoria(){
      if(posSalida_glob[0]==posActual[0] && posSalida_glob[1] == posActual[1]) finalFile<<"entornoMostrarMensaje (\"  ¡ Lo conseguiste !    \");"<<endl;
      else finalFile<<"entornoMostrarMensaje (\"  ¡ Mala suerte !    \");"<<endl;
}

void yyerror(const char* s){         /*    llamada por cada error sintactico de yacc */
	cout << "Error sintáctico en la línea \033[1;31m"<<n_lineas<<"\033[0m"<<endl;	
      reset_flags();
      errorFichero = true;
} 

bool insertar(tipo_datoTS *var, bool init, bool cte){
      if(init == true) var->init = true;
      else var->init = false;

      if(cte == true) var->cte = true;
      else var-> cte = false;

      return tabla->insertar(var);
}

void initFile(){
      finalFile<<"#include <iostream>"<<endl;
      finalFile<<"#include <allegro5/allegro.h>"<<endl;
      finalFile<<"#include <stdio.h>"<<endl;
      finalFile<<"#include \"entorno.h\""<<endl;
      finalFile<<"using namespace std;"<<endl;
      finalFile<<"int main(int argc, char** argv){"<<endl;
      finalFile<<"entornoIniciar ("<<dimension_glob<<");"<<endl;
      finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
	finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;
      fileInicializado = true;
}

bool moverse(int pasos, int direccion){
      bool exit = false;
      for(int i = 0;i < pasos && !exit;i++){
            switch(direccion){
                  case 0://Norte
                        if(posActual[1] - 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al NORTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]][posActual[1]-1] == 1) {cout<<"N - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finEjemplo=true;finalFile<<"entornoPonerChoque("<<posActual[1]-1<<","<<posActual[0]<<");"<<endl;}
                        else {posActual[1] = posActual[1]-1;cout << "N\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;}
                  break;
                  case 1://Sur
                        if(posActual[1] + 1 >= dimension_glob) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al SUR!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]][posActual[1]+1] == 1) {cout<<"S - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finEjemplo=true;finalFile<<"entornoPonerChoque("<<posActual[1]+1<<","<<posActual[0]<<");"<<endl;}
                        else {posActual[1] = posActual[1]+1; cout << "S\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
                  case 2://Este
                        if(posActual[0] + 1 >= dimension_glob) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al ESTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]+1][posActual[1]] == 1) {cout<<"E - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finEjemplo=true;finalFile<<"entornoPonerChoque("<<posActual[1]<<","<<posActual[0]+1<<");"<<endl;}
                        else {posActual[0] = posActual[0]+1; cout << "E\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
                  case 3://Oeste
                        if(posActual[0] - 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al OESTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]-1][posActual[1]] == 1) {cout<<"O - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finEjemplo=true;finalFile<<"entornoPonerChoque("<<posActual[1]<<","<<posActual[0]-1<<");"<<endl;}
                        else {posActual[0] = posActual[0]-1; cout << "O\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
            }
            if(posActual[0] == posSalida_glob[0] && posActual[1] == posSalida_glob[1]) {cout << "\033[1;33mHas encontrado la salida en \033[0m"<< "\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m!!"<<endl;exit=true;finalFile<<"entornoPonerFiguraSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;printVictoria();finEjemplo=true;}
      }
}

void doLoop_obstaculos(){
      for(int i = 1; i<vect.repeticiones;i++){
            for(int j = 0;j<vect.instrucciones.size() && !finEjemplo;j++){
                  dato_vector_bucle temp = vect.instrucciones.find(j)->second;
                  cout<<"tipo: "<<temp.tipo_instruccion<<"; parametro: "<<temp.tipo<<endl;

                  switch(temp.tipo_instruccion){
                        case 0://Norte
                              if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&temp.dato.valor_entero>=0){
                                    if(posActual[1]-temp.dato.valor_entero >= 0){
                                          posActual[1]=posActual[1]-temp.dato.valor_entero;
                                    }else{
                                          posActual[1]=0;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al NORTE!"<<endl;
                                    }
                              }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al NORTE erróneo"<<endl;};
                              reset_flags();
                        break;
                        case 1://Sur
                              if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&temp.dato.valor_entero>=0){
                                    if(posActual[1]+temp.dato.valor_entero < dimension_glob){
                                          posActual[1]=posActual[1]+temp.dato.valor_entero;
                                    }else{
                                          posActual[1]=dimension_glob-1;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al SUR!"<<endl;
                                    }
                              }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al SUR erróneo"<<endl;};
                              reset_flags();
                        break;
                        case 2://Este
                              if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&temp.dato.valor_entero>=0){
                                    if(posActual[0]+temp.dato.valor_entero < dimension_glob){
                                          posActual[0]=posActual[0]+temp.dato.valor_entero;
                                    }else{
                                          posActual[0]=dimension_glob-1;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al ESTE!"<<endl;
                                    }
                              }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al ESTE erróneo"<<endl;};
                              reset_flags();
                        break;
                        case 3://Oeste
                              if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&temp.dato.valor_entero>=0){
                                    if(posActual[0]-temp.dato.valor_entero >= 0){
                                          posActual[0]=posActual[0]-temp.dato.valor_entero;
                                    }else{
                                          posActual[0]=0;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al OESTE!"<<endl;
                                    }
                              }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al OESTE erróneo"<<endl;};
                              reset_flags();
                        break;
                        case 4://Obstaculo
                              matriz_obstaculos[posActual[0]][posActual[1]] = 1;
                              finalFile<<"entornoPonerObstaculo("<<posActual[1]<<","<<posActual[0]<<");"<<endl;
                              cout<<"OBSTACULO colocado en <"<<posActual[0]<<","<<posActual[1]<<">"<<endl; /*TODO*/;
                              reset_flags();
                        break;
                        case 5://Escribir
                              if(fileInicializado){
                                    switch(temp.tipo){
                                          case 0:
                                                finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_entero<<"\");"<<endl;
                                          break;
                                          case 1: 
                                                finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_real<<"\");"<<endl;
                                          break;
                                          case 2:
                                                finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_logico<<"\");"<<endl;
                                          break;
                                          case 3:
                                                finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_cad<<"\");"<<endl;
                                          break;
                                          case 4:
                                                finalFile<<"entornoMostrarMensaje(\"<"<<temp.dato.valor_pos[0]<<","<<temp.dato.valor_pos[1]<<">\");"<<endl;
                                          break;
                                    }
                              }
                              reset_flags();
                        break;
                  }
            }
      }
}

void doLoop_ejemplos(){
      for(int i = 1; i<vect.repeticiones;i++){
            for(int j = 0;j<vect.instrucciones.size();j++){
                  dato_vector_bucle temp = vect.instrucciones.find(j)->second;
                  if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&temp.dato.valor_entero>=0){
                        if(!finEjemplo){
                              switch(temp.tipo_instruccion){
                                    case 0: //Norte
                                          moverse(temp.dato.valor_entero, 0);
                                    break;
                                    case 1: //Sur
                                          moverse(temp.dato.valor_entero, 1);
                                    break;
                                    case 2: //Este
                                          moverse(temp.dato.valor_entero, 2);
                                    break;
                                    case 3: //Oeste
                                          moverse(temp.dato.valor_entero, 3);
                                    break;
                                    case 5: //Escribir
                                          if(fileInicializado){
                                                switch(temp.tipo){
                                                      case 0:
                                                            finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_entero<<"\");"<<endl;
                                                      break;
                                                      case 1: 
                                                            finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_real<<"\");"<<endl;
                                                      break;
                                                      case 2:
                                                            finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_logico<<"\");"<<endl;
                                                      break;
                                                      case 3:
                                                            finalFile<<"entornoMostrarMensaje(\""<<temp.dato.valor_cad<<"\");"<<endl;
                                                      break;
                                                      case 4:
                                                            finalFile<<"entornoMostrarMensaje(\"<"<<temp.dato.valor_pos[0]<<","<<temp.dato.valor_pos[1]<<">\");"<<endl;
                                                      break;
                                                }
                                          }
                                    break;
                              }
                        }
                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte erróneo"<<endl;};
                  reset_flags();
            }
      }
}

void printTabla(ofstream &out){
      out << "****************************************" <<endl;
      out << "***NOMBRE      TIPO      VALOR    CTE***" <<endl;
      out << "****************************************" <<endl;

      nodo* n = tabla->getFirst();
      while(n!=NULL){
            out <<"**"<< n->dato.nombre<<"            ";
            if(n->dato.init == true){
                  switch (n->dato.tipo){
                        case 0: out << "Int          "<<n->dato.valor.valor_entero;break;
                        case 1: out << "Float        "<<n->dato.valor.valor_real;break;
                        case 2: out << "Bool         ";
                              if(n->dato.valor.valor_real)
                                    out<<"True";
                              else
                                    out<<"False";
                              break;
                        default: out << "undefined";break;
                        case 3: out << "String       "<<n->dato.valor.valor_cad;break;
                        case 4: out << "Position     <"<<n->dato.valor.valor_pos[0]<<","<<n->dato.valor.valor_pos[1]<<">";break;
                  }
            }
            else{
                 switch (n->dato.tipo){
                        case 0: out << "Int          NI";break;
                        case 1: out << "Float        NI";break;
                        case 2: out << "Bool         NI";break;
                        default: out << "undefined";break;
                        case 3: out << "String       NI";break;
                        case 4: out << "Position     NI";break;

                  } 
            }
            if(n->dato.cte == true) out<<"     SI"<<endl;
            else out<<"      NO"<<endl;
            
            n=n->sig;
      }
      out << "*********************************" <<endl;
      out << "*******Variables Globales********" <<endl;
      out << "** DIMENSION: "<<dimension_glob<<endl;
      out << "** POS_ENTRADA: <"<<posEntrada_glob[0]<<","<<posEntrada_glob[1]<<">"<<endl;
      out << "** POS_SALIDA: <"<<posSalida_glob[0]<<","<<posSalida_glob[1]<<">"<<endl;
      out << "** PAUSA: "<<pausa_glob<<endl;
      out << "** POS_ACTUAL: <"<<posActual[0]<<","<<posActual[1]<<">"<<endl;
      out << "*********************************" <<endl;
      out << "*******NI = No Inicializado******" <<endl;
      out << "*********************************" <<endl;
      out << "***************MAPA**************" <<endl;
      for(int i = 0; i < dimension_glob; i++){
            for(int j = 0; j < dimension_glob; j++){
                  out << matriz_obstaculos[j][i]<<" ";
            }
            out<<endl;
      }
}


#line 425 "calculadora.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "calculadora.h".  */
#ifndef YY_YY_CALCULADORA_H_INCLUDED
# define YY_YY_CALCULADORA_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    ENTERO = 259,
    OBSTACULO = 260,
    VARIABLE = 261,
    ESCRIBIR = 262,
    CADENA = 263,
    DEFINICIONES = 264,
    CONFIGURACION = 265,
    OBSTACULOS = 266,
    EJEMPLOS = 267,
    DIMENSION = 268,
    ENTRADA = 269,
    SALIDA = 270,
    PAUSA = 271,
    NORTE = 272,
    SUR = 273,
    ESTE = 274,
    OESTE = 275,
    EJEMPLO = 276,
    FINEJEMPLO = 277,
    REPITE = 278,
    FINREPITE = 279,
    IF = 280,
    THEN = 281,
    ELSE = 282,
    ENDIF = 283,
    REAL = 284,
    INT = 285,
    FLOAT = 286,
    STRING = 287,
    POS = 288,
    OR = 289,
    AND = 290,
    NOT = 291,
    LE = 292,
    GE = 293,
    EQ = 294,
    NE = 295,
    menos = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 359 "calculadora.y" /* yacc.c:355  */

      //Tipo union por si en el futuro lo podemos usar
      typedef char tipo_cadena[50];
      typedef int tipo_pos[2];
      union tipo_valor{
            int valor_entero;//0
            float valor_real;//1
            bool valor_logico;//2
            tipo_cadena valor_cad;//3
            tipo_pos valor_pos;//4
      };

      int c_entero;
      float c_real;
      char c_cadena[20];
      bool c_bool;

#line 525 "calculadora.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALCULADORA_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 542 "calculadora.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   761

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    47,     2,     2,
      49,    50,    45,    43,    54,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    53,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   401,   401,   402,   403,   404,   405,   406,   407,   410,
     457,   485,   519,   553,   555,   557,   571,   606,   648,   656,
     663,   670,   677,   685,   688,   689,   690,   704,   705,   706,
     707,   708,   720,   721,   731,   733,   734,   735,   736,   737,
     738,   739,   740,   741,   755,   768,   771,   810,   833,   860,
     887,   888,   891,   892,   893,   895,   896,   905,   918,   931,
     944,   957,   960,   962,   963,   976,   990,  1007,  1023,  1039,
    1055,  1066,  1066,  1071,  1072,  1075,  1078,  1080,  1083,  1098,
    1113,  1128,  1143,  1144,  1144,  1149,  1152,  1152,  1154,  1155,
    1155,  1158,  1158,  1160,  1161,  1161
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "ENTERO", "OBSTACULO",
  "VARIABLE", "ESCRIBIR", "CADENA", "DEFINICIONES", "CONFIGURACION",
  "OBSTACULOS", "EJEMPLOS", "DIMENSION", "ENTRADA", "SALIDA", "PAUSA",
  "NORTE", "SUR", "ESTE", "OESTE", "EJEMPLO", "FINEJEMPLO", "REPITE",
  "FINREPITE", "IF", "THEN", "ELSE", "ENDIF", "REAL", "INT", "FLOAT",
  "STRING", "POS", "OR", "AND", "NOT", "LE", "GE", "EQ", "NE", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'('", "')'", "menos",
  "'\\n'", "'='", "','", "$accept", "lista_instrucciones", "asignacion",
  "escribir", "declaracion", "expr", "expr_logica", "asignacion_sin_ctes",
  "bloque_definiciones", "bloque_configuracion", "bloque_obstaculos",
  "$@1", "bloque_ejemplos", "bloque_ejemplos_anidado", "$@2",
  "condicional_obstaculos", "$@3", "cierre_condicional_obstaculos", "$@4",
  "condicional_ejemplos", "$@5", "cierre_condicional_ejemplos", "$@6", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    60,    62,    43,    45,    42,    47,    37,    94,    40,
      41,   296,    10,    61,    44
};
# endif

#define YYPACT_NINF -177

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-177)))

#define YYTABLE_NINF -24

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     235,   -43,   -34,   151,   -29,   -25,   -19,    28,    52,    56,
      65,    45,   235,  -177,   -48,   -38,    88,  -177,  -177,  -177,
      29,  -177,   173,   190,   173,   433,   -23,  -177,    73,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,   235,    81,    38,   190,
     449,     9,  -177,   507,  -177,   190,  -177,   493,    39,   190,
     190,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     190,  -177,   173,   173,  -177,   242,   190,   214,   355,  -177,
    -177,  -177,   215,  -177,  -177,   265,  -177,  -177,   713,   713,
     713,   713,   713,   713,   125,   125,    53,    53,    53,    53,
      68,  -177,    64,    67,  -177,    30,   117,    69,    75,    74,
     140,   182,   190,  -177,  -177,    31,    79,   190,   190,   190,
     190,   190,   173,  -177,  -177,   190,    73,  -177,  -177,    24,
    -177,   107,  -177,   190,   538,   190,   548,   558,   190,  -177,
     568,  -177,   578,   588,   598,   608,   618,    33,   679,   513,
     364,  -177,    86,   190,   465,    43,   385,   243,  -177,   411,
    -177,  -177,   514,  -177,   112,  -177,  -177,  -177,  -177,  -177,
     113,    90,    93,    95,  -177,   526,  -177,  -177,    97,   190,
     190,   190,   144,  -177,   101,  -177,  -177,  -177,   190,  -177,
     686,   693,   700,   106,   394,  -177,   415,   112,   707,   112,
     122,   130,   131,  -177,   138,  -177,   139,   141,  -177,  -177,
    -177,   424,  -177,   275,  -177,  -177,   190,   190,   190,   190,
     145,   190,   173,  -177,  -177,   146,   147,  -177,   112,   628,
     638,   648,   658,  -177,   668,   100,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,   175,  -177,  -177,   155,   300,   444,  -177,
     158,   160,  -177,  -177,  -177,   315,   161,   164,  -177,  -177,
    -177,  -177,   330,   166,  -177
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,     0,    14,     0,    35,    25,    26,
       0,    24,     0,     0,     0,     0,     0,    52,    55,    63,
      18,    19,    20,    21,     1,     7,     0,     0,     0,     0,
       0,     0,    15,     0,    45,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    16,     0,     0,    17,     0,     0,     0,     0,     8,
      22,    10,     0,     9,    12,     0,    27,    36,    39,    40,
      41,    42,    37,    38,    28,    29,    30,    31,    33,    32,
      44,    43,     0,     0,    54,     0,    55,     0,     0,     0,
       0,     0,     0,    50,    62,     0,     0,     0,     0,     0,
       0,     0,     0,    74,    73,     0,    55,    63,    53,     0,
      51,     0,    63,     0,     0,     0,     0,     0,     0,    70,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,     0,    57,     0,
      59,    61,     0,    65,     6,    69,    66,    67,    68,    71,
       0,     0,     0,     0,    47,     0,    46,    49,     0,     0,
       0,     0,     0,    63,     0,    11,    63,    75,     0,    75,
       0,     0,     0,     0,     0,    86,     0,     5,     0,     4,
       0,     0,     0,    77,     0,    63,     0,     0,    58,    60,
      64,     0,    72,     0,    75,    48,     0,     0,     0,     0,
       0,     0,     0,    82,    85,     0,     0,    87,     3,     0,
       0,     0,     0,    76,     0,     0,    89,    88,    81,    78,
      79,    80,    83,     0,    63,    77,     0,     0,     0,    91,
       0,     0,    77,    90,    84,     0,     0,     0,    92,    94,
      93,    77,     0,     0,    95
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,    -4,   159,     5,   162,    -3,     2,   -60,  -177,   -94,
    -107,  -177,  -176,  -142,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,   103,    14,    43,    26,   113,    65,    67,
      68,   173,   154,   201,   235,   114,   195,   217,   234,   214,
     242,   248,   251
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   187,   119,   189,    36,    13,    37,   104,    35,    15,
     140,    62,    63,    40,   -23,   146,   -23,    13,    41,    16,
      46,    47,   139,    27,    44,    97,    48,    28,   218,    64,
      98,     3,    69,    29,    30,    18,    72,    19,   100,   101,
     102,    13,    75,    62,    63,    34,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    31,   104,
      21,    74,    32,    96,    90,    91,   184,    62,    63,   186,
      13,    33,   128,    62,    63,    23,   141,    62,    63,   104,
      45,    42,   118,   129,    37,   160,    66,    70,   203,    77,
      71,    17,    18,   238,    19,   167,    38,   124,   126,   127,
     245,    60,   130,    63,   132,   133,   134,   135,   136,   252,
      17,    18,   138,    19,   137,   142,   116,    21,   144,   117,
     147,   120,   149,   145,    22,   152,   122,   237,   121,    39,
      66,   131,    23,   172,    62,    63,    21,    24,   164,   174,
     165,   213,   175,    22,    18,   176,    19,   177,   143,   179,
     183,    23,   233,   185,    17,    18,    24,    19,   193,    20,
      55,    56,    57,    58,    59,    60,   180,   181,   182,    21,
      57,    58,    59,    60,   198,   188,    17,    18,   213,    19,
      21,   123,   199,   200,    23,   213,    18,    22,    19,    45,
     202,   204,   213,   205,    18,    23,    19,   223,   226,   227,
      24,   236,    21,   219,   220,   221,   222,   239,   224,    22,
     243,    21,   244,   249,   225,    97,   250,    23,   254,    21,
      98,     3,    24,   125,    94,    99,    23,    95,   100,   101,
     102,    45,     0,     0,    23,    -2,     1,     0,     0,    45,
       0,     2,     3,     1,     4,     5,     6,     0,     2,     3,
       0,     0,    92,    93,     0,     0,     0,     0,    55,    56,
      57,    58,    59,    60,     0,     7,     8,     9,    10,   115,
       0,     0,     7,     8,     9,    10,    97,     0,     0,     0,
     105,    98,     3,     0,     0,     0,    55,    56,    57,    58,
      59,    60,   107,   108,   109,   110,     0,   169,   111,     0,
     112,    97,   215,   216,     0,   105,    98,     3,    55,    56,
      57,    58,    59,    60,     0,    76,    97,   107,   108,   109,
     110,    98,     3,   111,     0,   112,     0,     0,   240,     0,
       0,    97,   206,   207,   208,   209,    98,     3,   211,     0,
     212,     0,   246,   247,     0,     0,     0,   206,   207,   208,
     209,     0,     0,   211,     0,   212,    97,     0,   253,     0,
     105,    98,     3,     0,     0,    97,     0,   106,     0,   105,
      98,     3,   107,   108,   109,   110,   163,     0,   111,     0,
     112,   107,   108,   109,   110,     0,    97,   111,     0,   112,
     105,    98,     3,     0,     0,    97,     0,   168,     0,   105,
      98,     3,   107,   108,   109,   110,     0,     0,   111,     0,
     112,   107,   108,   109,   110,     0,    97,   111,   194,   112,
     105,    98,     3,     0,     0,    97,     0,   196,     0,     0,
      98,     3,   107,   108,   109,   110,     0,     0,   111,     0,
     112,   206,   207,   208,   209,    97,   210,   211,     0,   212,
      98,     3,     0,     0,    55,    56,    57,    58,    59,    60,
       0,   206,   207,   208,   209,   170,     0,   211,   241,   212,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,    61,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     0,     0,
       0,    73,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    97,     0,     0,   166,     0,    98,
       3,     0,     0,     0,   162,     0,     0,   100,   101,   102,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,    76,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     0,    55,    56,    57,
      58,    59,    60,     0,     0,     0,     0,     0,   171,    55,
      56,    57,    58,    59,    60,     0,     0,     0,     0,     0,
     178,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     148,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     150,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     151,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     153,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     155,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     156,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     157,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     158,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     159,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     228,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     229,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     230,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     231,    55,    56,    57,    58,    59,    60,     0,     0,     0,
     232,   161,    55,    56,    57,    58,    59,    60,   190,    55,
      56,    57,    58,    59,    60,   191,    55,    56,    57,    58,
      59,    60,   192,    55,    56,    57,    58,    59,    60,   197,
      55,    56,    57,    58,    59,    60,    55,    56,    57,    58,
      59,    60
};

static const yytype_int16 yycheck[] =
{
       3,   177,    96,   179,    52,     0,    54,    67,    12,    52,
     117,    34,    35,    16,    52,   122,    54,    12,    16,    53,
      23,    24,   116,    52,    22,     1,    24,    52,   204,    52,
       6,     7,    36,    52,     6,     4,    39,     6,    14,    15,
      16,    36,    45,    34,    35,     0,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     6,   119,
      29,    52,     6,    66,    62,    63,   173,    34,    35,   176,
      65,     6,    41,    34,    35,    44,    52,    34,    35,   139,
      49,    52,    52,    52,    54,    52,    13,     6,   195,    50,
      52,     3,     4,   235,     6,    52,     8,   100,   101,   102,
     242,    48,   105,    35,   107,   108,   109,   110,   111,   251,
       3,     4,   115,     6,   112,     8,    52,    29,   121,    52,
     123,    52,   125,   121,    36,   128,    52,   234,    53,    41,
      13,    52,    44,    21,    34,    35,    29,    49,    52,    26,
     143,   201,    52,    36,     4,    52,     6,    52,    41,    52,
       6,    44,    52,    52,     3,     4,    49,     6,    52,     8,
      43,    44,    45,    46,    47,    48,   169,   170,   171,    29,
      45,    46,    47,    48,    52,   178,     3,     4,   238,     6,
      29,    41,    52,    52,    44,   245,     4,    36,     6,    49,
      52,    52,   252,    52,     4,    44,     6,    52,    52,    52,
      49,    26,    29,   206,   207,   208,   209,    52,   211,    36,
      52,    29,    52,    52,   212,     1,    52,    44,    52,    29,
       6,     7,    49,    41,    65,    11,    44,    65,    14,    15,
      16,    49,    -1,    -1,    44,     0,     1,    -1,    -1,    49,
      -1,     6,     7,     1,     9,    10,    11,    -1,     6,     7,
      -1,    -1,    10,    11,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    -1,    30,    31,    32,    33,    54,
      -1,    -1,    30,    31,    32,    33,     1,    -1,    -1,    -1,
       5,     6,     7,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    17,    18,    19,    20,    -1,    54,    23,    -1,
      25,     1,    27,    28,    -1,     5,     6,     7,    43,    44,
      45,    46,    47,    48,    -1,    50,     1,    17,    18,    19,
      20,     6,     7,    23,    -1,    25,    -1,    -1,    28,    -1,
      -1,     1,    17,    18,    19,    20,     6,     7,    23,    -1,
      25,    -1,    27,    28,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    23,    -1,    25,     1,    -1,    28,    -1,
       5,     6,     7,    -1,    -1,     1,    -1,    12,    -1,     5,
       6,     7,    17,    18,    19,    20,    12,    -1,    23,    -1,
      25,    17,    18,    19,    20,    -1,     1,    23,    -1,    25,
       5,     6,     7,    -1,    -1,     1,    -1,    12,    -1,     5,
       6,     7,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      25,    17,    18,    19,    20,    -1,     1,    23,    24,    25,
       5,     6,     7,    -1,    -1,     1,    -1,    12,    -1,    -1,
       6,     7,    17,    18,    19,    20,    -1,    -1,    23,    -1,
      25,    17,    18,    19,    20,     1,    22,    23,    -1,    25,
       6,     7,    -1,    -1,    43,    44,    45,    46,    47,    48,
      -1,    17,    18,    19,    20,    54,    -1,    23,    24,    25,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    52,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    -1,    -1,
      -1,    52,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     1,    -1,    -1,    52,    -1,     6,
       7,    -1,    -1,    -1,    11,    -1,    -1,    14,    15,    16,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    50,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    -1,    43,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      52,    42,    43,    44,    45,    46,    47,    48,    42,    43,
      44,    45,    46,    47,    48,    42,    43,    44,    45,    46,
      47,    48,    42,    43,    44,    45,    46,    47,    48,    42,
      43,    44,    45,    46,    47,    48,    43,    44,    45,    46,
      47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     9,    10,    11,    30,    31,    32,
      33,    56,    57,    58,    59,    52,    53,     3,     4,     6,
       8,    29,    36,    44,    49,    60,    61,    52,    52,    52,
       6,     6,     6,     6,     0,    56,    52,    54,     8,    41,
      60,    61,    52,    60,    61,    49,    60,    60,    61,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    52,    34,    35,    52,    63,    13,    64,    65,    56,
       6,    52,    60,    52,    52,    60,    50,    50,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    10,    11,    57,    59,    60,     1,     6,    11,
      14,    15,    16,    58,    62,     5,    12,    17,    18,    19,
      20,    23,    25,    62,    70,    54,    52,    52,    52,    64,
      52,    53,    52,    41,    60,    41,    60,    60,    41,    52,
      60,    52,    60,    60,    60,    60,    60,    61,    60,    64,
      65,    52,     8,    41,    60,    61,    65,    60,    52,    60,
      52,    52,    60,    52,    67,    52,    52,    52,    52,    52,
      52,    42,    11,    12,    52,    60,    52,    52,    12,    54,
      54,    54,    21,    66,    26,    52,    52,    52,    54,    52,
      60,    60,    60,     6,    65,    52,    65,    67,    60,    67,
      42,    42,    42,    52,    24,    71,    12,    42,    52,    52,
      52,    68,    52,    65,    52,    52,    17,    18,    19,    20,
      22,    23,    25,    62,    74,    27,    28,    72,    67,    60,
      60,    60,    60,    52,    60,    61,    52,    52,    52,    52,
      52,    52,    52,    52,    73,    69,    26,    65,    68,    52,
      28,    24,    75,    52,    52,    68,    27,    28,    76,    52,
      52,    77,    68,    28,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    56,    56,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    59,    59,
      59,    59,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    65,    65,    65,    67,    67,    68,    68,    68,
      68,    68,    68,    69,    68,    68,    71,    70,    72,    73,
      72,    75,    74,    76,    77,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    12,     9,     9,     6,     2,     3,     4,
       4,     8,     4,     1,     2,     3,     3,     3,     2,     2,
       2,     2,     3,     2,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     4,     4,     8,     4,
       1,     2,     0,     3,     2,     0,     4,     4,     8,     4,
       8,     4,     2,     0,     8,     4,     4,     4,     4,     4,
       3,     0,     8,     2,     2,     0,     7,     0,     4,     4,
       4,     4,     2,     0,     8,     2,     0,     8,     2,     0,
       6,     0,     8,     2,     0,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 401 "calculadora.y" /* yacc.c:1646  */
    {}
#line 1885 "calculadora.c" /* yacc.c:1646  */
    break;

  case 9:
#line 410 "calculadora.y" /* yacc.c:1646  */
    {if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = (yyvsp[-1].c_real); break;
                                                                  case 1: var->valor.valor_real = (yyvsp[-1].c_real); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero";break;
                                                                  case 1: cout<<"real"  ;break;
                                                                  case 2: cout<<"logico";break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                            cout << " y no se le puede asignar tipo ";
                                                            switch (check_tipo_num()){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = (yyvsp[-1].c_real); break;
                                                                  case 1: var->valor.valor_real = (yyvsp[-1].c_real); break;
                                                            }
                                                      if(!insertar(var,true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      
                                                
                                          };
                                    
                                    reset_flags();
                                    }
#line 1937 "calculadora.c" /* yacc.c:1646  */
    break;

  case 10:
#line 457 "calculadora.y" /* yacc.c:1646  */
    {
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var)!=0){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, (yyvsp[-1].c_cadena));
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, (yyvsp[-1].c_cadena));
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      reset_flags();
      }
#line 1970 "calculadora.c" /* yacc.c:1646  */
    break;

  case 11:
#line 485 "calculadora.y" /* yacc.c:1646  */
    {if(!real_final){
                                                      if(tabla->buscar((yyvsp[-7].c_cadena), var)!=0){
                                                            if(var->tipo == 4){
                                                                  strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = (yyvsp[-4].c_real);
                                                                  var->valor.valor_pos[1] = (yyvsp[-2].c_real);
                                                                  if(!insertar(var, true, false))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                            }
                                                            else{
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-7].c_cadena)<<" es de tipo ";
                                                                  switch (var->tipo){
                                                                        case 0: cout<<"entero"<<endl;break;
                                                                        case 1: cout<<"real"<<endl;break;
                                                                        case 2: cout<<"logico"<<endl;break;
                                                                        case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                        case 4: cout<<"posicion"<<endl;break;
                                                                  }
                                                            }
                                                      }
                                                      else{strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = (yyvsp[-4].c_real);
                                                                  var->valor.valor_pos[1] = (yyvsp[-2].c_real);
                                                            if(!insertar(var, true, true))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                }
                                                else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, las coordenadas de la posición deben ser valores enteros"<<endl;
                                                reset_flags();
                                          }
#line 2008 "calculadora.c" /* yacc.c:1646  */
    break;

  case 12:
#line 519 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = (yyvsp[-1].c_bool); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = (yyvsp[-1].c_bool); break;
                                                            }
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                          };
                                    reset_flags();
                                    }
#line 2047 "calculadora.c" /* yacc.c:1646  */
    break;

  case 13:
#line 553 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2053 "calculadora.c" /* yacc.c:1646  */
    break;

  case 14:
#line 555 "calculadora.y" /* yacc.c:1646  */
    {yyerrok;reset_flags();}
#line 2059 "calculadora.c" /* yacc.c:1646  */
    break;

  case 15:
#line 557 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                          cout << (yyvsp[-1].c_cadena) <<endl;
                                          reset_flags();
                                          if(fileInicializado){
                                                finalFile<<"entornoMostrarMensaje(\""<<(yyvsp[-1].c_cadena)<<"\");"<<endl;}
                                          }
                                          if(bucle){
                                                dato_vector_bucle d;
                                                d.tipo_instruccion = 5;
                                                d.tipo = 3;
                                                strcpy(d.dato.valor_cad,(yyvsp[-1].c_cadena));
                                                vect.instrucciones.insert({vect.instrucciones.size(),d});
                                          }
                              }
#line 2078 "calculadora.c" /* yacc.c:1646  */
    break;

  case 16:
#line 571 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                    if(str){
                                          cout << var->valor.valor_cad <<endl;
                                          if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<var->valor.valor_cad<<"\");"<<endl;}
                                          if(bucle){
                                                dato_vector_bucle d;
                                                d.tipo_instruccion = 5;
                                                d.tipo = 3;
                                                strcpy(d.dato.valor_cad, var->valor.valor_cad);
                                                vect.instrucciones.insert({vect.instrucciones.size(),d});
                                          }
                                    }else if(posVar){
                                          cout <<"<"<< var->valor.valor_pos[0] <<","<<var->valor.valor_pos[1]<<">"<<endl;
                                          if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<"<"<< var->valor.valor_pos[0] <<","<<var->valor.valor_pos[1]<<">"<<"\");"<<endl;}
                                          if(bucle){
                                                dato_vector_bucle d;
                                                d.tipo_instruccion = 5;
                                                d.tipo = 4;
                                                d.dato.valor_pos[0] = var->valor.valor_pos[0];
                                                d.dato.valor_pos[1] = var->valor.valor_pos[1];
                                                vect.instrucciones.insert({vect.instrucciones.size(),d});
                                          }
                                    }
                                    else {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<(yyvsp[-1].c_real)<<"\");"<<endl;}
                                          cout <<(yyvsp[-1].c_real)<<endl;
                                          if(bucle){
                                                dato_vector_bucle d;
                                                d.tipo_instruccion = 5;
                                                d.tipo = 1;
                                                d.dato.valor_real = (yyvsp[-1].c_real);
                                                vect.instrucciones.insert({vect.instrucciones.size(),d});
                                          }
                                    }
                              }
                              reset_flags();}}
#line 2118 "calculadora.c" /* yacc.c:1646  */
    break;

  case 17:
#line 606 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                    if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                if(cmp){	
                                                      if((yyvsp[-1].c_bool))	
                                                            {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\"true\");"<<endl;}cout<<"true";
                                                                  if(bucle){
                                                                        dato_vector_bucle d;
                                                                        d.tipo_instruccion = 5;
                                                                        d.tipo = 3;
                                                                        strcpy(d.dato.valor_cad, "true");
                                                                        vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                                  }
                                                            }	
                                                      else {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\"false\");"<<endl;}
                                                            cout<<"false";
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 5;
                                                                  d.tipo = 3;
                                                                  strcpy(d.dato.valor_cad, "false");
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                      }	
                                                }	
                                                else	
                                                      {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<(yyvsp[-1].c_bool)<<"\");"<<endl;}
                                                      cout<<(yyvsp[-1].c_bool);
                                                      if(bucle){
                                                            dato_vector_bucle d;
                                                            d.tipo_instruccion = 5;
                                                            d.tipo = 1;
                                                            d.dato.valor_real = (yyvsp[-1].c_bool);
                                                            vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                      }
                                                }	
                                                cout<<endl;
                                    }
                                    reset_flags();}
      }
#line 2162 "calculadora.c" /* yacc.c:1646  */
    break;

  case 18:
#line 648 "calculadora.y" /* yacc.c:1646  */
    {
                              if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=0;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 2175 "calculadora.c" /* yacc.c:1646  */
    break;

  case 19:
#line 656 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=1;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 2187 "calculadora.c" /* yacc.c:1646  */
    break;

  case 20:
#line 663 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=3;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 2199 "calculadora.c" /* yacc.c:1646  */
    break;

  case 21:
#line 670 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=4;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 2211 "calculadora.c" /* yacc.c:1646  */
    break;

  case 22:
#line 677 "calculadora.y" /* yacc.c:1646  */
    {int temp = var->tipo;
                                    if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                          strcpy(var->nombre, (yyvsp[0].c_cadena));
                                          var->tipo = temp;
                                          if(!insertar(var, false, false))
                                                cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 2224 "calculadora.c" /* yacc.c:1646  */
    break;

  case 23:
#line 685 "calculadora.y" /* yacc.c:1646  */
    {yyerrok;reset_flags();}
#line 2230 "calculadora.c" /* yacc.c:1646  */
    break;

  case 24:
#line 688 "calculadora.y" /* yacc.c:1646  */
    {real=true;real_final=true;(yyval.c_real)=(yyvsp[0].c_real);}
#line 2236 "calculadora.c" /* yacc.c:1646  */
    break;

  case 25:
#line 689 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_real)=(yyvsp[0].c_entero);}
#line 2242 "calculadora.c" /* yacc.c:1646  */
    break;

  case 26:
#line 690 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 1){
                                    switch(var->tipo){
                                          case 0: (yyval.c_real)=var->valor.valor_entero;break;
                                          case 1: (yyval.c_real)=var->valor.valor_real;real=true;real_final=true;break;
                                          case 2: cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<(yyvsp[0].c_cadena)<<" de tipo logico no puede estar en la parte derecha de la asignacion"<<endl;error_bool_derecha=true;break;
                                          case 3: str = true;break;
                                          case 4: posVar = true;break;
                                    }    
                              }
                              else{
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<(yyvsp[0].c_cadena)<<" no ha sido definida previamente"<<endl;
                                    error_nodef = true;
                                    }
                              }
#line 2261 "calculadora.c" /* yacc.c:1646  */
    break;

  case 27:
#line 704 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_real)=(yyvsp[-1].c_real);}
#line 2267 "calculadora.c" /* yacc.c:1646  */
    break;

  case 28:
#line 705 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)+(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2273 "calculadora.c" /* yacc.c:1646  */
    break;

  case 29:
#line 706 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)-(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2279 "calculadora.c" /* yacc.c:1646  */
    break;

  case 30:
#line 707 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)*(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2285 "calculadora.c" /* yacc.c:1646  */
    break;

  case 31:
#line 708 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar){ 
                                    if(real){
                                          (yyval.c_real)=(float)((yyvsp[-2].c_real)/(yyvsp[0].c_real));
                                          real=false;
                                          }
                                    else{
                                          (yyval.c_real)=(int)((yyvsp[-2].c_real)/(yyvsp[0].c_real));
                                          };
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl; error_str = true;}
                              
                              }
#line 2302 "calculadora.c" /* yacc.c:1646  */
    break;

  case 32:
#line 720 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=pow((yyvsp[-2].c_real),(yyvsp[0].c_real));else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2308 "calculadora.c" /* yacc.c:1646  */
    break;

  case 33:
#line 721 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) {if(!real){
                                          (yyval.c_real)=(int)(yyvsp[-2].c_real)%(int)(yyvsp[0].c_real);
                                          }
                                    else {
                                          error_mod=true;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador % no se puede usar con datos de tipo real" <<endl;
                                          }
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}
                              }
#line 2323 "calculadora.c" /* yacc.c:1646  */
    break;

  case 34:
#line 731 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)= -(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2329 "calculadora.c" /* yacc.c:1646  */
    break;

  case 35:
#line 733 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;(yyval.c_bool)=(yyvsp[0].c_bool);}
#line 2335 "calculadora.c" /* yacc.c:1646  */
    break;

  case 36:
#line 734 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_bool)=(yyvsp[-1].c_bool);}
#line 2341 "calculadora.c" /* yacc.c:1646  */
    break;

  case 37:
#line 735 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) < (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2347 "calculadora.c" /* yacc.c:1646  */
    break;

  case 38:
#line 736 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) > (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2353 "calculadora.c" /* yacc.c:1646  */
    break;

  case 39:
#line 737 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) <= (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2359 "calculadora.c" /* yacc.c:1646  */
    break;

  case 40:
#line 738 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) >= (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2365 "calculadora.c" /* yacc.c:1646  */
    break;

  case 41:
#line 739 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) == (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2371 "calculadora.c" /* yacc.c:1646  */
    break;

  case 42:
#line 740 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) != (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 2377 "calculadora.c" /* yacc.c:1646  */
    break;

  case 43:
#line 741 "calculadora.y" /* yacc.c:1646  */
    {
                              cmp=true;
                              if(((yyvsp[-2].c_bool)==1||(yyvsp[-2].c_bool)==0)&&((yyvsp[0].c_bool)==1||(yyvsp[0].c_bool)==0))
                                    {if((yyvsp[-2].c_bool)==1 && (yyvsp[0].c_bool)==1)
                                          (yyval.c_bool)=1;
                                    else 
                                          (yyval.c_bool)=0;
                                    }
                              else{
                                    error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador AND sólo acepta expresiones tipo lógico" <<endl;
                                    }
                              }
#line 2395 "calculadora.c" /* yacc.c:1646  */
    break;

  case 44:
#line 755 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;
                              if(((yyvsp[-2].c_bool)==1||(yyvsp[-2].c_bool)==0)&&((yyvsp[0].c_bool)==1||(yyvsp[0].c_bool)==0))
                              {     if((yyvsp[-2].c_bool)==1||(yyvsp[0].c_bool)==1)
                                          (yyval.c_bool)=1;
                                    else {
                                          (yyval.c_bool)=0;
                                          }
                                    }
                              else{
                                          error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador OR sólo acepta expresiones tipo lógico" <<endl;
                                    }    
                              }
#line 2413 "calculadora.c" /* yacc.c:1646  */
    break;

  case 45:
#line 768 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_bool)=!(yyvsp[0].c_bool);}
#line 2419 "calculadora.c" /* yacc.c:1646  */
    break;

  case 46:
#line 771 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = (yyvsp[-1].c_real); break;
                                                                  case 1: var->valor.valor_real = (yyvsp[-1].c_real); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero";break;
                                                                  case 1: cout<<"real"  ;break;
                                                                  case 2: cout<<"logico";break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                            cout << " y no se le puede asignar tipo ";
                                                            switch (check_tipo_num()){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, variable no inicializada en el bloque DEFINICIONES."<<endl;}
                                                      
                                                
                                          };
                                    
                                    reset_flags();}
                                    }
#line 2463 "calculadora.c" /* yacc.c:1646  */
    break;

  case 47:
#line 810 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var)!=0){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, (yyvsp[-1].c_cadena));
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, variable no inicializada en el bloque DEFINICIONES."<<endl;}
                                                reset_flags();}
      }
#line 2491 "calculadora.c" /* yacc.c:1646  */
    break;

  case 48:
#line 833 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!real_final){
                                                      if(tabla->buscar((yyvsp[-7].c_cadena), var)!=0){
                                                            if(var->tipo == 4){
                                                                  strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = (yyvsp[-4].c_real);
                                                                  var->valor.valor_pos[1] = (yyvsp[-2].c_real);
                                                                  if(!insertar(var, true, false))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                            }
                                                            else{
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-7].c_cadena)<<" es de tipo ";
                                                                  switch (var->tipo){
                                                                        case 0: cout<<"entero"<<endl;break;
                                                                        case 1: cout<<"real"<<endl;break;
                                                                        case 2: cout<<"logico"<<endl;break;
                                                                        case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                        case 4: cout<<"posicion"<<endl;break;
                                                                  }
                                                            }
                                                      }
                                                      else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, variable no inicializada en el bloque DEFINICIONES."<<endl;}
                                                }
                                                else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, las coordenadas de la posición deben ser valores enteros"<<endl;
                                                reset_flags();}
                                          }
#line 2522 "calculadora.c" /* yacc.c:1646  */
    break;

  case 49:
#line 860 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = (yyvsp[-1].c_bool); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, variable no inicializada en el bloque DEFINICIONES."<<endl;}
                                          };
                                    reset_flags();}
                                    }
#line 2554 "calculadora.c" /* yacc.c:1646  */
    break;

  case 50:
#line 887 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2560 "calculadora.c" /* yacc.c:1646  */
    break;

  case 51:
#line 888 "calculadora.y" /* yacc.c:1646  */
    {yyerrok;reset_flags();}
#line 2566 "calculadora.c" /* yacc.c:1646  */
    break;

  case 52:
#line 891 "calculadora.y" /* yacc.c:1646  */
    {initFile();}
#line 2572 "calculadora.c" /* yacc.c:1646  */
    break;

  case 55:
#line 895 "calculadora.y" /* yacc.c:1646  */
    {if(!fileInicializado)initFile();}
#line 2578 "calculadora.c" /* yacc.c:1646  */
    break;

  case 56:
#line 896 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(3<(yyvsp[-2].c_real) && (yyvsp[-2].c_real)<11){dimension_glob = (yyvsp[-2].c_real);
                                                                                          posSalida_glob[0]=(yyvsp[-2].c_real)-1;
                                                                                          posSalida_glob[1]=(yyvsp[-2].c_real)-1;
                                                                                          finalFile<<"entornoTerminar();"<<endl;
                                                                                          finalFile<<"entornoIniciar("<<dimension_glob<<");"<<endl;}
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de DIMENSION debe estar entre 4 y 10"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de DIMENSION erróneo"<<endl;};
                                                                  reset_flags();}
#line 2592 "calculadora.c" /* yacc.c:1646  */
    break;

  case 57:
#line 905 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
                                                                        if(0<=var->valor.valor_pos[0] && var->valor.valor_pos[0] < dimension_glob && 0 <= var->valor.valor_pos[1] && var->valor.valor_pos[1] < dimension_glob){
                                                                              if(var->valor.valor_pos[0] != posSalida_glob[0] || var->valor.valor_pos[1] != posSalida_glob[1]){
                                                                                    if(var->valor.valor_pos[0] == 0 || var->valor.valor_pos[0] == dimension_glob-1 || var->valor.valor_pos[1] == 0 || var->valor.valor_pos[1] == dimension_glob-1){
                                                                                          posEntrada_glob[0] = var->valor.valor_pos[0];
                                                                                          posEntrada_glob[1] = var->valor.valor_pos[1];
                                                                                          finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar al borde del tablero"<<endl;   
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA no puede coincidir con la SALIDA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA erróneo"<<endl;};
                                                                  reset_flags();}
#line 2610 "calculadora.c" /* yacc.c:1646  */
    break;

  case 58:
#line 918 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= (yyvsp[-4].c_real) && (yyvsp[-4].c_real) < dimension_glob && 0 <= (yyvsp[-2].c_real) && (yyvsp[-2].c_real) < dimension_glob){
                                                                              if((yyvsp[-4].c_real) != posSalida_glob[0] || (yyvsp[-2].c_real) != posSalida_glob[1]){
                                                                                    if((yyvsp[-4].c_real) == 0 || (yyvsp[-4].c_real) == dimension_glob-1 || (yyvsp[-2].c_real) == 0 || (yyvsp[-2].c_real) == dimension_glob-1){
                                                                                          posEntrada_glob[0] = (yyvsp[-4].c_real);
                                                                                          posEntrada_glob[1] = (yyvsp[-2].c_real);
                                                                                          finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar al borde del tablero"<<endl;
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA no puede coincidir con la SALIDA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA erróneo"<<endl;};
                                                                  reset_flags();}
#line 2628 "calculadora.c" /* yacc.c:1646  */
    break;

  case 59:
#line 931 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
                                                                        if(0<=var->valor.valor_pos[0] && var->valor.valor_pos[0] < dimension_glob && 0 <= var->valor.valor_pos[1] && var->valor.valor_pos[1] < dimension_glob){
                                                                              if(var->valor.valor_pos[0] != posEntrada_glob[0] || var->valor.valor_pos[1] != posEntrada_glob[1]){
                                                                                    if(var->valor.valor_pos[0] == 0 || var->valor.valor_pos[0] == dimension_glob-1 || var->valor.valor_pos[1] == 0 || var->valor.valor_pos[1] == dimension_glob-1){
                                                                                          posSalida_glob[0] = var->valor.valor_pos[0];
                                                                                          posSalida_glob[1] = var->valor.valor_pos[1];
                                                                                          finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar al borde del tablero"<<endl;   
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA no puede coincidir con la ENTRADA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA erróneo"<<endl;};
                                                                  reset_flags();}
#line 2646 "calculadora.c" /* yacc.c:1646  */
    break;

  case 60:
#line 944 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= (yyvsp[-4].c_real) && (yyvsp[-4].c_real) < dimension_glob && 0 <= (yyvsp[-2].c_real) && (yyvsp[-2].c_real) < dimension_glob){
                                                                              if((yyvsp[-4].c_real) != posEntrada_glob[0] || (yyvsp[-2].c_real) != posEntrada_glob[1]){
                                                                                    if((yyvsp[-4].c_real) == 0 || (yyvsp[-4].c_real) == dimension_glob-1 || (yyvsp[-2].c_real) == 0 || (yyvsp[-2].c_real) == dimension_glob-1){
                                                                                          posSalida_glob[0] = (yyvsp[-4].c_real);
                                                                                          posSalida_glob[1] = (yyvsp[-2].c_real);
                                                                                          finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar al borde del tablero"<<endl;
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA no puede coincidir con la ENTRADA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA erróneo"<<endl;};
                                                                  reset_flags();}
#line 2664 "calculadora.c" /* yacc.c:1646  */
    break;

  case 61:
#line 957 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&(check_tipo_num()==0 || check_tipo_num()==1)){
                                                                        if(0 < (yyvsp[-1].c_real)) pausa_glob = (yyvsp[-1].c_real);
                                                                  }reset_flags();}
#line 2672 "calculadora.c" /* yacc.c:1646  */
    break;

  case 63:
#line 962 "calculadora.y" /* yacc.c:1646  */
    {if(!fileInicializado)initFile();}
#line 2678 "calculadora.c" /* yacc.c:1646  */
    break;

  case 64:
#line 963 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= (yyvsp[-4].c_real) && (yyvsp[-4].c_real) < dimension_glob && 0 <= (yyvsp[-2].c_real) && (yyvsp[-2].c_real) < dimension_glob){
                                                                              if(((yyvsp[-4].c_real) != posSalida_glob[0] || (yyvsp[-2].c_real) != posSalida_glob[1]) && ((yyvsp[-4].c_real) != posEntrada_glob[0] || (yyvsp[-2].c_real) != posEntrada_glob[1])){
                                                                                    matriz_obstaculos[(int)(yyvsp[-4].c_real)][(int)(yyvsp[-2].c_real)] = 1;
                                                                                    finalFile<<"entornoPonerObstaculo("<<(yyvsp[-2].c_real)<<","<<(yyvsp[-4].c_real)<<");"<<endl;
                                                                                    cout<<"OBSTACULO colocado en <"<<(yyvsp[-4].c_real)<<","<<(yyvsp[-2].c_real)<<">"<<endl;
                                                                                    posActual[0] = (yyvsp[-4].c_real);
                                                                                    posActual[1] = (yyvsp[-2].c_real);
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO no puede coincidir con la ENTRADA o SALIDA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO erróneo"<<endl;};
                                                                  reset_flags();}}
#line 2696 "calculadora.c" /* yacc.c:1646  */
    break;

  case 65:
#line 976 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
                                                      if(0<=var->valor.valor_pos[0] && var->valor.valor_pos[0] < dimension_glob && 0 <= var->valor.valor_pos[1] && var->valor.valor_pos[1] < dimension_glob){
                                                            if((var->valor.valor_pos[0] != posEntrada_glob[0] || var->valor.valor_pos[1] != posEntrada_glob[1])&&(var->valor.valor_pos[0] != posSalida_glob[0] || var->valor.valor_pos[1] != posSalida_glob[1])){
                                                                  matriz_obstaculos[var->valor.valor_pos[0]][var->valor.valor_pos[1]] = 1;
                                                                  finalFile<<"entornoPonerObstaculo("<<(int)var->valor.valor_pos[1]<<","<<(int)var->valor.valor_pos[0]<<");"<<endl;
                                                                  cout<<"OBSTACULO colocado en <"<<var->valor.valor_pos[0]<<","<<var->valor.valor_pos[1]<<">"<<endl; /*TODO*/
                                                                  posActual[0] = var->valor.valor_pos[0];
                                                                  posActual[1] = var->valor.valor_pos[1];  
                                                            }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO no puede coincidir con la ENTRADA o SALIDA"<<endl;
                                                      }
                                                      else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO debe estar dentro del tablero"<<endl;
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO erróneo"<<endl;};
                                                reset_flags();}
                                                }
#line 2715 "calculadora.c" /* yacc.c:1646  */
    break;

  case 66:
#line 990 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                      if(posActual[1]+(yyvsp[-1].c_real) < dimension_glob){
                                                            posActual[1]=posActual[1]+(yyvsp[-1].c_real);
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 1;
                                                                  d.tipo = 0;
                                                                  d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                      }else{
                                                            posActual[1]=dimension_glob-1;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al SUR!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al SUR erróneo"<<endl;};
                                                reset_flags();}
                                          }
#line 2737 "calculadora.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1007 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                      if(posActual[0]+(yyvsp[-1].c_real) < dimension_glob){
                                                            posActual[0]=posActual[0]+(yyvsp[-1].c_real);
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 2;
                                                                  d.tipo = 0;
                                                                  d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                      }else{
                                                            posActual[0]=dimension_glob-1;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al ESTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al ESTE erróneo"<<endl;};
                                                reset_flags();}}
#line 2758 "calculadora.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1023 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                      if(posActual[0]-(yyvsp[-1].c_real) >= 0){
                                                            posActual[0]=posActual[0]-(yyvsp[-1].c_real);
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 3;
                                                                  d.tipo = 0;
                                                                  d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                      }else{
                                                            posActual[0]=0;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al OESTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al OESTE erróneo"<<endl;};
                                                reset_flags();}}
#line 2779 "calculadora.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1039 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                      if(posActual[1]-(yyvsp[-1].c_real) >= 0){
                                                            posActual[1]=posActual[1]-(yyvsp[-1].c_real);
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 0;
                                                                  d.tipo = 0;
                                                                  d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                      }else{
                                                            posActual[1]=0;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al NORTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al NORTE erróneo"<<endl;};
                                                reset_flags();}}
#line 2800 "calculadora.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1055 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                            matriz_obstaculos[posActual[0]][posActual[1]] = 1;
                                                            finalFile<<"entornoPonerObstaculo("<<posActual[1]<<","<<posActual[0]<<");"<<endl;
                                                            cout<<"OBSTACULO colocado en <"<<posActual[0]<<","<<posActual[1]<<">"<<endl; /*TODO*/;
                                                            if(bucle){
                                                                  dato_vector_bucle d;
                                                                  d.tipo_instruccion = 4;
                                                                  vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                            }
                                                            reset_flags();}
                                                }
#line 2816 "calculadora.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1066 "calculadora.y" /* yacc.c:1646  */
    {if(!bucle){
                                                bucle = true;
                                                vect.repeticiones=(yyvsp[-1].c_real);
                                          }
      }
#line 2826 "calculadora.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1070 "calculadora.y" /* yacc.c:1646  */
    {doLoop_obstaculos();vect.instrucciones.clear();bucle=false;}
#line 2832 "calculadora.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1075 "calculadora.y" /* yacc.c:1646  */
    {posActual[0]=posEntrada_glob[0]; posActual[1]=posEntrada_glob[1];
                        finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                        finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;}
#line 2840 "calculadora.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1078 "calculadora.y" /* yacc.c:1646  */
    {printVictoria();finEjemplo=false;}
#line 2846 "calculadora.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1080 "calculadora.y" /* yacc.c:1646  */
    {posActual[0]=posEntrada_glob[0]; posActual[1]=posEntrada_glob[1];
                              finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                              finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;}
#line 2854 "calculadora.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1083 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                            if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                                  if(!finEjemplo){
                                                                        moverse((int)(yyvsp[-1].c_real), 1);
                                                                        if(bucle){
                                                                              dato_vector_bucle d;
                                                                              d.tipo_instruccion = 1;
                                                                              d.tipo = 0;
                                                                              d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                              vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                                        }
                                                                  }
                                                            }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al SUR erróneo"<<endl;};
                                                      reset_flags();}
                                                      }
#line 2874 "calculadora.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1098 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                            if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                                  if(!finEjemplo){
                                                                        moverse((int)(yyvsp[-1].c_real), 2);
                                                                        if(bucle){
                                                                              dato_vector_bucle d;
                                                                              d.tipo_instruccion = 2;
                                                                              d.tipo = 0;
                                                                              d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                              vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                                        }
                                                                  }
                                                      }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al ESTE erróneo"<<endl;};
                                                      reset_flags();}
                                                      }
#line 2894 "calculadora.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1113 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                            if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                                  if(!finEjemplo){
                                                                        moverse((int)(yyvsp[-1].c_real), 3);
                                                                        if(bucle){
                                                                              dato_vector_bucle d;
                                                                              d.tipo_instruccion = 3;
                                                                              d.tipo = 0;
                                                                              d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                              vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                                        }
                                                                  }
                                                      }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al OESTE erróneo"<<endl;};
                                                      reset_flags();}
                                                      }
#line 2914 "calculadora.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1128 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar){
                                                            if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&(yyvsp[-1].c_real)>=0){
                                                                  if(!finEjemplo){
                                                                        moverse((int)(yyvsp[-1].c_real), 0);
                                                                        if(bucle){
                                                                              dato_vector_bucle d;
                                                                              d.tipo_instruccion = 0;
                                                                              d.tipo = 0;
                                                                              d.dato.valor_entero = (yyvsp[-1].c_real);
                                                                              vect.instrucciones.insert({vect.instrucciones.size(),d});
                                                                        }
                                                                  }
                                                      }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al NORTE erróneo"<<endl;};
                                                      reset_flags();}
                                                      }
#line 2934 "calculadora.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1144 "calculadora.y" /* yacc.c:1646  */
    {if(!bucle){
                                                bucle = true;
                                                vect.repeticiones=(yyvsp[-1].c_real);
                                          }
      }
#line 2944 "calculadora.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1148 "calculadora.y" /* yacc.c:1646  */
    {doLoop_ejemplos();vect.instrucciones.clear();bucle=false;}
#line 2950 "calculadora.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1152 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar)ejecutar = (yyvsp[-3].c_bool);}
#line 2956 "calculadora.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1154 "calculadora.y" /* yacc.c:1646  */
    {ejecutar = true;}
#line 2962 "calculadora.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1155 "calculadora.y" /* yacc.c:1646  */
    {ejecutar=!ejecutar;}
#line 2968 "calculadora.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1155 "calculadora.y" /* yacc.c:1646  */
    {ejecutar = true;}
#line 2974 "calculadora.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1158 "calculadora.y" /* yacc.c:1646  */
    {if(ejecutar)ejecutar = (yyvsp[-3].c_bool);}
#line 2980 "calculadora.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1160 "calculadora.y" /* yacc.c:1646  */
    {ejecutar = true;}
#line 2986 "calculadora.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1161 "calculadora.y" /* yacc.c:1646  */
    {ejecutar=!ejecutar;}
#line 2992 "calculadora.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1161 "calculadora.y" /* yacc.c:1646  */
    {ejecutar = true;}
#line 2998 "calculadora.c" /* yacc.c:1646  */
    break;


#line 3002 "calculadora.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1163 "calculadora.y" /* yacc.c:1906  */


int main(int argc, char *argv[]){
     tabla = (Tabla*)malloc(sizeof(Tabla));
     var = (tipo_datoTS*)malloc(sizeof(tipo_datoTS));
     n_lineas = 0;
     if(argc == 3) {
     		yyin=fopen(argv[1],"rt");
            finalFile.open(argv[2], std::ofstream::trunc);
     		n_lineas = 0;
       	yyparse();
            fclose(yyin);
            finalFile<<"entornoMostrarMensajeFin (\"  ¡ Fin !    \");"<<endl;	
            finalFile<<"entornoTerminar();"<<endl;
            finalFile<<"entornoPausa(1);"<<endl;
            finalFile<<"return 0;"<<endl;
            finalFile<<"}"<<endl;

            finalFile.close();
            if(errorFichero) remove(argv[2]);
            
            std::ofstream ofs ("tabla_variables.txt", std::ofstream::trunc);
            printTabla(ofs);
            ofs.close();

         	return 0;
	}
      else{
            yyin=fopen(argv[1],"rt");
            string fileName = argv[1];
            string newFileName = fileName.substr(0,fileName.find_last_of('.'))+".cpp";
            
            finalFile.open(newFileName.c_str(), std::ofstream::trunc);
     		n_lineas = 0;
       	yyparse();
            fclose(yyin);

            if(errorFichero) remove("gala.cpp");
            std::ofstream ofs ("tabla_variables.txt", std::ofstream::trunc);
            printTabla(ofs);
            ofs.close();

         	return 0;
      }
     return 0;
}
