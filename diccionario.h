#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#define CABECERA_POSICION_PRINCIPAL 0L
#define SIN_DIRECCION -1L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "entidad.h"
#include "atributo.h"
typedef enum
{
    IMPRIMIR_DICCIONARIO = 1,
    NUEVA_ENTIDAD,
    ELIMINAR_ENTIDAD,
    MODIFICAR_ENTIDAD,
    NUEVO_ATRIBUTO,
    ELIMINAR_ATRIBUTO,
    MODIFICAR_ATRIBUTO,
    REGRESAR
} OpcionSubmenu;

void operar_diccionario(OpcionSubmenu opcionSeleccionada, char *nombreDiccionario);
void Imprimir_Diccionario(char *nombreDiccionario);

#endif