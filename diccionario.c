#include "diccionario.h"
#include "entidad.h"

void operar_diccionario(OpcionSubmenu opcionSeleccionada, char *nombreDiccionario)
{
    TEntidad Entidad_Temporal;
    char Nombre[MAX_LINE];
    switch (opcionSeleccionada)
    {
    case IMPRIMIR_DICCIONARIO:
        printf("\n-- HAS SELECCIONADO 'IMPRIMIR EL DICCIONARIO DE DATOS' --\n\n");

        break;
    case NUEVA_ENTIDAD:
        printf("\n-- HAS SELECCIONADO 'CREAR UNA NUEVA ENTIDA' --\n\n");
        Capturar_Nombre_Entidad(&Entidad_Temporal);
        Crear_Nueva_Entidad(nombreDiccionario, Entidad_Temporal);
        break;
    case ELIMINAR_ENTIDAD:
        printf("\n-- HAS SELECCIONADO 'ELIMINAR UNA ENTIDAD' --\n\n");
        printf("INTRODUZCA EL NOMBRE DE LA ENTIDAD QUE DESEE ELIMINAR: \n");
        scanf(" %[^\n]", Nombre);
        Entidad_Temporal = Eliminar_Entidad(nombreDiccionario, Nombre);
        break;
    case MODIFICAR_ENTIDAD:
        printf("\n-- HAS SELECCIONADO 'MODIFICAR UNA ENTIDAD EXISTENTE' --\n\n");
        printf("INTRODUZCA EL NOMBRE DE LA ENTIDAD QUE DESEE MODIFICAR: \n");
        scanf(" %[^\n]", Nombre);
        modificar_Entidad(nombreDiccionario, Nombre);
        break;
    case NUEVO_ATRIBUTO:
        printf("\n-- HAS SELECCIONADO 'CREAR UN NUEVO ATRIBUTO' --\n\n");
        break;
    case ELIMINAR_ATRIBUTO:
        printf("\n-- HAS SELECCIONADO 'ELIMINAR UN ATRIBUTO' --\n\n");
        break;
    case MODIFICAR_ATRIBUTO:
        printf("\n-- HAS SELECCIONADO 'MODIFICAR UN ATRIBUTO EXISTENTE' --\n\n");
        break;
    case REGRESAR:
        printf("\nREGRESANDO...\n");
        FILE *archivo = fopen(nombreDiccionario, "rb");
        fclose(archivo);
        break;
    default:
        system("clear");
        printf("\n\nOPCION NO VALIDA\nPOR FAVOR ELIJA UNA OPCION VALIDA\n\n");
        break;
    }
}
