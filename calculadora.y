%{
#include <iostream>
#include <fstream>
#include <math.h>
#include "tabla.c"
#include "string.h"
#include <stdio.h>
 

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
      for(i = 0;i < pasos && !exit;i++){
            switch(direccion){
                  case 0://Norte
                        if(posActual[1] - 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al NORTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]][posActual[1]-1] == 1) {cout<<"N - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finalFile<<"entornoPonerChoque("<<posActual[1]-1<<","<<posActual[0]<<");"<<endl;}
                        else {posActual[1] = posActual[1]-1;cout << "N\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;}
                  break;
                  case 1://Sur
                        if(posActual[1] + 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al SUR!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]][posActual[1]+1] == 1) {cout<<"S - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finalFile<<"entornoPonerChoque("<<posActual[1]+1<<","<<posActual[0]<<");"<<endl;}
                        else {posActual[1] = posActual[1]+1; cout << "S\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
                  case 2://Este
                        if(posActual[0] + 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al ESTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]+1][posActual[1]] == 1) {cout<<"E - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finalFile<<"entornoPonerChoque("<<posActual[1]<<","<<posActual[0]+1<<");"<<endl;}
                        else {posActual[0] = posActual[0]+1; cout << "E\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
                  case 3://Oeste
                        if(posActual[0] - 1 < 0) {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al OESTE!"<<endl;exit=true;}
                        else if(matriz_obstaculos[posActual[0]-1][posActual[1]] == 1) {cout<<"O - Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, te has dado contra un OBSTACULO!"<<endl;exit=true;finalFile<<"entornoPonerChoque("<<posActual[1]<<","<<posActual[0]-1<<");"<<endl;}
                        else {posActual[0] = posActual[0]-1; cout << "O\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m"<<endl;finalFile<<"entornoPonerFigura("<<posActual[1]<<","<<posActual[0]<<","<<pausa_glob<<");"<<endl;};
                  break;
            }
            if(posActual[0] == posSalida_glob[0] && posActual[1] == posSalida_glob[1]) {cout << "\033[1;33mHas encontrado la salida en \033[0m"<< "\033[1;32m<"<<posActual[0]<<","<<posActual[1]<<">"<<"\033[0m!!"<<endl;exit=true;finalFile<<"entornoPonerFiguraSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;printVictoria();finEjemplo=true;}
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
      for(i = 0; i < dimension_glob; i++){
            for(j = 0; j < dimension_glob; j++){
                  out << matriz_obstaculos[j][i]<<" ";
            }
            out<<endl;
      }
}

%}
%union{
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
}

%start lista_instrucciones

%token <c_bool> BOOL
%token <c_entero> ENTERO
%token <c_cadena> OBSTACULO VARIABLE ESCRIBIR CADENA DEFINICIONES CONFIGURACION OBSTACULOS EJEMPLOS DIMENSION ENTRADA SALIDA PAUSA NORTE SUR ESTE OESTE EJEMPLO FINEJEMPLO REPITE FINREPITE IF THEN ELSE ENDIF
%token REAL
%token INT FLOAT STRING POS
%token OR AND NOT LE GE EQ NE

%type <c_real> expr REAL
%type <c_bool> expr_logica
%left OR
%left AND
%right NOT
%left '<' LE '>' GE EQ NE
%left '+' '-'  /* asociativo por la izquierda, misma prioridad */
%left '*' '/' '%' /* asociativo por la izquierda, prioridad alta */
%right '^'   /* asociativo por la derecha, prioridad más alta */
 
%left '(' ')'     /* paréntesis */
%left menos


%%
lista_instrucciones: 		{}
      |DEFINICIONES '\n' bloque_definiciones CONFIGURACION '\n' bloque_configuracion OBSTACULOS '\n' bloque_obstaculos EJEMPLOS '\n' bloque_ejemplos 
      |CONFIGURACION '\n' bloque_configuracion OBSTACULOS '\n' bloque_obstaculos EJEMPLOS '\n' bloque_ejemplos     
      |DEFINICIONES '\n' bloque_definiciones OBSTACULOS '\n' bloque_obstaculos EJEMPLOS '\n' bloque_ejemplos       
      |OBSTACULOS '\n' bloque_obstaculos EJEMPLOS '\n' bloque_ejemplos        
      |asignacion lista_instrucciones     
      |declaracion '\n' lista_instrucciones      
      ;

asignacion:VARIABLE '=' expr '\n'     	{if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar($1, var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = $3; break;
                                                                  case 1: var->valor.valor_real = $3; break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
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
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = $3; break;
                                                                  case 1: var->valor.valor_real = $3; break;
                                                            }
                                                      if(!insertar(var,true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      
                                                
                                          };
                                    
                                    reset_flags();
                                    }
      |VARIABLE '=' CADENA '\n'           {
                                                if(tabla->buscar($1, var)!=0){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, $3);
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, $3);
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      reset_flags();
      }
      |VARIABLE '=' '<'expr ',' expr '>' '\n'   {if(!real_final){
                                                      if(tabla->buscar($1, var)!=0){
                                                            if(var->tipo == 4){
                                                                  strcpy(var->nombre, $1);
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = $4;
                                                                  var->valor.valor_pos[1] = $6;
                                                                  if(!insertar(var, true, false))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                            }
                                                            else{
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                                  switch (var->tipo){
                                                                        case 0: cout<<"entero"<<endl;break;
                                                                        case 1: cout<<"real"<<endl;break;
                                                                        case 2: cout<<"logico"<<endl;break;
                                                                        case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                        case 4: cout<<"posicion"<<endl;break;
                                                                  }
                                                            }
                                                      }
                                                      else{strcpy(var->nombre, $1);
                                                                  strcpy(var->nombre, $1);
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = $4;
                                                                  var->valor.valor_pos[1] = $6;
                                                            if(!insertar(var, true, true))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                }
                                                else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, las coordenadas de la posición deben ser valores enteros"<<endl;
                                                reset_flags();
                                          }

      |VARIABLE '=' expr_logica '\n'     	{if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                
                                                if(tabla->buscar($1, var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = $3; break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = $3; break;
                                                            }
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                          };
                                    reset_flags();
                                    }
      |escribir   {reset_flags();}
      
      |error '\n' {yyerrok;reset_flags();}       
	;
escribir:ESCRIBIR CADENA '\n' {if(ejecutar){cout << $2 <<endl;reset_flags();if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<$2<<"\");"<<endl;}}}
      |ESCRIBIR expr '\n'     {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                    if(str){
                                          cout << var->valor.valor_cad <<endl;
                                          if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<var->valor.valor_cad<<"\");"<<endl;}
                                    }else if(posVar){
                                          cout <<"<"<< var->valor.valor_pos[0] <<","<<var->valor.valor_pos[1]<<">"<<endl;
                                          if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<"<"<< var->valor.valor_pos[0] <<","<<var->valor.valor_pos[1]<<">"<<"\");"<<endl;}
                                    }
                                    else {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<$2<<"\");"<<endl;}cout <<$2<<endl;}
                              }
                              reset_flags();}}
      |ESCRIBIR expr_logica '\n' {if(ejecutar){
                                    if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                if(cmp){	
                                                      if($2)	
                                                            {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\"true\");"<<endl;}cout<<"true";}	
                                                      else {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\"false\");"<<endl;}cout<<"false";}	
                                                }	
                                                else	
                                                      {if(fileInicializado){finalFile<<"entornoMostrarMensaje(\""<<$2<<"\");"<<endl;}cout<<$2;}	
                                                cout<<endl;
                                    }
                                    reset_flags();}
      }
      ;


declaracion: INT VARIABLE    {
                              if(tabla->buscar($2, var) == 0){
                                    var->tipo=0;
                                    strcpy(var->nombre, $2);
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
      |FLOAT VARIABLE         {if(tabla->buscar($2, var) == 0){
                                    var->tipo=1;
                                    strcpy(var->nombre, $2);
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
      |STRING VARIABLE        {if(tabla->buscar($2, var) == 0){
                                    var->tipo=3;
                                    strcpy(var->nombre, $2);
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
      |POS VARIABLE          {if(tabla->buscar($2, var) == 0){
                                    var->tipo=4;
                                    strcpy(var->nombre, $2);
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
      |declaracion ',' VARIABLE     {int temp = var->tipo;
                                    if(tabla->buscar($3, var) == 0){
                                          strcpy(var->nombre, $3);
                                          var->tipo = temp;
                                          if(!insertar(var, false, false))
                                                cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
      |error '\n' {yyerrok;reset_flags();} 
      ;

expr:    REAL 		      {real=true;real_final=true;$$=$1;}
       | ENTERO 		      {$$=$1;}    
       | VARIABLE             {if(tabla->buscar($1, var) == 1){
                                    switch(var->tipo){
                                          case 0: $$=var->valor.valor_entero;break;
                                          case 1: $$=var->valor.valor_real;real=true;real_final=true;break;
                                          case 2: cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<$1<<" de tipo logico no puede estar en la parte derecha de la asignacion"<<endl;error_bool_derecha=true;break;
                                          case 3: str = true;break;
                                          case 4: posVar = true;break;
                                    }    
                              }
                              else{
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<$1<<" no ha sido definida previamente"<<endl;
                                    error_nodef = true;
                                    }
                              }  
       | '(' expr ')'         {$$=$2;}           
       | expr '+' expr 		{if(!str&&!posVar) $$=$1+$3;else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}              
       | expr '-' expr    	{if(!str&&!posVar) $$=$1-$3;else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}            
       | expr '*' expr        {if(!str&&!posVar) $$=$1*$3;else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}} 
       | expr '/' expr        {if(!str&&!posVar){ 
                                    if(real){
                                          $$=(float)($1/$3);
                                          real=false;
                                          }
                                    else{
                                          $$=(int)($1/$3);
                                          };
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl; error_str = true;}
                              
                              }
       | expr '^' expr        {if(!str&&!posVar) $$=pow($1,$3);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       | expr '%' expr        {if(!str&&!posVar) {if(!real){
                                          $$=(int)$1%(int)$3;
                                          }
                                    else {
                                          error_mod=true;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador % no se puede usar con datos de tipo real" <<endl;
                                          }
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}
                              } 
       |'-' expr %prec menos  {if(!str&&!posVar) $$= -$2;else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       ;
expr_logica: BOOL                 {cmp=true;$$=$1;}
       | '(' expr_logica ')'         {$$=$2;}
       |expr '<' expr         {cmp=true;if(!str&&!posVar) {if($1 < $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr '>' expr         {cmp=true;if(!str&&!posVar) {if($1 > $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr LE expr         {cmp=true;if(!str&&!posVar) {if($1 <= $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr GE expr         {cmp=true;if(!str&&!posVar) {if($1 >= $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr EQ expr         {cmp=true;if(!str&&!posVar) {if($1 == $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr NE expr         {cmp=true;if(!str&&!posVar) {if($1 != $3)$$=1;else $$=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
       |expr_logica AND expr_logica		{
                              cmp=true;
                              if(($1==1||$1==0)&&($3==1||$3==0))
                                    {if($1==1 && $3==1)
                                          $$=1;
                                    else 
                                          $$=0;
                                    }
                              else{
                                    error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador AND sólo acepta expresiones tipo lógico" <<endl;
                                    }
                              }
                              
       |expr_logica OR expr_logica		{cmp=true;
                              if(($1==1||$1==0)&&($3==1||$3==0))
                              {     if($1==1||$3==1)
                                          $$=1;
                                    else {
                                          $$=0;
                                          }
                                    }
                              else{
                                          error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador OR sólo acepta expresiones tipo lógico" <<endl;
                                    }    
                              }
       |NOT expr_logica         {$$=!$2;}
       ;

asignacion_sin_ctes:VARIABLE '=' expr '\n'     	{if(ejecutar){if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar($1, var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = $3; break;
                                                                  case 1: var->valor.valor_real = $3; break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
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
      |VARIABLE '=' CADENA '\n'           {if(ejecutar){
                                                if(tabla->buscar($1, var)!=0){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, $3);
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
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
      |VARIABLE '=' '<'expr ',' expr '>' '\n'   {if(ejecutar){if(!real_final){
                                                      if(tabla->buscar($1, var)!=0){
                                                            if(var->tipo == 4){
                                                                  strcpy(var->nombre, $1);
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = $4;
                                                                  var->valor.valor_pos[1] = $6;
                                                                  if(!insertar(var, true, false))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                            }
                                                            else{
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
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

      |VARIABLE '=' expr_logica '\n'     	{if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                
                                                if(tabla->buscar($1, var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = $3; break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
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
      |escribir   {reset_flags();}
      |error '\n' {yyerrok;reset_flags();}       
	;

bloque_definiciones: {initFile();}
      |bloque_definiciones declaracion '\n'
      |bloque_definiciones asignacion
      ;
bloque_configuracion:   {if(!fileInicializado)initFile();}
      |DIMENSION expr bloque_configuracion '\n'                   {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(3<$2 && $2<11){dimension_glob = $2;
                                                                                          posSalida_glob[0]=$2-1;
                                                                                          posSalida_glob[1]=$2-1;
                                                                                          finalFile<<"entornoTerminar();"<<endl;
                                                                                          finalFile<<"entornoIniciar("<<dimension_glob<<");"<<endl;}
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de DIMENSION debe estar entre 4 y 10"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de DIMENSION erróneo"<<endl;};
                                                                  reset_flags();}
      |bloque_configuracion ENTRADA expr '\n'                     {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
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
      |bloque_configuracion ENTRADA '<'expr ',' expr '>' '\n'     {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= $4 && $4 < dimension_glob && 0 <= $6 && $6 < dimension_glob){
                                                                              if($4 != posSalida_glob[0] || $6 != posSalida_glob[1]){
                                                                                    if($4 == 0 || $4 == dimension_glob-1 || $6 == 0 || $6 == dimension_glob-1){
                                                                                          posEntrada_glob[0] = $4;
                                                                                          posEntrada_glob[1] = $6;
                                                                                          finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar al borde del tablero"<<endl;
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA no puede coincidir con la SALIDA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de ENTRADA erróneo"<<endl;};
                                                                  reset_flags();}
      |bloque_configuracion SALIDA expr '\n'                      {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
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
      |bloque_configuracion SALIDA '<'expr ',' expr '>' '\n'      {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= $4 && $4 < dimension_glob && 0 <= $6 && $6 < dimension_glob){
                                                                              if($4 != posEntrada_glob[0] || $6 != posEntrada_glob[1]){
                                                                                    if($4 == 0 || $4 == dimension_glob-1 || $6 == 0 || $6 == dimension_glob-1){
                                                                                          posSalida_glob[0] = $4;
                                                                                          posSalida_glob[1] = $6;
                                                                                          finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;
                                                                                    }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar al borde del tablero"<<endl;
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA no puede coincidir con la ENTRADA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de SALIDA erróneo"<<endl;};
                                                                  reset_flags();}
      |bloque_configuracion PAUSA expr '\n'                       {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&(check_tipo_num()==0 || check_tipo_num()==1)){
                                                                        if(0 < $3) pausa_glob = $3;
                                                                  }reset_flags();}
      |bloque_configuracion asignacion_sin_ctes
      ;
bloque_obstaculos:      {if(!fileInicializado)initFile();}
      |bloque_obstaculos OBSTACULO '<'expr ',' expr '>' '\n' {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0){
                                                                        if(0 <= $4 && $4 < dimension_glob && 0 <= $6 && $6 < dimension_glob){
                                                                              if(($4 != posSalida_glob[0] || $6 != posSalida_glob[1]) && ($4 != posEntrada_glob[0] || $6 != posEntrada_glob[1])){
                                                                                    matriz_obstaculos[(int)$4][(int)$6] = 1;
                                                                                    finalFile<<"entornoPonerObstaculo("<<$6<<","<<$4<<");"<<endl;
                                                                                    cout<<"OBSTACULO colocado en <"<<$4<<","<<$6<<">"<<endl;
                                                                                    posActual[0] = $4;
                                                                                    posActual[1] = $6;
                                                                              }else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO no puede coincidir con la ENTRADA o SALIDA"<<endl;
                                                                        }
                                                                        else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO debe estar dentro del tablero"<<endl;
                                                                  }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor de OBSTACULO erróneo"<<endl;};
                                                                  reset_flags();}}
      |bloque_obstaculos OBSTACULO expr '\n'    {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==4){
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
      |bloque_obstaculos SUR expr '\n'          {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(posActual[1]+$3 < dimension_glob){
                                                            posActual[1]=posActual[1]+$3;
                                                      }else{
                                                            posActual[1]=dimension_glob-1;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al SUR!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al SUR erróneo"<<endl;};
                                                reset_flags();}
                                          }
      |bloque_obstaculos ESTE expr '\n'         {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(posActual[0]+$3 < dimension_glob){
                                                            posActual[0]=posActual[0]+$3;
                                                      }else{
                                                            posActual[0]=dimension_glob-1;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al ESTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al ESTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_obstaculos OESTE expr '\n'        {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(posActual[0]-$3 >= 0){
                                                            posActual[0]=posActual[0]-$3;
                                                      }else{
                                                            posActual[0]=0;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al OESTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al OESTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_obstaculos NORTE expr '\n'        {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(posActual[1]-$3 >= 0){
                                                            posActual[1]=posActual[1]-$3;
                                                      }else{
                                                            posActual[1]=0;
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, no puedes moverte tanto al NORTE!"<<endl;
                                                      }
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al NORTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_obstaculos OBSTACULO '\n'         {if(ejecutar){matriz_obstaculos[posActual[0]][posActual[1]] = 1;
                                                finalFile<<"entornoPonerObstaculo("<<posActual[1]<<","<<posActual[0]<<");"<<endl;
                                                cout<<"OBSTACULO colocado en <"<<posActual[0]<<","<<posActual[1]<<">"<<endl; /*TODO*/;
                                                reset_flags();}}
      |bloque_obstaculos REPITE expr '\n' bloque_obstaculos FINREPITE '\n' {}
      |bloque_obstaculos condicional_obstaculos
      |bloque_obstaculos asignacion_sin_ctes
      ;

bloque_ejemplos:  {posActual[0]=posEntrada_glob[0]; posActual[1]=posEntrada_glob[1];
                        finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                        finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;}
      |bloque_ejemplos EJEMPLO VARIABLE '\n' bloque_ejemplos_anidado FINEJEMPLO '\n' {printVictoria();finEjemplo=false;}
      ;
bloque_ejemplos_anidado:      {posActual[0]=posEntrada_glob[0]; posActual[1]=posEntrada_glob[1];
                              finalFile<<"entornoPonerEntrada("<<posEntrada_glob[1]<<","<<posEntrada_glob[0]<<","<<pausa_glob<<");"<<endl;
                              finalFile<<"entornoPonerSalida("<<posSalida_glob[1]<<","<<posSalida_glob[0]<<");"<<endl;}
      |bloque_ejemplos_anidado SUR expr '\n'          {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(!finEjemplo)moverse((int)$3, 1);
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al SUR erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_ejemplos_anidado ESTE expr '\n'         {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(!finEjemplo)moverse((int)$3, 2);
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al ESTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_ejemplos_anidado OESTE expr '\n'        {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(!finEjemplo)moverse((int)$3, 3);
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al OESTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_ejemplos_anidado NORTE expr '\n'        {if(ejecutar){if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str&&check_tipo_num()==0&&$3>=0){
                                                      if(!finEjemplo)moverse((int)$3, 0);
                                                }else{cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, valor para moverte al NORTE erróneo"<<endl;};
                                                reset_flags();}}
      |bloque_ejemplos_anidado asignacion_sin_ctes
      |bloque_ejemplos_anidado condicional_ejemplos
      ;

condicional_obstaculos:IF expr_logica '\n' {ejecutar = $2;} THEN '\n' bloque_obstaculos cierre_condicional_obstaculos
      ;
cierre_condicional_obstaculos: ENDIF '\n' {ejecutar = true;}
      |ELSE '\n' {if(!ejecutar)ejecutar = true; else ejecutar = false;} bloque_obstaculos ENDIF '\n' {ejecutar = true;}
      ;

condicional_ejemplos:IF expr_logica '\n' {ejecutar = $2;} THEN '\n' bloque_ejemplos_anidado cierre_condicional_ejemplos
      ;
cierre_condicional_ejemplos: ENDIF '\n' {ejecutar = true;}
      |ELSE '\n' {if(!ejecutar)ejecutar = true; else ejecutar = false;} bloque_ejemplos_anidado ENDIF '\n' {ejecutar = true;}
      ;
%%

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
            finalFile.open("gala.cpp", std::ofstream::trunc);
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