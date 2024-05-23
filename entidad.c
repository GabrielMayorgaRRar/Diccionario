#include "entidad.h"

void Capturar_Nombre_Entidad(TEntidad *Entidad_Temporal)
{
    printf("INTRODUZCA EL NOMBRE QUE LE DESEE ASIGANAR A LA ENTIDAD: \n");
    scanf(" %[^\n]", Entidad_Temporal->nombre);
    Entidad_Temporal->ptrEntidad = -1;
    Entidad_Temporal->ptrAtributo = -1;
    Entidad_Temporal->direccionArchivo = -1;
}

void Crear_Nueva_Entidad(char nom_arch[MAX_LINE], TEntidad Entidad_Temporal)
{
    FILE *arch;
    long cab;
    TEntidad Entidad_Actual, Entidad_Anterior;

    arch = fopen(nom_arch, "rb+");
    if (arch)
    {
        fread(&cab, sizeof(long), 1, arch);
        fseek(arch, 0, SEEK_END);
        Entidad_Temporal.direccionArchivo = ftell(arch);

        if (cab == -1)
        {
            fseek(arch, 0, SEEK_SET);
            cab = Entidad_Temporal.direccionArchivo;
            fwrite(&cab, sizeof(long), 1, arch);
        }
        else
        {
            fseek(arch, cab, SEEK_SET);
            fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);

            if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) == 0)
            {
                printf("\n-- LA ENTIDAD '%s' YA EXISTE. NO SE PUEDE AGREGAR. --\n", Entidad_Temporal.nombre);
                fclose(arch);
                return;
            }

            if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) < 0)
            {
                Entidad_Temporal.ptrEntidad = cab;
                fseek(arch, 0, SEEK_SET);
                cab = Entidad_Temporal.direccionArchivo;
                fwrite(&cab, sizeof(long), 1, arch);
            }
            else
            {
                while (Entidad_Actual.ptrEntidad != -1 && strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) > 0)
                {
                    Entidad_Anterior = Entidad_Actual;
                    fseek(arch, Entidad_Anterior.ptrEntidad, SEEK_SET);
                    fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                }
                if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) == 0)
                {
                    printf("\n-- LA ENTIDAD '%s' YA EXISTE. NO SE PUEDE AGREGAR. --\n", Entidad_Temporal.nombre);
                    fclose(arch);
                    return;
                }

                if (strcmp(Entidad_Temporal.nombre, Entidad_Actual.nombre) < 0)
                {
                    Entidad_Anterior.ptrEntidad = Entidad_Temporal.direccionArchivo;
                    Entidad_Temporal.ptrEntidad = Entidad_Actual.direccionArchivo;
                    fseek(arch, Entidad_Anterior.direccionArchivo, SEEK_SET);
                    fwrite(&Entidad_Anterior, sizeof(TEntidad), 1, arch);
                }
                else
                {
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
    }
    else
    {
        printf("-- NO SE ENCONTRO EL DICCIONARIO --\n");
    }
}

TEntidad Eliminar_Entidad(char nom_Diccionario[MAX_LINE], char nom_Entidad[MAX_LINE])
{
    FILE *arch;
    long cab;
    TEntidad Entidad_Actual, Entidad_Anterior, Entidad_Resultante;
    int entidad_encontrada = 0;

    arch = fopen(nom_Diccionario, "rb+");
    if (arch)
    {
        fread(&cab, sizeof(long), 1, arch);
        if (cab != -1)
        {
            fseek(arch, cab, SEEK_SET);
            fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
            if (strcmp(nom_Entidad, Entidad_Actual.nombre) == 0)
            {
                Entidad_Resultante = Entidad_Actual;
                cab = Entidad_Actual.ptrEntidad;
                fseek(arch, 0, SEEK_SET);
                fwrite(&cab, sizeof(long), 1, arch);
                entidad_encontrada = 1;
            }
            else
            {
                while (Entidad_Actual.ptrEntidad != -1 && strcmp(nom_Entidad, Entidad_Actual.nombre) != 0)
                {
                    Entidad_Anterior = Entidad_Actual;
                    fseek(arch, Entidad_Anterior.ptrEntidad, SEEK_SET);
                    fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                }
                if (strcmp(nom_Entidad, Entidad_Actual.nombre) == 0)
                {
                    Entidad_Resultante = Entidad_Actual;
                    Entidad_Anterior.ptrEntidad = Entidad_Actual.ptrEntidad;
                    fseek(arch, Entidad_Anterior.direccionArchivo, SEEK_SET);
                    fwrite(&Entidad_Anterior, sizeof(TEntidad), 1, arch);
                    entidad_encontrada = 1;
                }
            }
            if (entidad_encontrada)
            {
                printf("\n-- LA ENTIDAD '%s' HA SIDO ELIMINADA CORRECTAMENTE. --\n", nom_Entidad);
            }
            else
            {
                printf("\n-- LA ENTIDAD NO EXISTE, ME HICISTE BUSCAR EN VANO πππ --\n");
            }
        }
        else
        {
            printf("\n-- EL DICCIONARIO ESTA VACIO --\n");
        }
        fclose(arch);
    }
    else
    {
        printf("\n-- NO SE ENCONTRO EL DICCIONARIO --\n");
    }
    return Entidad_Resultante;
}

void modificar_Entidad(char nom_Archivo[MAX_LINE], char nom_Entidad[MAX_LINE])
{
    FILE *arch;
    TEntidad Entidad_Auxiliar, Entidad_Modificada, Entidad_Temporal;

    arch = fopen(nom_Archivo, "rb+");
    if (arch)
    {
        long cab;
        fread(&cab, sizeof(long), 1, arch);

        int encontrada = 0;
        while (cab != -1)
        {
            fseek(arch, cab, SEEK_SET);
            fread(&Entidad_Auxiliar, sizeof(TEntidad), 1, arch);

            if (strcmp(Entidad_Auxiliar.nombre, nom_Entidad) == 0)
            {
                long pos_modificar = ftell(arch) - sizeof(TEntidad);
                fseek(arch, pos_modificar, SEEK_SET);
                fread(&Entidad_Temporal, sizeof(TEntidad), 1, arch);

                printf("\nINTRODUCE EL NUEVO NOMBRE PARA LA ENTIDAD : ");
                scanf(" %[^\n]", Entidad_Modificada.nombre);

                Entidad_Modificada.ptrEntidad = Entidad_Temporal.ptrEntidad;
                Entidad_Modificada.ptrAtributo = Entidad_Temporal.ptrAtributo;
                Entidad_Modificada.direccionArchivo = Entidad_Temporal.direccionArchivo;

                fseek(arch, pos_modificar, SEEK_SET);
                fwrite(&Entidad_Modificada, sizeof(TEntidad), 1, arch);

                encontrada = 1;
                printf("\nLA ENTIDAD '%s' SE MODIFICO CORRECTAMENTE.\n", nom_Entidad);
                break;
            }
            cab = Entidad_Auxiliar.ptrEntidad;
        }

        if (!encontrada)
        {
            printf("\nLA ENTIDAD '%s' NO FUE ENCONTRADA EN EL ARCHIVO.\n", nom_Entidad);
        }

        fclose(arch);
    }
    else
    {
        printf("\n-- NO SE ENCONTRO EL DICCIONARIO --\n");
    }
}