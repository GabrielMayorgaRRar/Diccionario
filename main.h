#ifndef MAIN_H
#define MAIN_H
#define MAX_LINE 50

#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"

typedef enum opciones
{
    SIN_SELECCION,
    NUEVO_DICCIONARIO,
    ABRIR_DICCIONARIO,
    CERRAR_PROGRAMA
} OpcionMenu;

void mostrar_menu(void);
short entrada_de_usuario(void);
void procesar_opcion_seleccionada(OpcionMenu opcionSeleccionada);
void mostrar_submenu(void);
void creaArchivo(char nomArch[MAX_LINE]);
//Como se va a añadir ".pasame" ocupo modificarlo
int Abrir_Diccionario(char *nom_arch);

#endif