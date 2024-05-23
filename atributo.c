#include "atributo.h"

void Capturar_Atributo(TAtributo *Atributo_Temporal)
{
    int aux = 0, naux = 0;
    int auxtipo, auxtam, auxclave;
    printf("INTRODUZCA EL NOMBRE QUE LE DESEE ASIGANAR AL ATRIBUTO: \n");
    scanf(" %[^\n]", Atributo_Temporal->nombre);
    Atributo_Temporal->Tipo_de_Atributo = 0;
    printf("INTRODUZCA EL TIPO DE DATO: \n");
    captura_tipo(&auxtipo, &auxtam);
    Atributo_Temporal->Tipo_de_Atributo = auxtipo;
    Atributo_Temporal->Tam = auxtam;
    Atributo_Temporal->ptrAtributo = -1;
    Atributo_Temporal->direccionArchivo = -1;
}

void Agregar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], TAtributo Atributo_Temporal)
{
    FILE *arch;
    TEntidad Entidad_Temporal;
    TAtributo Atributo_Actual;
    long pos;
    int enc = 0;
    arch = fopen(nom_Diccionario, "rb+");
    if (arch)
    {
        fread(&pos, sizeof(long), 1, arch);
        if (pos != -1)
        {
            while (pos != -1 && !enc)
            {
                fseek(arch, pos, SEEK_SET);
                fread(&Entidad_Temporal, sizeof(TEntidad), 1, arch);
                if (strcmp(nombre_Entidad, Entidad_Temporal.nombre) == 0)
                {
                    enc = 1;
                }
                pos = Entidad_Temporal.ptrEntidad;
            }
            if (enc)
            {
                fseek(arch, 0, SEEK_END);
                Atributo_Temporal.direccionArchivo = ftell(arch);
                Atributo_Temporal.ptrEntidad = Entidad_Temporal.ptrEntidad;
                if (Entidad_Temporal.ptrAtributo == -1)
                {
                    Entidad_Temporal.ptrAtributo = Atributo_Temporal.direccionArchivo;
                    fseek(arch, Entidad_Temporal.direccionArchivo, SEEK_SET);
                    fwrite(&Entidad_Temporal, sizeof(TEntidad), 1, arch);
                }
                else
                {
                    pos = Entidad_Temporal.ptrAtributo;
                    while (pos != -1)
                    {
                        fseek(arch, pos, SEEK_SET);
                        fread(&Atributo_Actual, sizeof(TAtributo), 1, arch);
                        pos = Atributo_Actual.ptrAtributo;
                    }
                    Atributo_Actual.ptrAtributo = Atributo_Temporal.direccionArchivo;
                    fseek(arch, Atributo_Actual.direccionArchivo, SEEK_SET);
                    fwrite(&Atributo_Actual, sizeof(TAtributo), 1, arch);
                }
                fseek(arch, Atributo_Temporal.direccionArchivo, SEEK_SET);
                fwrite(&Atributo_Temporal, sizeof(TAtributo), 1, arch);
            }
            else
            {
                printf("\n-- LA ENTIDAD NO EXISTE, ME HICISTE BUSCAR EN VANO πππ --\n\n");
            }
        }
        else
        {
            printf("\n-- EL DICCIONARIO ESTA VACIO --\n\n");
        }
        fclose(arch);
    }
    else
    {
        printf("\n");
        printf("-- NO SE ENCONTRO EL DICCIONARIO --\n\n");
    }
}

void captura_tipo(int *tipo, int *tam)
{
    short opcionActual = SIN_SELECCION, aux = 0;
    while (opcionActual < CARACTER || opcionActual > EXTRA)
    {
        Menu_Tipo_Datos();
        printf("INTRODUZCA LA OPERACION QUE DESEA HACER: ");
        scanf("%hi", &opcionActual);
        switch (opcionActual)
        {
        case CARACTER:
            *tipo = CARACTER;
            *tam = sizeof(char);
            break;
        case ENTERO:
            *tipo = ENTERO;
            *tam = sizeof(int);
            break;
        case CADENA:
            printf("INTRODUZCA EL NUMERO DE CARACTERES: \n");
            scanf("%d", &aux);
            *tipo = CADENA;
            *tam = aux * sizeof(char);
            break;
        default:
            system("clear");
            printf("\n\nOPCION NO VALIDA\nPOR FAVOR ELIJA UNA OPCION VALIDA\n\n");
            break;
        }
    }
}

void Menu_Tipo_Datos(void)
{
    puts("----------DATOS DISPONIBLES----------");
    printf("(%i) CARACTER\n", CARACTER);
    printf("(%i) ENTERO\n", ENTERO);
    printf("(%i) CADENA\n", CADENA);
}