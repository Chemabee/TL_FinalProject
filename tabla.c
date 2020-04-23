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
        if (identificador->init == true)
        {
            primero->dato.init = true;
        }
        else primero->dato.init = false;
        
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

        if(!found){
            aux=(nodo*)malloc(sizeof(nodo));
            aux->dato=*identificador;
            aux->sig=NULL;
            act->sig=aux;
            insertado = true;
        }
        else{//Encontrado, comprobar tipo variable y, si se puede, cambiarlo
            if(identificador->tipo == act->dato.tipo){
                //Tipo correcto
                act->dato.valor=identificador->valor;
                insertado=true;
            }
        }
    }
    return insertado;
}

bool Tabla::buscar(tipo_cadena nombre, tipo_datoTS *identificador){
    nodo * act = getFirst();
    bool found = false;
    while (act!=NULL && !found)
    {
        if(strcmp(act->dato.nombre, nombre)==0){
            //Encontrado
            found=true;
            strcpy((*identificador).nombre, act->dato.nombre);
            (*identificador).tipo = act->dato.tipo;
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
                }
            }
        }
        else
            act = act->sig;
    }
    return found;
}