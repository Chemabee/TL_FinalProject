#include <iostream>
#include <allegro5/allegro.h>
#include <stdio.h>
#include "entorno.h"
using namespace std;
int main(int argc, char** argv){
entornoIniciar (10);
entornoPonerEntrada(0,0,0.5);
entornoPonerSalida(9,9);
entornoMostrarMensaje("AAA");
entornoMostrarMensaje("<0,6>");
entornoMostrarMensaje("<6,4>");
entornoMostrarMensaje("<0,2>");
entornoMostrarMensaje("<0,6>");
entornoMostrarMensaje("OBSTACULOS");
entornoMostrarMensaje("<0,6>");
entornoMostrarMensaje("BBB");
entornoPonerEntrada(6,5,0.5);
entornoPonerSalida(2,0);
entornoPonerSalida(6,0);
entornoMostrarMensaje("OBSTACULOS");
entornoMostrarMensaje("<0,2>");
entornoPonerObstaculo(2,0);
entornoMostrarMensaje("<0,6>");
entornoMostrarMensaje("OBSTACULOS");
entornoMostrarMensaje("<0,6>");
entornoPonerObstaculo(0,0);
entornoPonerObstaculo(1,0);
entornoPonerEntrada(6,5,0.4);
entornoPonerSalida(6,0);
entornoPonerEntrada(6,5,0.4);
entornoPonerSalida(6,0);
entornoMostrarMensaje("Soy Ejemplo 0");
entornoPonerFigura(6,4,0.4);
entornoPonerFigura(6,3,0.4);
entornoPonerFigura(6,2,0.4);
entornoPonerFigura(6,1,0.4);
entornoPonerFigura(5,1,0.4);
entornoPonerFigura(4,1,0.4);
entornoPonerFigura(3,1,0.4);
entornoPonerFigura(3,2,0.4);
entornoPonerFigura(3,3,0.4);
entornoPonerFigura(2,3,0.4);
entornoPonerFigura(1,3,0.4);
entornoPonerFigura(1,2,0.4);
entornoPonerFigura(1,1,0.4);
entornoPonerChoque(1,0);
entornoMostrarMensaje ("  ¡ Mala suerte !    ");
entornoPonerEntrada(6,5,0.4);
entornoPonerSalida(6,0);
entornoMostrarMensaje("Soy Ejemplo 1");
entornoPonerFigura(6,4,0.4);
entornoPonerFigura(6,3,0.4);
entornoPonerFigura(6,2,0.4);
entornoPonerFigura(6,1,0.4);
entornoPonerFigura(5,1,0.4);
entornoPonerFigura(4,1,0.4);
entornoPonerFigura(3,1,0.4);
entornoPonerFigura(3,2,0.4);
entornoPonerFigura(3,3,0.4);
entornoPonerFigura(2,3,0.4);
entornoPonerFigura(1,3,0.4);
entornoPonerFigura(1,2,0.4);
entornoPonerFigura(1,1,0.4);
entornoMostrarMensaje ("  ¡ Mala suerte !    ");
entornoPonerEntrada(6,5,0.4);
entornoPonerSalida(6,0);
entornoMostrarMensaje("Soy Ejemplo 2");
entornoPonerFigura(5,5,0.4);
entornoPonerFigura(5,4,0.4);
entornoPonerFigura(5,3,0.4);
entornoPonerFigura(6,3,0.4);
entornoPonerFigura(6,2,0.4);
entornoPonerFigura(6,1,0.4);
entornoPonerFigura(6,0,0.4);
entornoPonerFiguraSalida(6,0);
entornoMostrarMensaje ("  ¡ Lo conseguiste !    ");
entornoMostrarMensaje ("  ¡ Lo conseguiste !    ");
entornoPonerEntrada(6,5,0.4);
entornoPonerSalida(6,0);
entornoMostrarMensaje("Soy Ejemplo 3");
entornoPonerFigura(6,4,0.4);
entornoPonerFigura(6,3,0.4);
entornoPonerFigura(6,2,0.4);
entornoPonerFigura(6,1,0.4);
entornoPonerFigura(6,0,0.4);
entornoPonerFiguraSalida(6,0);
entornoMostrarMensaje ("  ¡ Lo conseguiste !    ");
entornoMostrarMensaje ("  ¡ Lo conseguiste !    ");
return 0;
}
