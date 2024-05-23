#include "main.h"

int main(void)
{
    short opcionActual = SIN_SELECCION;
    do
    {
        mostrar_menu();
        opcionActual = entrada_de_usuario();
        system("clear");
        procesar_opcion_seleccionada((OpcionMenu)opcionActual);
    } while (opcionActual != CERRAR_PROGRAMA);
    return EXIT_SUCCESS;
}

void mostrar_menu(void)
{
    puts("----------MENU DICCIONARIO DE DATOS----------");
    printf("(%i) CREAR UN NUEVO DICCIONARIO\n", NUEVO_DICCIONARIO);
    printf("(%i) ABRIR UN DICCIONARIO EXISTENTE\n", ABRIR_DICCIONARIO);
    printf("(%i) SALIR\n", CERRAR_PROGRAMA);
}

short entrada_de_usuario(void)
{
    short opcion_seleccionada;
    printf("INTRODUZCA LA OPERACION QUE DESEA HACER: ");
    scanf("%hi", &opcion_seleccionada);
    return opcion_seleccionada;
}

void procesar_opcion_seleccionada(OpcionMenu opcionSeleccionada)
{
    int Existe_Diccionario;
    char nombreDiccionario[MAX_LINE];
    short operacionRealizar = SIN_SELECCION;

    switch (opcionSeleccionada)
    {
    case NUEVO_DICCIONARIO:
        printf("INTRODUCE EL NOMBRE DEL DICCIONARIO: ");
        scanf(" %[^\n]", nombreDiccionario);
        strcat(nombreDiccionario, ".PASEME");
        Existe_Diccionario = Diccionario_Existir(nombreDiccionario);
        if (Existe_Diccionario == 1)
        {
            printf("\nEL DICCIONARIO YA EXISTE\n");
            printf("\nABRIENDO...\n\n");
        }
        else
        {
            printf("\nCREANDO...\n\n");
            Crear_Diccionario(nombreDiccionario);
        }
        do
        {
            Menu_de_Operaciones();
            operacionRealizar = entrada_de_usuario();
            system("clear");
            operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
        } while (operacionRealizar != REGRESAR);

        break;
    case ABRIR_DICCIONARIO:
        printf("INTRODUCE EL NOMBRE DEL DICCIONARIO: ");
        scanf(" %[^\n]", nombreDiccionario);
        Existe_Diccionario = Abrir_Diccionario(nombreDiccionario);
        if (Existe_Diccionario == 1)
        {
            printf("\nABRIENDO...\n\n");
            do
            {
                Menu_de_Operaciones();
                operacionRealizar = entrada_de_usuario();
                system("clear");
                operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
            } while (operacionRealizar != REGRESAR);
        }
        else
        {
            printf("\nEL DICCIONARIO NO EXSITE\n\n");
        }
        break;
    case CERRAR_PROGRAMA:
        system("clear");
        puts("CERRANDO...");
        break;
    default:
        system("clear");
        printf("\n\nOPCION NO VALIDA\nPOR FAVOR ELIJA UNA OPCION VALIDA\n\n");
        break;
    }
}

void Menu_de_Operaciones(void)
{
    puts("----------OPERACIONES DISPONIBLES----------");
    printf("(%i) IMPRIMIR EL DICCIONARIO DE DATOS\n", IMPRIMIR_DICCIONARIO);
    printf("(%i) CREAR UNA NUEVA ENTIDAD\n", NUEVA_ENTIDAD);
    printf("(%i) ELIMINAR UNA ENTIDAD\n", ELIMINAR_ENTIDAD);
    printf("(%i) MODIFICAR UNA ENTIDAD EXISTENTE\n", MODIFICAR_ENTIDAD);
    printf("(%i) CREAR UN NUEVO ATRIBUTO\n", NUEVO_ATRIBUTO);
    printf("(%i) ELIMINAR UN ATRIBUTO\n", ELIMINAR_ATRIBUTO);
    printf("(%i) MODIFICAR UN ATRIBUTO EXISTENTE\n", MODIFICAR_ATRIBUTO);
    printf("(%i) LIMPIAR PANTALLA\n", LIMPIAR_PANTALLA);
    printf("(%i) CERRAR Y VOLVER\n", REGRESAR);
}

void Crear_Diccionario(char nomArch[MAX_LINE])
{
    long cab = -1L;
    FILE *arch;
    arch = fopen(nomArch, "wb+");
    if (arch)
    {
        fwrite(&cab, sizeof(long), 1, arch);
        fclose(arch);
    }
    else
    {
    }
}

int Abrir_Diccionario(char *nom_arch)
{
    FILE *arch;
    int ban = 0;
    strcat(nom_arch, ".PASEME");
    arch = fopen(nom_arch, "rb");
    if (arch == NULL)
    {
        return ban;
    }
    printf("\nEL DICCIONARIO HA SIDO ABIERTO\n\n");
    ban = 1;
    fclose(arch);
    return ban;
}

int Diccionario_Existir(char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (archivo == NULL)
    {
        return 0;
    }
    else
    {
        fclose(archivo);
        return 1;
    }
}