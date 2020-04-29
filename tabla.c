#include "tabla.h"
#include <stdio.h>
#include <string.h>

nodo * Tabla::getFirst(){
    return primero;
}

bool Tabla::insertar(tipo_datoTS *identificador){//inserta un dato si no existe, y si existe lo actualiza
    nodo * act = getFirst();
    nodo * aux;
    bool found = false, insertado = false;
    if(act == NULL){
        primero = (nodo*)malloc(sizeof(nodo));
        primero->dato=*identificador;
        primero->sig=NULL;
        insertado = true;
    }
    else{//Buscar el nombre del identificador, y si no se encuentra añadirlo al final
        if(strcmp(act->dato.nombre, identificador->nombre)==0){
            found=true;
        }

        while(!found && act->sig!=NULL){
            act=act->sig;
            if(strcmp(act->dato.nombre, identificador->nombre)==0)
                found=true;
        }

        if(!found){//Insertando por primera vez la variable
            aux=(nodo*)malloc(sizeof(nodo));
            aux->dato=*identificador;
            aux->sig=NULL;
            act->sig=aux;
            insertado = true;
        }
        else{//Encontrado, comprobar tipo variable y, si se puede, cambiarlo
            if(identificador->tipo == act->dato.tipo && !act->dato.cte){
                //Tipo correcto y no es constante
                act->dato.valor=identificador->valor;
                //Además indicar que se le ha asignado un valor?
                act->dato.init=true;
                insertado=true;
            }
        }
    }
    return insertado;
}

/**
 * 
 *Busca un elemento dado el nombre, y lo devuelve en la variable identificador. 
 *Si no encontrado = 0
 *Si encontrado pero !inicializado = -1
 *Si encontrado e inicializado = 1
 *  
 **/
int Tabla::buscar(tipo_cadena nombre, tipo_datoTS *identificador){
    nodo * act = getFirst();
    bool found = false;
    while (act!=NULL && !found)
    {
        if(strcmp(act->dato.nombre, nombre)==0){
            //Encontrado
            found=true;
            strcpy((*identificador).nombre, act->dato.nombre);
            (*identificador).tipo = act->dato.tipo;
            (*identificador).init = act->dato.init;
            (*identificador).cte = act->dato.cte;
            if(act->dato.cte == true){
                if(act->dato.tipo == 0){
                (*identificador).valor.valor_entero = act->dato.valor.valor_entero;
                }
                else{
                    if(act->dato.tipo == 1){
                        (*identificador).valor.valor_real = act->dato.valor.valor_real;
                    }
                    else{
                        if(act->dato.tipo == 2){
                            (*identificador).valor.valor_logico = act->dato.valor.valor_logico;
                        }
                        else{
                            if(act->dato.tipo == 3){
                                strcpy((*identificador).valor.valor_cad, act->dato.valor.valor_cad);
                            }
                            else{
                                if (act->dato == 4)
                                {
                                    (*identificador).valor.valor_pos = act->dato.valor.valor_pos;
                                }
                                
                            }  
                        }
                    }
                }
            }
        }
        else
            act = act->sig;
    }
    if (found)
    {
        if (act->dato.init == true)
        {
            return 1;
        }
        else return -1;
    }
    else return 0;
    
}