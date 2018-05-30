/* pila - 97548 - Vasquez Kevin - corrector: Martin */
#include "pila.h"
#include <stdlib.h>

#define STACKSIZE 5
#define CARGA_AUMENTAR_REDUCIR 2
#define CARGA_COMPARAR 4
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/*Función adicional para la pila*/
bool pila_redimensionar(pila_t *pila, size_t tam){
	void *nuevo = realloc(pila->datos, tam*sizeof(void *));
	if(nuevo == NULL) return false;
	pila->datos = nuevo;
	pila->capacidad = tam;
	return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(){
	pila_t *pila = malloc(sizeof(pila_t));
	if(pila == NULL) return false;
	pila->datos = malloc(STACKSIZE*sizeof(void *));
	if(pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->cantidad = 0;
	pila->capacidad = STACKSIZE;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
	if(pila->cantidad == pila->capacidad){
		if(!pila_redimensionar(pila, CARGA_AUMENTAR_REDUCIR*pila->capacidad)) return false;
	}
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void *pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)) return NULL;
	void *dato = pila_ver_tope(pila);
	pila->cantidad--;
	if(pila->cantidad < pila->capacidad / CARGA_COMPARAR){
		pila_redimensionar(pila, pila->capacidad / CARGA_AUMENTAR_REDUCIR);
	}
	return dato;
}