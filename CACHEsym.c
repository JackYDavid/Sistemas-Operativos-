/*
 * JacoboDeCosDavidPerez.c
 * 
 * Copyright 2020 root <root@david-VirtualBox>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

	typedef struct {
		short int ETQ;
		short int Datos[8];
		} TLineaCache;
		
	typedef TLineaCache ArrayCache[4];

int main(){
	//variable que utilizamos para comprobar si se han leido bien los fichero o el bucle ha terminado. si fin esta en -1 no entrara en el bucle
	int fin = 0;
	
	//inicializamos la variable cache y asignamos valor en la funcion inicializar
	ArrayCache cache;
	fin = inicializar(&cache);
	
	//Inicializamos el array de chars que llamamos RAM
	unsigned char RAM[1024];
	fin = inicializarRAM(&RAM[1024])
	
	//Utilizamos un bucle donde lea linea por linea los accesos que se quieren hacer, hasta llegar al final del fichero accesos_memoria.txt
	unsigned char linea;
	
	while(fin != -1){
		leeDireccion(&linea);
		//ahora hay que comprobar que las etiquetas coinciden y actualizar los archivos
	
	}
	return 0;
	
}

void inicializar(ArrayCache* cache){
		ArrayCache aux;
		
	for(int i = 0; i < 4; i++){
		aux[i].ETQ = 255
		
		for(int j = 0; j < 8; j++){
			aux[i].Datos[j] = 0;
			
		}	
	}
	
	*cache = aux;
	
}

int inicializarRAM(unsigned char* RAM[1024]){
	int result = 0;
	unsigned char AUX[1024];
	FILE *f1;
	
	//Apertura del fichero binario
	f1 = fopen("RAM.bin", "r");
	
	
	//Comprobar que el fichero ha sido abierto correctamente
	if(f1==NULL){
		printf("No se puede abrir el fichero RAM.bin");
		result = -1;
		
		}
		
	else{
		fread(AUX, sizeof(RAM), 1, f1);
		*RAM = AUX
	
	}
	return result;

}


int leeDireccion(unsigned char* linea){
	int lectura = 0;
	FILE *f2;
	unsigned char lineaAUX;
	
	//abrimos el archivo y comprobamos que se ha abierto correctamente
	f2 = fopen("accesos_memoria.txt", "r");
	if(f==NULL) 
		printf("No se ha podido encontrar el fichero accesos_memoria.txt");
		lectura = -1;
		
	else{
		//comprobamos que no hemos llegado al final del archivo
		if(!feof(f2)){
			fscanf(f2, "%X", &lineaAUX);
			*linea = lineaAUX;
		}
		else 
			lectura = -1;
	}	
	
	return lectura;
	

}


