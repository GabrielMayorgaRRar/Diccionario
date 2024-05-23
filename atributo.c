#include "atributo.h"

void Capturar_Atributo(TAtributo *Atributo_Temporal)
{
    int aux = 0, naux = 0;
    int auxtipo, auxtam, auxclave;
    printf("INTRODUZCA EL NOMBRE QUE LE DESEE ASIGANAR AL ATRIBUTO: \n");
    scanf(" %[^\n]", Atributo_Temporal->nombre);
    Atributo_Temporal->Tipo_de_Atributo = 0;
    printf("INTRODUZCA EL TIPO DE DATO: \n");
    Capturar_Tipo_Dato(&auxtipo, &auxtam);
    Atributo_Temporal->Tipo_de_Atributo = auxtipo;
    Atributo_Temporal->Tam = auxtam;
    Atributo_Temporal->ptrAtributo = -1;
    Atributo_Temporal->direccionArchivo = -1;
}

void Capturar_Tipo_Dato(int *tipo, int *tam)
{
    short opcionActual = SIN_SELECCIONS, aux = 0;
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
            scanf("%hd", &aux);
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

                // Verificar si el atributo ya existe en la entidad
                pos = Entidad_Temporal.ptrAtributo;
                while (pos != -1)
                {
                    fseek(arch, pos, SEEK_SET);
                    fread(&Atributo_Actual, sizeof(TAtributo), 1, arch);
                    if (strcmp(Atributo_Temporal.nombre, Atributo_Actual.nombre) == 0)
                    {
                        printf("\n-- EL ATRIBUTO YA EXISTE EN LA ENTIDAD --\n\n");
                        fclose(arch);
                        return;
                    }
                    pos = Atributo_Actual.ptrAtributo;
                }

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
        printf("\n-- NO SE ENCONTRO EL DICCIONARIO --\n\n");
    }
}

TAtributo Eliminar_Atributo(char nom_Diccionario[MAX_LINE], char nombre_Entidad[MAX_LINE], char nombre_Atributo[MAX_LINE])
{
    FILE *arch;
    TEntidad Entidad_Actual;
    TAtributo Atributo_Actual, Atributo_Anterior, Atributo_Resultante;
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
                fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                if (strcmp(nombre_Entidad, Entidad_Actual.nombre) == 0)
                {
                    enc = 1;
                }
                pos = Entidad_Actual.ptrEntidad;
            }
            if (enc)
            {
                if (Entidad_Actual.ptrAtributo != -1)
                {
                    pos = Entidad_Actual.ptrAtributo;
                    fseek(arch, Entidad_Actual.ptrAtributo, SEEK_SET);
                    fread(&Entidad_Actual, sizeof(TAtributo), 1, arch);
                    if (strcmp(nombre_Atributo, Atributo_Actual.nombre) == 0)
                    {
                        Atributo_Resultante = Atributo_Actual;
                        Entidad_Actual.ptrAtributo = Atributo_Actual.ptrAtributo;
                        fseek(arch, Entidad_Actual.direccionArchivo, SEEK_SET);
                        fwrite(&Entidad_Actual, sizeof(TEntidad), 1, arch);
                    }
                    else
                    {
                        while (Atributo_Actual.ptrAtributo != -1 &&
                               strcmp(nombre_Atributo, Atributo_Actual.nombre) != 0)
                        {
                            Atributo_Anterior = Atributo_Actual;
                            fseek(arch, Atributo_Actual.ptrAtributo, SEEK_SET);
                            fread(&Atributo_Actual, sizeof(TAtributo), 1, arch);
                        }
                        if (strcmp(nombre_Atributo, Atributo_Actual.nombre) == 0)
                        {
                            Atributo_Resultante = Atributo_Actual;
                            Atributo_Anterior.ptrAtributo = Atributo_Actual.ptrAtributo;
                            fseek(arch, Atributo_Anterior.direccionArchivo, SEEK_SET);
                            fwrite(&Atributo_Anterior, sizeof(TAtributo), 1, arch);
                        }
                        else
                        {
                            printf("\nEL ATRIBUTO NO EXISTE, ME HICISTE BUSCAR EN VANO πππ \n");
                        }
                    }
                }
                else
                {
                    printf("\n-- LA ENTIDAD NO TIENE ATRIBUTOS, ME HICISTE BUSCAR EN VANO πππ  --\n\n");
                }
            }
            else
            {
                printf("\n-- LA ENTIDAD NO EXISTE, ME HICISTE BUSCAR EN VANO πππ  --\n\n");
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
        printf("\n-- NO SE ENCONTRO EL DICCIONARIO --\n\n");
    }
    return Atributo_Resultante;
}

void Imprimir_Atributo_Actual(TAtributo Atributo_Actual)
{
    printf("\n-|DATOS DEL ATRIBUTO|-\n");
    printf("NOMBRE DEL ATRIBUTO: %s\n", Atributo_Actual.nombre);
    switch (Atributo_Actual.Tipo_de_Atributo)
    {
    case ENTERO:
        printf("TIPO DE DATO: %d (ENTERO)\n", Atributo_Actual.Tipo_de_Atributo);
        break;
    case CARACTER:
        printf("TIPO DE DATO: %d (CARACTER)\n", Atributo_Actual.Tipo_de_Atributo);
        break;
    case CADENA:
        printf("TIPO DE DATO: %d (CADENA)\n", Atributo_Actual.Tipo_de_Atributo);
        break;
    default:
        break;
    }

    printf("TAMAÑO: %d\n", Atributo_Actual.Tam);
    printf("PTRATRIBUTO: %ld\n", Atributo_Actual.ptrAtributo);
    printf("DIRECCION DEL DICCIONARIO: %ld\n", Atributo_Actual.direccionArchivo);
}