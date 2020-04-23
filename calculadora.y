%{
#include <iostream>
#include <fstream>
#include <math.h>
#include "tabla.c"
 

using namespace std;

bool real_final=false;
bool real=false;
bool error_mod=false;
bool error_log=false;
bool error_nodef = false;
bool error_bool_derecha = false;
bool cmp=false;

Tabla* tabla;
tipo_datoTS* var;

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
}

string check_tipo(){
      if(cmp) return "logico";
      else if(real_final) return "real";
      else return "entero";
}
int check_tipo_num(){
      if(cmp) return 2;
      else if(real_final) return 1;
      else return 0;
}
void yyerror(const char* s){         /*    llamada por cada error sintactico de yacc */
	cout << "Error sintáctico en la línea \033[1;31m"<<n_lineas<<"\033[0m"<<endl;	
      reset_flags();
} 

bool insertar(tipo_datoTS *var){
      return tabla->insertar(var);
}

void printTabla(ofstream &out){
      out << "*********************************" <<endl;
      out << "***NOMBRE      TIPO      VALOR***" <<endl;
      out << "*********************************" <<endl;

      nodo* n = tabla->getFirst();
      while(n!=NULL){
            out <<"**"<< n->dato.nombre<<"            ";
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
            }
            out <<endl;
            n=n->sig;
      }
      out << "*********************************" <<endl;

}
%}
%union{
      int c_entero;
      float c_real;
      char c_cadena[20];
      bool c_bool;
}

%start lista_instrucciones

%token <c_bool> BOOL
%token <c_entero> ENTERO
%token <c_cadena> VARIABLE ESCRIBIR CADENA
%token REAL
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
      |lista_instrucciones asignacion
      ;

asignacion:VARIABLE '=' expr '\n'     	{if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar($1, var)){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = $3; break;
                                                                  case 1: var->valor.valor_real = $3; break;
                                                            }
                                                            if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero";break;
                                                                  case 1: cout<<"real"  ;break;
                                                                  case 2: cout<<"logico";break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                            }
                                                            cout << " y no se le puede asignar tipo ";
                                                            switch (check_tipo_num()){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = $3; break;
                                                                  case 1: var->valor.valor_real = $3; break;
                                                            }
                                                      if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
                                                      
                                                
                                          };
                                    
                                    reset_flags();
                                    }
      |VARIABLE '=' CADENA '\n'           {
                                                if(tabla->buscar($1, var)){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, $3);
                                                            if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, $3);
                                                      if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
      }

      |VARIABLE '=' expr_logica '\n'     	{if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar($1, var)){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = $3; break;
                                                            }
                                                            if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<$1<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, $1);
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = $3; break;
                                                            }
                                                      if(!insertar(var))
                                                                  cout<<"Error en la asignacion"<<endl;
                                                      }
                                          };
                                    reset_flags();
                                    }
      |ESCRIBIR CADENA '\n' {cout << "cad " << $2 <<endl;}
      |ESCRIBIR expr '\n' {cout << $2 <<endl;reset_flags();}
      |ESCRIBIR expr_logica '\n' {
                                    if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                if(cmp){	
                                                      if($2)	
                                                            cout<<"true";	
                                                      else cout<<"false";	
                                                }	
                                                else	
                                                      cout<<$2;	
                                                cout<<endl;
                                    }
                                    reset_flags();
      }
      |ESCRIBIR VARIABLE            {
                                          if(tabla->buscar($1, var) && var->init == true){
                                                      switch (var->tipo){
                                                                  case 0: cout<<var->valor.valor_entero<<endl;break;
                                                                  case 1: cout<<var->valor.valor_real<<endl;break;
                                                                  case 2: cout<<var->valor.valor_logico<<endl;break;
                                                                  case 3: cout<<var->valor.valor_cad<<endl;break;
                                                            }
                                          }
                                          else cout<<"Variable no inicializada"<<endl;
                                          reset_flags();

      }
      |error '\n' {yyerrok;reset_flags();}       
	;

expr:    REAL 		      {real=true;real_final=true;$$=$1;}
       | ENTERO 		      {$$=$1;}    
       | VARIABLE             {if(tabla->buscar($1, var)){
                                    switch(var->tipo){
                                          case 0: $$=var->valor.valor_entero;break;
                                          case 1: $$=var->valor.valor_real;real=true;real_final=true;break;
                                          case 2: cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<$1<<" de tipo logico no puede estar en la parte derecha de la asignacion"<<endl;error_bool_derecha=true;break;
                                    }    
                              }
                              else{
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<$1<<" no ha sido definida previamente"<<endl;
                                    error_nodef = true;
                                    }
                              }  
       | '(' expr ')'         {$$=$2;}           
       | expr '+' expr 		{$$=$1+$3;}              
       | expr '-' expr    	{$$=$1-$3;}            
       | expr '*' expr        {$$=$1*$3;} 
       | expr '/' expr        {if(real){
                                    $$=(float)($1/$3);
                                    real=false;
                                    }
                              else{
                                    $$=(int)($1/$3);
                                    };
                              }
       | expr '^' expr        {$$=pow($1,$3);}
       | expr '%' expr        {if(!real){
                                    $$=(int)$1%(int)$3;
                                    }
                              else {
                                    error_mod=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador % no se puede usar con datos de tipo real" <<endl;
                                    }
                              } 
       |'-' expr %prec menos  {$$= -$2;}
       ;
expr_logica: BOOL                 {cmp=true;$$=$1;}
       | '(' expr_logica ')'         {$$=$2;}
       |expr '<' expr         {cmp=true; if($1 < $3)$$=1;else $$=0;}
       |expr '>' expr         {cmp=true; if($1 > $3)$$=1;else $$=0;}
       |expr LE expr         {cmp=true; if($1 <= $3)$$=1;else $$=0;}
       |expr GE expr         {cmp=true; if($1 >= $3)$$=1;else $$=0;}
       |expr EQ expr         {cmp=true; if($1 == $3)$$=1;else $$=0;}
       |expr NE expr         {cmp=true; if($1 != $3)$$=1;else $$=0;}
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
%%

int main(int argc, char *argv[]){
     tabla = (Tabla*)malloc(sizeof(Tabla));
     var = (tipo_datoTS*)malloc(sizeof(tipo_datoTS));
     n_lineas = 0;
     if (argc != 3) {
		cout <<"error en los argumentos"<<endl;
            cout <<endl<<"******************************************************"<<endl;
            cout <<"*      Calculadora de expresiones aritméticas        *"<<endl;
            cout <<"*                                                    *"<<endl;
            cout <<"*      1)con el prompt LISTO>                        *"<<endl;
            cout <<"*        teclea una expresión, por ej. 1+2<ENTER>    *"<<endl;
            cout <<"*        Este programa indicará                      *"<<endl;
            cout <<"*        si es gramaticalmente correcto              *"<<endl;
            cout <<"*      2)para terminar el programa                   *"<<endl;
            cout <<"*        teclear SALIR<ENTER>                        *"<<endl;
            cout <<"*      3)si se comete algun error en la expresión    *"<<endl;
            cout <<"*        se mostrará un mensaje y la ejecución       *"<<endl;
            cout <<"*        del programa finaliza                       *"<<endl;
            cout <<"******************************************************"<<endl<<endl<<endl;
            yyparse();
            cout <<"****************************************************"<<endl;
            cout <<"*                 ADIOS!!!!                        *"<<endl;
            cout <<"****************************************************"<<endl;
	}else {
     		yyin=fopen(argv[1],"rt");
     		n_lineas = 0;
       	yyparse();
            fclose(yyin);

            std::ofstream ofs (argv[2], std::ofstream::trunc);
            printTabla(ofs);
            ofs.close();

         	return 0;
	}
     return 0;
}
