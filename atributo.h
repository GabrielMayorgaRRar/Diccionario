#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "entidad.h"

#define CABECERA_POSICION_PRINCIPAL 0L
#define NOMBRE_ATRIBUTO 50
#define SIN_DIRECCION -1L
#define MAX_LINE 50

typedef enum tipoAtributo
{
    SIN_SELECCIONS,
    CARACTER,
    ENTERO,
    CADENA,
    EXTRA
} TipoAtributo;

typedef struct atributo
{
    TipoAtributo Tipo_de_Atributo;
    char nombre[NOMBRE_ATRIBUTO];
    int Tam;
    long ptrAtributo;
    long ptrEntidad;
    long direccionArchivo;
} TAtributo;

void Capturar_Atributo(TAtributo *Atributo_Temporal);
void Agregar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], TAtributo Atributo_Temporal);
void Capturar_Tipo_Dato(int *tipo, int *tam);
void Menu_Tipo_Datos(void);

#endif