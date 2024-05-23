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
    int Existe_Diccionario;
    char nombreDiccionario[MAX_LINE];
    short operacionRealizar = SIN_SELECCION;

    switch (opcionSeleccionada)
    {
    case NUEVO_DICCIONARIO:
        creaArchivo(nombreDiccionario);
        Existe_Diccionario = Abrir_Diccionario(nombreDiccionario);
        if(Existe_Diccionario==1){
            printf("\nEL DICCIONARIO YA EXISTE\n");
            printf("\nABRIENDO...\n\n");
        }
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
        Existe_Diccionario = Abrir_Diccionario(nombreDiccionario);
        if(Existe_Diccionario==1) {
            printf("\nABRIENDO...\n\n");
          do
        {
            mostrar_submenu();
            operacionRealizar = entrada_de_usuario();
            system("clear");
            operar_diccionario((OpcionSubmenu)operacionRealizar, nombreDiccionario);
        } while (operacionRealizar != REGRESAR);
        }
        
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
    puts("----------OPERACIONES DISPONIBLES----------");
    printf("%i) IMPRIMIR DICCIONARIO DE DATOS\n", IMPRIMIR_DICCIONARIO);
    printf("%i) CREAR UNA NUEVA ENTIDAD\n", NUEVA_ENTIDAD);
    printf("%i) ELIMINAR ENTIDAD\n", ELIMINAR_ENTIDAD);
    printf("%i) MODIFICAR UNA ENTIDAD EXISTENTE\n", MODIFICAR_ENTIDAD);
    printf("%i) CREAR UN NUEVO ATRIBUTO\n", NUEVO_ATRIBUTO);
    printf("%i) ELIMINAR UN ATRIBUTO\n", ELIMINAR_ATRIBUTO);
    printf("%i) MODIFICAR UN ATRIBUTO EXISTENTE\n", MODIFICAR_ATRIBUTO);
    printf("%i) CERRAR Y VOLVER\n", REGRESAR);
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

int Abrir_Diccionario(char *nom_arch) {
  FILE *arch;
  int ban = 0;
  strcat(nom_arch, ".paseme");
  arch = fopen(nom_arch, "rb");
  if(arch==NULL) {
    printf("\nEL DICCIONARIO NO EXSITE\n\n");
    return ban;
  }
  printf("\nEL DICCIONARIO HA SIDO ABIERTO\n\n");
  ban = 1;
  fclose(arch);
  return ban;
}