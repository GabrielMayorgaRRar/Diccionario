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
    puts("----------Diccionario de Datos----------");
    printf("%i) Crear un nuevo diccionario\n", NUEVO_DICCIONARIO);
    printf("%i) Abrir un diccionario existente\n", ABRIR_DICCIONARIO);
    printf("%i) Salir\n", CERRAR_PROGRAMA);
}

short entrada_de_usuario(void)
{
    short opcion_seleccionada;
    printf("Por favor selecciona una opcion: ");
    scanf("%hi", &opcion_seleccionada);
    return opcion_seleccionada;
}

void procesar_opcion_seleccionada(OpcionMenu opcionSeleccionada)
{
    char nombreDiccionario[MAX_LINE];
    short operacionRealizar = SIN_SELECCION;

    switch (opcionSeleccionada)
    {
    case NUEVO_DICCIONARIO:
        creaArchivo(nombreDiccionario);

        do
        {
            mostrar_submenu();
            operacionRealizar = entrada_de_usuario();
            system("clear");
            operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
        } while (operacionRealizar != REGRESAR);

        break;
    case ABRIR_DICCIONARIO:
        printf("Introduce el nombre del diccionario: ");
        scanf(" %[^\n]", nombreDiccionario);
        do
        {
            mostrar_submenu();
            operacionRealizar = entrada_de_usuario();
            system("clear");
            operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
        } while (operacionRealizar != REGRESAR);
        break;
    case CERRAR_PROGRAMA:
        puts("Saliendo...");
        break;
    default:
        puts("Opcion no valida, intenta de nuevo");
        break;
    }
}

void mostrar_submenu(void)
{
    puts("----------Operacion a realizar----------");
    printf("%i) Imprimir diccionario de datos\n", IMPRIMIR_DICCIONARIO);
    printf("%i) Nueva entidad\n", NUEVA_ENTIDAD);
    printf("%i) Eliminar entidad\n", ELIMINAR_ENTIDAD);
    printf("%i) Modificar entidad\n", MODIFICAR_ENTIDAD);
    printf("%i) Nuevo atributo\n", NUEVO_ATRIBUTO);
    printf("%i) Eliminar atributo\n", ELIMINAR_ATRIBUTO);
    printf("%i) Modificar atributo\n", MODIFICAR_ATRIBUTO);
    printf("%i) Regresar\n", REGRESAR);
}

void creaArchivo(char nomArch[MAX_LINE])
{
    long cab = -1L;
    FILE *arch;
    printf("Cual es el nombre del archivo: ");
    scanf(" %[^\n]", nomArch);
    strcat(nomArch, ".paseme");
    arch = fopen(nomArch, "wb+");
    if (arch)
    {
        fwrite(&cab, sizeof(long), 1, arch);
        fclose(arch);
    }
}