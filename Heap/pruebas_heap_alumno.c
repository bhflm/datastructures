#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>


#define TAM_ARREGLO 10

int funcion_cmp(void* elem1,void* elem2){
  //Suponiendo que los elementos donde apuntan elem1 y elem2 son ints
  int a= *(int*)elem1;
  int b= *(int*)elem2;

  if(a==b) return 0;
  else if(a>b) return 1;
  else return -1;
}

void pruebas_vacio(){
  heap_t* heap = heap_crear((cmp_func_t)funcion_cmp);
  print_test("Creo heap con funcion cmp, no esta vacio",heap_esta_vacio(heap));
  print_test("Cantidad de elementos en el heap es 0",heap_cantidad(heap)==0);
  print_test("Ver max en heap vacio null",!heap_ver_max(heap));
  print_test("Desencolar heap vacio es NULL",!heap_desencolar(heap));
  print_test("Encolar NULL es false",!heap_encolar(heap,NULL));
  heap_destruir(heap,NULL);
}

void pruebas_basicas(){
  heap_t* heap=heap_crear((cmp_func_t)funcion_cmp);
  int a=9,b=7,c=11,d=5,e=17,f=1,g=21;

  print_test("Creo heap vacio",heap_esta_vacio(heap));
  print_test("Elementos es 0",heap_cantidad(heap)==0);
  print_test("Encolo a",heap_encolar(heap,&a));
  print_test("Ver max es a",heap_ver_max(heap)==&a);
  print_test("Encolo b",heap_encolar(heap,&b));
  print_test("Ver max sigue siendo a",heap_ver_max(heap)==&a);
  print_test("Cantidad de elementos es 2",heap_cantidad(heap)==2);
  print_test("Encolo c",heap_encolar(heap,&c));
  print_test("C>A entonces ver max ahora es c",heap_ver_max(heap)==&c);
  print_test("Cantidad de elementos es 3",heap_cantidad(heap)==3);
  print_test("Encolo d",heap_encolar(heap,&d));
  print_test("Cantidad de elementos es 4",heap_cantidad(heap)==4);
  print_test("Encolo e",heap_encolar(heap,&e));
  print_test("Cantidad de elementos es 5",heap_cantidad(heap)==5);
  print_test("E>C Ver max ahora es E",heap_ver_max(heap)==&e);
  print_test("Encolo f",heap_encolar(heap,&f));
  print_test("Cantidad de elementos es 6",heap_cantidad(heap)==6);
  print_test("Encolo g",heap_encolar(heap,&g));
  print_test("Cantidad de elementos es 7",heap_cantidad(heap)==7);
  print_test("G>E Ver max ahora es G",heap_ver_max(heap)==&g);
  print_test("DESENCOLO G",heap_desencolar(heap)==&g);
  print_test("cantidad de elementos es 6",heap_cantidad(heap)==6);
  print_test("DESENCOLO E",heap_desencolar(heap)==&e);
  print_test("cantidad de elementos es 5",heap_cantidad(heap)==5);
  print_test("DESENCOLO C",heap_desencolar(heap)==&c);
  print_test("cantidad de elementos es 4",heap_cantidad(heap)==4);
  print_test("DESENCOLO A",heap_desencolar(heap)==&a);
  print_test("cantidad de elementos es 3",heap_cantidad(heap)==3);
  print_test("DESENCOLO B",heap_desencolar(heap)==&b);
  print_test("cantidad de elementos es 2",heap_cantidad(heap)==2);
  heap_destruir(heap,NULL);

}

void pruebas_heap_crear_arr(){
  int array[TAM_ARREGLO]={16,4,10,14,7,9,3,2,8,1}; //array que usa de ejemplo el cormen
  void* p_array[TAM_ARREGLO];
  for(size_t i=0;i<TAM_ARREGLO;i++){
    p_array[i] = &array[i];
  }
  heap_t* heap= heap_crear_arr(p_array,TAM_ARREGLO,(cmp_func_t)funcion_cmp);

  print_test("Heap con crear_arr no esta vacio",!heap_esta_vacio(heap));
  print_test("Heap cantidad=TAM_ARREGLO",heap_cantidad(heap)==TAM_ARREGLO);
  print_test("Heap en forma",heap_ver_max(heap)==p_array[0]);
  heap_destruir(heap,NULL);
}

void pruebas_heapsort(){
  int array[TAM_ARREGLO]={16,4,10,14,7,9,3,2,8,1}; //array que usa de ejemplo el cormen
  void* p_array[TAM_ARREGLO];
  for(size_t i=0;i<TAM_ARREGLO;i++){
    p_array[i] = &array[i];
  }
  heap_sort(p_array,TAM_ARREGLO,(cmp_func_t)funcion_cmp);

}

void pruebas_heap_alumno(){
  pruebas_vacio();
  pruebas_basicas();
  pruebas_heap_crear_arr();
  pruebas_heapsort();
}



//Pruebas volumen
//Pruebas con destruir
//Prueabs borde???
//mas pruebas
