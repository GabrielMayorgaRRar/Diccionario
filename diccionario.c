#include "diccionario.h"
#include "entidad.h"

void operar_diccionario(OpcionSubmenu opcionSeleccionada, const char *nombreDiccionario)
{
    switch (opcionSeleccionada)
    {
    case IMPRIMIR_DICCIONARIO:

        break;
    case NUEVA_ENTIDAD:

        break;
    case ELIMINAR_ENTIDAD:

        break;
    case MODIFICAR_ENTIDAD:

        break;
    case NUEVO_ATRIBUTO:

        break;
    case ELIMINAR_ATRIBUTO:

        break;
    case MODIFICAR_ATRIBUTO:

        break;
    case REGRESAR:

        break;
    default:
        system("clear");
        printf("\n\nOPCION NO VALIDA\nPOR FAVOR ELIJA UNA OPCION VALIDA\n\n");
        break;
    }
}
