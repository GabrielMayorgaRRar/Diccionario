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
#define MAX_ATRIBUTOS 1000000
#define A -1

typedef enum tipoAtributo
{
    SIN_SELECCIONS,
    CARACTER,
    ENTERO,
    CADENA,
    EXTRA
} TipoAtributo;

typedef enum modificarAtributo
{
    SIN_SELECCIO,
    NOMBRE,
    TIPO,
    CONTINUAR
} TMAtributo;

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
void Modificar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], char nombre_Atributo[MAX_LINE]);
void Capturar_Tipo_Dato(int *TipoD, int *Tama);
void Menu_Modificar_Atributo(void);
TAtributo Eliminar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], char nombre_Atributo[MAX_LINE]);
void Menu_Tipo_Datos(void);
TAtributo Buscar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], char nombre_Atributo[MAX_LINE]);

#endif

