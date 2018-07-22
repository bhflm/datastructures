#include "cola.h"
#include "testing.h"

#include <stdlib.h>
#include <stddef.h>

#include <stdio.h>

#define TEST_VOL 1000

void pruebas_cola_nula(){
	cola_t* cola = cola_crear();
	print_test("Cola recien creada esta vacia",cola_esta_vacia(cola));
	print_test("Ver primero en cola vacia es null",cola_ver_primero(cola)==NULL);
	print_test("Descolar en cola vacia es null",cola_desencolar(cola)==NULL);
	print_test("Destruyo cola vacia",true);
	cola_destruir(cola,NULL);
}

void pruebas_basicas(){
  cola_t* cola;
  cola = cola_crear();
  print_test("Cola esta vacia",cola_esta_vacia(cola));
  int a = 1,b = 2,c = 3;
  print_test("Encolo 1",cola_encolar(cola,&a));
  print_test("Ver primero es igual a lo que encole",cola_ver_primero(cola)==&a);
  print_test("Encolo 2",cola_encolar(cola,&b));
  print_test("Encolo 3",cola_encolar(cola,&c));
  print_test("INVARIANTE: Desencolo 1",cola_desencolar(cola)==&a);
  print_test("INVARIANTE: Ver primero ahora es 2",cola_ver_primero(cola)==&b);
  print_test("INVARIANTE: Desencolo 2",cola_desencolar(cola)==&b);
  print_test("INVARIANTE: Ver primero ahora es 3",cola_ver_primero(cola)==&c);
  print_test("Desencolo 3",cola_desencolar(cola)==&c);
  print_test("Cola desencolada esta vacia",cola_esta_vacia(cola));
  print_test("Encolar NULL es valido",cola_encolar(cola,NULL));
  cola_destruir(cola,free);
}

void pruebas_cola_volumen(){

  cola_t* cola=cola_crear();

  int* arr= malloc(TEST_VOL*sizeof(int));

  bool ok = true;
  for(int i=0;i<TEST_VOL-1;i++){
    ok&=cola_encolar(cola,&arr[i]);
  }

  print_test("Encolo 1000 veces el mismo",ok);
  
  ok=true;
  for(int i=0;i<TEST_VOL-1;i++){
    ok&=(cola_desencolar(cola)==&arr[i]);
  }
  print_test("Desencolo 1000 veces el mismo",ok);
  print_test("Cola vacia",cola_esta_vacia(cola));
  free(arr);

  ok=true;
  for(size_t i=0;i<TEST_VOL;i++){
    ok&=cola_encolar(cola,malloc(sizeof(int)));
  }
  print_test("Encolo 1000 punteros",ok);

  cola_destruir(cola,free);

}

void pruebas_cola_alumno() {
  pruebas_cola_nula();
  pruebas_basicas();
  pruebas_cola_volumen();
}
