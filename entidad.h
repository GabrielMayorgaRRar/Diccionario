#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atributo.h"

#define CABECERA_POSICION_PRINCIPAL 0L
#define NOMBRE_ENTIDADS 50
#define SIN_DIRECCION -1L
#define MAX_LINE 50

typedef struct datoEntidad
{
    char nombre[NOMBRE_ENTIDADS];
    long ptrEntidad;
    long ptrAtributo;
    long direccionArchivo;
} TEntidad;

void Capturar_Nombre_Entidad(TEntidad *Entidad_Temporal);
void Crear_Nueva_Entidad(char nom_arch[MAX_LINE], TEntidad Entidad_Temporal);
TEntidad Eliminar_Entidad(char nom_Diccionario[MAX_LINE], char nom_Entidad[MAX_LINE]);
void modificar_Entidad(char nom_Archivo[MAX_LINE], char nom_Entidad[MAX_LINE]);

#endif
