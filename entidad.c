#include "entidad.h"

void Capturar_Nombre_Entidad(TEntidad *Entidad_Temporal)
{
    printf("INTRODUZCA EL NOMBRE QUE LE DESEE ASIGANAR A LA ENTIDAD: \n");
    scanf(" %[^\n]", Entidad_Temporal->nombre);
    Entidad_Temporal->ptrEntidad = -1;
    Entidad_Temporal->ptrAtributo = -1;
    Entidad_Temporal->direccionArchivo = -1;
}

void Crear_Nueva_Entidad(char nom_arch[MAX_LINE], TEntidad Entidad_Temporal) {
    FILE *arch;
    long cab;
    TEntidad Entidad_Actual, Entidad_Anterior;

    arch = fopen(nom_arch, "rb+");
    if (arch) {
        fread(&cab, sizeof(long), 1, arch);
        fseek(arch, 0, SEEK_END);
        Entidad_Temporal.direccionArchivo = ftell(arch);

        if (cab == -1) {
            fseek(arch, 0, SEEK_SET);
            cab = Entidad_Temporal.direccionArchivo;
            fwrite(&cab, sizeof(long), 1, arch);
        } else {
            fseek(arch, cab, SEEK_SET);
            fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);

            if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) == 0) {
                printf("\n-- LA ENTIDAD '%s' YA EXISTE. NO SE PUEDE AGREGAR. --\n", Entidad_Temporal.nombre);
                fclose(arch);
                return;
            }

            if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) < 0) {
                Entidad_Temporal.ptrEntidad = cab;
                fseek(arch, 0, SEEK_SET);
                cab = Entidad_Temporal.direccionArchivo;
                fwrite(&cab, sizeof(long), 1, arch);
            } else {
                while (Entidad_Actual.ptrEntidad != -1 && strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) > 0) {
                    Entidad_Anterior = Entidad_Actual;
                    fseek(arch, Entidad_Anterior.ptrEntidad, SEEK_SET);
                    fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                }
                if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) == 0) {
                    printf("\n-- LA ENTIDAD '%s' YA EXISTE. NO SE PUEDE AGREGAR. --\n", Entidad_Temporal.nombre);
                    fclose(arch);
                    return;
                }

                if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) < 0) {
                    Entidad_Anterior.ptrEntidad = Entidad_Temporal.direccionArchivo;
                    Entidad_Temporal.ptrEntidad = Entidad_Actual.direccionArchivo;
                    fseek(arch, Entidad_Anterior.direccionArchivo, SEEK_SET);
                    fwrite(&Entidad_Anterior, sizeof(TEntidad), 1, arch);
                } else {
                    Entidad_Actual.ptrEntidad = Entidad_Temporal.direccionArchivo;
                    fseek(arch, Entidad_Actual.direccionArchivo, SEEK_SET);
                    fwrite(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                }
            }
        }

        fseek(arch, Entidad_Temporal.direccionArchivo, SEEK_SET);
        fwrite(&Entidad_Temporal, sizeof(TEntidad), 1, arch);
        printf("\n-- LA ENTIDAD '%s' HA SIDO AGREGADA CORRECTAMENTE. -- \n", Entidad_Temporal.nombre);
        fclose(arch);
    } else {
        printf("-- NO SE ENCONTRO EL DICCIONARIO --\n");
    }
}

TEntidad Eliminar_Entidad(char nom_Diccionario[MAX_LINE], char nom_Entidad[MAX_LINE]) {
    FILE *arch;
    long cab;
    TEntidad e_act, e_ant, rest;
    int entidad_encontrada = 0;

    arch = fopen(nom_Diccionario, "rb+");
    if (arch) {
        fread(&cab, sizeof(long), 1, arch);
        if (cab != -1) {
            fseek(arch, cab, SEEK_SET);
            fread(&e_act, sizeof(TEntidad), 1, arch);
            if (strcmp(nom_Entidad, e_act.nombre) == 0) {
                rest = e_act;
                cab = e_act.ptrEntidad;
                fseek(arch, 0, SEEK_SET);
                fwrite(&cab, sizeof(long), 1, arch);
                entidad_encontrada = 1;
            } else {
                while (e_act.ptrEntidad != -1 && strcmp(nom_Entidad, e_act.nombre) != 0) {
                    e_ant = e_act;
                    fseek(arch, e_ant.ptrEntidad, SEEK_SET);
                    fread(&e_act, sizeof(TEntidad), 1, arch);
                }
                if (strcmp(nom_Entidad, e_act.nombre) == 0) {
                    rest = e_act;
                    e_ant.ptrEntidad = e_act.ptrEntidad;
                    fseek(arch, e_ant.direccionArchivo, SEEK_SET);
                    fwrite(&e_ant, sizeof(TEntidad), 1, arch);
                    entidad_encontrada = 1;
                }
            }
            if (entidad_encontrada) {
                printf("\n-- LA ENTIDAD '%s' HA SIDO ELIMINADA CORRECTAMENTE. --\n", nom_Entidad);
            } else {
                printf("\n-- LA ENTIDAD NO EXISTE, ME HICISTE BUSCAR EN VANO πππ --\n");
            }
        } else {
            printf("\n-- EL DICCIONARIO ESTA VACIO --\n");
        }
        fclose(arch);
    } else {
        printf("-- NO SE ENCONTRO EL DICCIONARIO --\n");
    }
    return rest;
}

void modificar_Entidad(char nom_Archivo[MAX_LINE], char nom_Entidad[MAX_LINE]) {
    TEntidad Entidad_Auxiliar, Entidad_Modificada;
    Entidad_Auxiliar = Eliminar_Entidad(nom_Archivo, nom_Entidad);
    
    if (strcmp(Entidad_Auxiliar.nombre, nom_Entidad) == 0) {
        printf("-- INGRESE LOS NUEVOS DATOS DE LA ENTIDAD --\n\n");
        printf("Ingrese el nuevo nombre de la entidad: ");
        scanf("%s", Entidad_Modificada.nombre);
        Entidad_Modificada.ptrEntidad = -1; 
        Entidad_Modificada.direccionArchivo = -1;
        Crear_Nueva_Entidad(nom_Archivo, Entidad_Modificada);

        printf("-- LA ENTIDAD '%s' HA SIDO MODIFICADA CORRECTAMENTE. --\n", Entidad_Modificada.nombre);
    } else {
        printf("-- LA ENTIDAD '%s' NO FUE ENCONTRADA PARA MODIFICAR. --\n", nom_Entidad);
    }
}
