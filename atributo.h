#ifndef ATRIBUTO_H
#define ATRIBUTO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define CABECERA_POSICION_PRINCIPAL 0L
#define NOMBRE_ATRIBUTO 50
#define SIN_DIRECCION -1L

typedef enum tipoAtributo
{
    CARACTER,
    ENTERO,
    CADENA
} TipoAtributo;

typedef struct atributo
{
    TipoAtributo tipo;
    char nombre[NOMBRE_ATRIBUTO];
    int Largo;
    long ptrAtributo;
    long direccionArchivo;
} TAtributo;

#endif