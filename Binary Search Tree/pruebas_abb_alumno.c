#include "abb.h"
#include "testing.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.
/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

#define CANTIDAD_ALEATORIOS 10 //mantener este numero bajo porque si no muere ciclando en borrar aleatorio
#define TEST_VOL 1000


static void prueba_crear_abb_vacio(){
     printf("\t---PRUEBAS ABB VACIO---\n");
     abb_t* abb = abb_crear(NULL,NULL); //aca
     //Creo un abb vacio

     print_test("Prueba abb crear abb vacio", abb);
     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
     print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
     print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
     print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

     abb_destruir(abb);
 }

static void pruebas_abb_iterar_vacio(){
   printf("\t---PRUEBAS ITERAR NULL---\n");
   abb_t* abb=abb_crear(NULL,NULL);
   print_test("Abb vacio",abb_cantidad(abb)==0);
   abb_iter_t*iter=abb_iter_in_crear(abb);
   print_test("Iter con pila vacia",abb_iter_in_al_final(iter));
   print_test("Iter avanzar es false",!abb_iter_in_avanzar(iter));

   print_test("iter actual null",abb_iter_in_ver_actual(iter)==NULL);

   abb_iter_in_destruir(iter);
   abb_destruir(abb);
 }

static void pruebas_abb_guardar(){
  printf("\t---PRUEBAS GUARDAR\n");

  abb_t* abb = abb_crear(strcmp,NULL);

  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";
  char *clave4 = "tero", *valor4 = "chaja";

  print_test("ABB guardar clave 1", abb_guardar(abb,clave1,valor1));
  print_test("cantidad elementos es 1 ",abb_cantidad(abb)==1);
  print_test("obtener clave 1 es valor 1",abb_obtener(abb,clave1)==valor1);
  print_test("pertenece clave 1 true",abb_pertenece(abb,clave1));
  print_test("borrar clave 1 es valor 1",abb_borrar(abb,clave1)==valor1);
  print_test("Cantidad de elementos en arbol es 0",abb_cantidad(abb)==0);

  print_test("ABB guardar clave 2", abb_guardar(abb,clave2,valor2));
  print_test("Cantidad de elementos abb 2",abb_cantidad(abb)==1);
  print_test("obtener clave 2 es clave 2",abb_obtener(abb,clave2)==valor2);
  print_test("pertenece clave 2 true",abb_pertenece(abb,clave2));

  print_test("guardar clave 3",abb_guardar(abb,clave3,valor3));
  print_test("cantidad elementos 2",abb_cantidad(abb)==2);
  print_test("obtener clave 3 es valor 3",abb_obtener(abb,clave3)==valor3);
  print_test("clave 3 pertenece true",abb_pertenece(abb,clave3));

  print_test("guardar clave 4",abb_guardar(abb,clave4,valor4));
  print_test("cantidad elementos 3",abb_cantidad(abb)==3);
  print_test("obtener clave 4 es valor 4",abb_obtener(abb,clave4)==valor4);
  print_test("clave 4 pertenece true",abb_pertenece(abb,clave4));


  abb_destruir(abb);
}

static void pruebas_abb_reemplazar(){
    printf("\t---PRUEBAS REEMPLAZAR---\n");
  abb_t* abb = abb_crear(strcmp,NULL);

  char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
  char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

  print_test("Guardar clave 1",abb_guardar(abb,clave1,valor1a));
  print_test("Obtener clave 1 ok",abb_obtener(abb,clave1)==valor1a);
  print_test("Guardar clave 2",abb_guardar(abb,clave2,valor2a));
  print_test("Obtener clave 2 ok",abb_obtener(abb,clave2)==valor2a);
  print_test("Cantidad de elementos 2",abb_cantidad(abb)==2);

  print_test("Reemplazar clave 1 con otro valor",abb_guardar(abb,clave1,valor1b));
  print_test("Obtener clave1 es la clave nueva",abb_obtener(abb,clave1)==valor1b);
  print_test("Reemplazar clave 2 con otro valor",abb_guardar(abb,clave2,valor2b));
  print_test("Obtener clave 2 es clave nueva",abb_obtener(abb,clave2)==valor2b);
  print_test("Cantidad de elementos 2",abb_cantidad(abb)==2);

  abb_destruir(abb);


}

static void pruebas_reemplazar_destruir(){
    printf("\t---PRUEBAS REEMPLAZAR CON DESTRUIR---\n");
    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));


    print_test("Guardar clave 1",abb_guardar(abb,clave1,valor1a));
    print_test("Obtener clave 1 ok",abb_obtener(abb,clave1)==valor1a);
    print_test("Guardar clave 2",abb_guardar(abb,clave2,valor2a));
    print_test("Obtener clave 2 ok",abb_obtener(abb,clave2)==valor2a);
    print_test("Cantidad de elementos 2",abb_cantidad(abb)==2);

    print_test("Reemplazar clave 1 con otro valor",abb_guardar(abb,clave1,valor1b));
    print_test("Obtener clave1 es la clave nueva",abb_obtener(abb,clave1)==valor1b);
    print_test("Reemplazar clave 2 con otro valor",abb_guardar(abb,clave2,valor2b));
    print_test("Obtener clave 2 es clave nueva",abb_obtener(abb,clave2)==valor2b);
    print_test("Cantidad de elementos 2",abb_cantidad(abb)==2);


    abb_destruir(abb);
}

static void prueba_abb_borrar(){
  printf("\t---PRUEBAS ABB BORRAR---\n");

  abb_t* abb = abb_crear(strcmp,NULL);

  char *clave1 = "perro", *valor1 = "guau";
  char *clave2 = "gato", *valor2 = "miau";
  char *clave3 = "vaca", *valor3 = "mu";

  //meter mas elementos??

  print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
  print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
  print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
  print_test("Cantidad 3",abb_cantidad(abb)==3);
  print_test("borrar clave 1(raiz)",abb_borrar(abb,clave1));
  print_test("cantidad 2",abb_cantidad(abb)==2);
  print_test("clave 1 no pertenece",!abb_pertenece(abb,clave1));
  print_test("borrar clave 2",abb_borrar(abb,clave2));
  print_test("Clave 2 no pertenece",!abb_pertenece(abb,clave2));
  print_test("cantidad 1",abb_cantidad(abb)==1);
  print_test("borrar clave 3",abb_borrar(abb,clave3));
  print_test("clave 3 no pertenece",!abb_pertenece(abb,clave3));

  abb_destruir(abb);
}

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789";
int intN(int n) { return rand() % n; }
char *randomString(int len) {
  char *rstr = malloc((len + 1) * sizeof(char));
  int i;
  for (i = 0; i < len; i++) {
    rstr[i] = alphabet[intN(strlen(alphabet))];
  }
  rstr[len] = '\0';
  return rstr;
}

void pruebas_guardar_aleatorio(int cantidad){
  printf("\t---PRUEBAS ABB GUARDAR ALEATORIO---\n");
  srand((unsigned int)time(NULL));
  //Guarda aleatoriamente n claves en dos arboles.
  //Borra el primer arbol con destruir
  //El segundo arbol borra aleatoriamente todas las claves
  abb_t* abb1=abb_crear(strcmp,free);
  abb_t* abb2=abb_crear(strcmp,free);

  bool ok=true;
  for(size_t i=0;i<cantidad;i++){
  char *p;
  p = randomString(3);
  ok&= abb_guardar(abb1,p,p);

  }
  print_test("Se guardaron cantidad elementos arbol 1 ok",ok);

  //2do arbol

  ok=true;
  char** claves2=malloc(sizeof(char*)*cantidad);
  for(size_t i=0;i<cantidad;i++){
    char* p;
    char* p2;
    p = randomString(3);
    p2 = randomString(2);
    ok&= abb_guardar(abb2,p,p2);
    claves2[i]=p;
  }
  print_test("Se guardaron cantidad elementos arbol 2 ok",ok);

  for(size_t i=0;i<cantidad;i++){
    int i_rand = rand()%cantidad;
    while(!abb_pertenece(abb2,claves2[i_rand])){
      i_rand=rand()%cantidad;
    }
    free(abb_borrar(abb2,claves2[i_rand]));
  }

   for(size_t i=0;i<cantidad;i++){
     free(claves2[i]);
   }
  free(claves2);

  print_test("Se borraron todas las claves de arbol 2",abb_cantidad(abb2)==0);


  abb_destruir(abb1);
  abb_destruir(abb2);


}


static void pruebas_abb_volumen(size_t largo, bool debug){
    printf("\t---PRUEBAS ABB VOLUMEN---\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);
    for (size_t i = 0; i < largo; i++){
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (! ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    abb = abb_crear(strcmp,free);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);
    abb_destruir(abb);
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo){
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}


static void pruebas_abb_iterar(){
    printf("\t---PRUEBAS ITERADOR ABB---\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    print_test("insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    /* Se anula esta prueba por diferencias de criterios */
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


static void prueba_abb_iterar_volumen(size_t largo){
    printf("\t---PRUEBAS ABB ITERAR VOLUMEN---\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("iteración en volumen", ok);
    print_test("iteración en volumen, recorrio todo el largo", i == largo);
    print_test("iter esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}






 void pruebas_abb_alumno()
 {
     /* Ejecuta todas las pruebas unitarias. */
     prueba_crear_abb_vacio();
     pruebas_abb_guardar();
     pruebas_abb_iterar_vacio();
     pruebas_abb_reemplazar();
     pruebas_reemplazar_destruir();
     prueba_abb_borrar();
     pruebas_guardar_aleatorio(CANTIDAD_ALEATORIOS);
     pruebas_abb_volumen(TEST_VOL,true);
     pruebas_abb_iterar();
     prueba_abb_iterar_volumen(TEST_VOL);

}
