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

bool son_mismo_tipo(char cierre, char apertura){
	bool ok;
	switch(cierre){
		case '}':
			ok = apertura == '{';
			break;
		case ')':
			ok = apertura == '(';
			break;
		case ']':
			ok = apertura == '[';
			break;
	}
	return ok;
}

bool tope_es_comilla(pila_t *pila){
	if(pila_esta_vacia(pila)) return false;
	char *sep = pila_ver_tope(pila);
	return *sep == COMILLA;
}

bool verificar_sintaxis(pila_t *pila, char *linea, size_t i){
	if(es_apertura(linea[i])){
		pila_apilar(pila, &linea[i]);
	}
	 if(es_cierre(linea[i])){
		if(!son_mismo_tipo(linea[i], *(char *)pila_ver_tope(pila))){
			return true;
		}
		pila_desapilar(pila);
	}
	return false;
}

bool esta_balanceado(char *linea){
	pila_t *pila = pila_crear();
	size_t i = 0;
	bool omitir = false, salir = false;
	while(linea[i] != '\0' && !salir){
		if(omitir){
			if(linea[i] == '\'') omitir = false;
		}else{
			if(linea[i] == '\''){
				omitir = true;
			}else{
				salir = verificar_sintaxis(pila, linea, i);
			}
		}
		i++;
	}
	bool ok = pila_esta_vacia(pila) && !omitir;
	pila_destruir(pila);
	return ok;
}

void mostrar_validacion(char *linea){
	strtok(linea, "\n");
	if(esta_balanceado(linea)){
		fprintf(stdout, "%s %s\n", linea, "OK");
	}else{
		fprintf(stdout, "%s %s\n", linea, "ERROR");
	}
}

int main(int argc, char const *argv[])
{
	char *linea = NULL;
	size_t capacidad;
	while(getline(&linea, &capacidad, stdin) != -1){
		mostrar_validacion(linea);
	}

	return 0;
}