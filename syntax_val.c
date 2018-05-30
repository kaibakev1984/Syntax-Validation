#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#include "pila.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define COMILLA '\''

bool es_apertura(char sep){
	return sep == '{' || sep == '(' || sep == '[' ;
}

bool es_cierre(char sep){
	return sep == '}' || sep == ')' || sep == ']';
}

bool son_mismo_tipo(char cierre, void *apertura){
	char ape_car = *(char *)apertura;
	switch(cierre){
		case '}':
			return ape_car == '{';
			break;
		case ')':
			return ape_car == '(';
			break;
		case ']':
			return ape_car == '[';
			break;
	}
	return false;
}

bool tope_es_comilla(pila_t *pila){
	if(pila_esta_vacia(pila)) return false;
	char *sep = pila_ver_tope(pila);
	return *sep == COMILLA;
}

bool esta_balanceado(char *linea, size_t len){
	pila_t *pila = pila_crear();
	size_t i = 0;
	bool salir = false;
	while(i < len && !salir){
		if(tope_es_comilla(pila)){
			if(linea[i] == COMILLA){
				pila_desapilar(pila);
			}
		}else{
			if(es_apertura(linea[i]) || linea[i] == COMILLA){
				pila_apilar(pila, &linea[i]);
			}
			if(es_cierre(linea[i])){
				if(!son_mismo_tipo(linea[i], pila_ver_tope(pila))){
					salir = true;
				}else{
					pila_desapilar(pila);
				}
			}
		}
		i++;
	}
	bool ok = pila_esta_vacia(pila);
	pila_destruir(pila);
	return ok;
}

int main(int argc, char const *argv[])
{
	char *linea = NULL;
	size_t capacidad;
	ssize_t leidos;
	while((leidos = getline(&linea, &capacidad, stdin)) != -1){
		strtok(linea, "\n");
		if(esta_balanceado(linea, leidos)){
			fprintf(stdout, "%s\n", "OK");
		}else{
			fprintf(stdout, "%s\n", "ERROR");
		}
	}
	
	return 0;
}