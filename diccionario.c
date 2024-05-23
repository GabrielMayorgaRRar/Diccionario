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
    Imprimir_Diccionario(nombreDiccionario);
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

void Imprimir_Diccionario(char *nombreDiccionario)
{
  FILE *arch;
  long pos;
  TEntidad Entidad_Actual;
  TAtributo Atributo_Actual;
  arch = fopen(nombreDiccionario, "rb");
  if (arch)
  {
    fread(&pos, sizeof(long), 1, arch);
    if (pos == -1)
    {
      printf("\n-- EL DICCIONARIO ESTA VACIO --\n\n");
      fclose(arch);
      return;
    }
    while (pos != -1)
    {
      fseek(arch, pos, SEEK_SET);
      fread(&Entidad_Actual, sizeof(TEntidad), 1, arch);
      Imprimir_Entidad_Actual(Entidad_Actual);
      pos = Entidad_Actual.ptrAtributo;
      while (pos != -1)
      {
        fseek(arch, pos, SEEK_SET);
        fread(&Atributo_Actual, sizeof(TAtributo), 1, arch);
        Imprimir_Atributo_Actual(Atributo_Actual);
        pos = Atributo_Actual.ptrAtributo;
      }
      pos = Entidad_Actual.ptrEntidad;
    }
    fclose(arch);
  }
}

void Imprimir_Entidad_Actual(TEntidad Entidad_Actual)
{
  printf("\n-|DATOS DE LA ENTIDAD|-\n");
  printf("-NOMBRE DE LA ENTIDAD: %s\n", Entidad_Actual.nombre);
  printf("-PTRENTIDAD: %ld\n", Entidad_Actual.ptrEntidad);
  printf("-PTRATRIBUTO: %ld\n", Entidad_Actual.ptrAtributo);
  printf("DIRECCION DEL DICCIONARIO: %ld\n", Entidad_Actual.direccionArchivo);
}

void Imprimir_Atributo_Actual(TAtributo Atributo_Actual)
{
  printf("\n-|DATOS DEL ATRIBUTO|-\n");
  printf("NOMBRE DEL ATRIBUTO: %s\n", Atributo_Actual.nombre);
  printf("TIPOD DE DATO: %d\n", Atributo_Actual.Tipo_de_Atributo);
  printf("TAMAÑO: %d\n", Atributo_Actual.Tam);
  printf("PTRATRIBUTO: %ld\n", Atributo_Actual.ptrAtributo);
  printf("DIRECCION DEL DICCIONARIO: %ld\n", Atributo_Actual.direccionArchivo);
}