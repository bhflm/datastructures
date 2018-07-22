#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define TEST_VOLUMEN 10000



/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/



void pruebas_basicas(){
  pila_t* pila = pila_crear();
  int valor = 10;
  print_test("Puedo apilar un valor", pila_apilar(pila, &valor));
  print_test("Veo que el tope es exactamente lo que acabo de apilar", pila_ver_tope(pila) == &valor);
  int valor2=20;
  print_test("Puedo apilar otro valor", pila_apilar(pila, &valor2));
  print_test("Veo que el tope es exactamente lo que acabo de apilar", pila_ver_tope(pila) == &valor2);
  print_test("Pila vacia cuando tiene elementos es falso",!pila_esta_vacia(pila));
  print_test("Desapilo el ultimo valor y compruebo que verifique",pila_desapilar(pila)==&valor2);
  print_test("Cumple el invariante, valor1=tope",pila_ver_tope(pila)==&valor);
  print_test("Verifico el desapilado",pila_desapilar(pila)==&valor);
  print_test("Pila vacia",pila_esta_vacia(pila));
  print_test("Desapilar en una pila vacia es invalido",pila_desapilar(pila)==NULL);
  print_test("Ver tope en una pila vacia es invalido",pila_ver_tope(pila)==NULL);
  print_test("Apilar NULL es Valido",pila_apilar(pila,NULL));
  print_test("Desapilar NULL",pila_desapilar(pila)==NULL);
  pila_destruir(pila);
}

void pruebas_volumen(){
  pila_t* pila_vol = pila_crear();

  int* arr[TEST_VOLUMEN];

  bool ok = true;
  for(int i=0;i<TEST_VOLUMEN;i++){
    ok&=pila_apilar(pila_vol,&arr[i]);
    ok&=(pila_ver_tope(pila_vol)==&arr[i]);
  }
  print_test("Se apilaron todos los elementos respetando la invariante",ok);

  ok=true;
  for(int i=TEST_VOLUMEN-1;i>=0;i--){
    ok&=(pila_desapilar(pila_vol)==&arr[i]);
  }
  print_test("Desapilados todos los elemen respetando la invariante",ok);
  print_test("Pila vacia",pila_esta_vacia(pila_vol));
  pila_destruir(pila_vol);
}



void pruebas_pila_creada(){
  pila_t* pila_2=pila_crear();
  print_test("Ver tope en pila vacia es invalido: ",pila_ver_tope(pila_2)==NULL);
  print_test("Desapilar en pila recien creada es invalido",pila_desapilar(pila_2)==NULL);
  print_test("Esta_vacía en una pila recién creada es verdadero: ",pila_esta_vacia(pila_2));
  pila_destruir(pila_2);
}

void pruebas_pila_alumno() {
    pruebas_basicas();
    pruebas_volumen();
    pruebas_pila_creada();
}
