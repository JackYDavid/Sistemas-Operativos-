
#include <stdio.h>

	typedef struct {
		short int ETQ;
		short int Datos[8];
		} TLineaCache;
		
	typedef TLineaCache ArrayCache[4];
	
//int inicializar(ArrayCache* RAM);
//int inicializarRAM(unsigned char*RAM[1024]);
//void leeDireccion(int* linea);

void inicializar(ArrayCache* cache){
	
	for(int i = 0; i < 4; i++){
		cache[i]->ETQ = 255;
		
		for(int j = 0; j < 8; j++){
			cache[i]->Datos[j] = 0;
			
		}	
	}	
}

int inicializarRAM(char* RAM[1024]){
	int result = 0;
	char AUX[1024];
	FILE *f1;
	
	//Apertura del fichero binario
	f1 = fopen("RAM.bin", "r");
	
	
	//Comprobar que el fichero ha sido abierto correctamente
	if(f1==NULL){
		printf("No se puede abrir el fichero RAM.bin");
		result = -1;
		
		}
		
	else{
		fread(AUX, sizeof(AUX), 1, f1);
		*RAM = AUX;
	
	}
	return result;

}


int leeDireccion(int* linea){
	int lectura = 0;
	FILE *f2;
	int lineaAUX;
	
	//abrimos el archivo y comprobamos que se ha abierto correctamente
	f2 = fopen("accesos_memoria.txt", "r");
	if(f2==NULL){
		printf("No se ha podido encontrar el fichero accesos_memoria.txt");
		lectura = -1;
	}
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


int main(){
	//variable que utilizamos para comprobar si se han leido bien los fichero o el bucle ha terminado. si fin esta en -1 no entrara en el bucle
	int fin = 0;
	
	//inicializamos la variable cache y asignamos valor en la funcion inicializar
	ArrayCache cache;
	inicializar(&cache);
	
	//Inicializamos el array de chars que llamamos RAM
	char RAM[1024];
	fin = inicializarRAM(&RAM[1024]);
	
	//Utilizamos un bucle donde lea linea por linea los accesos que se quieren hacer, hasta llegar al final del fichero accesos_memoria.txt
	int linea;
	
	while(fin != -1){
		leeDireccion(&linea);
		//ahora hay que comprobar que las etiquetas coinciden y actualizar los archivos
	
	}
	return 0;
	
}

