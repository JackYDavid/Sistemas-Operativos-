#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
	#include <windows.h>
#else
       #include <unistd.h>
#endif

typedef struct{
	short int ETQ;
	short int Datos[8];
} T_LINEA_CACHE;


T_LINEA_CACHE copiaBloqueDeRAM (unsigned int bloque, T_LINEA_CACHE CACHEsym, char RAM[1025]){

	for (int i = 0; i <= 7; i++){
		CACHEsym.Datos[i] = RAM[bloque*8+i];
	}

	return (CACHEsym);
}


T_LINEA_CACHE ordenarDatos (T_LINEA_CACHE CACHEsym){

	T_LINEA_CACHE aux;
	for (int i = 8; i >= 0; i--){
		for (int j = 0; j <= 7; j++){
			aux.Datos[j] = CACHEsym.Datos[i - 1];
		}
	}

	return (CACHEsym);
}



void imprimirAcierto( T_LINEA_CACHE CACHEsym[], int tiempoglobal, unsigned int direccionCache, unsigned int etiqueta, unsigned int linea, unsigned int palabra, unsigned int bloque){

    //Este \n mejor no borrarlo porque sino CAOS
	printf("\n");
	printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X\n\n", tiempoglobal, direccionCache, etiqueta, linea, palabra, CACHEsym[linea].Datos[palabra]);

	for(int i = 0; i < 4 ; i++) {
		printf("ETQ: %X\t", CACHEsym[i].ETQ);
		printf("Datos: ");
		for(int j = 7; j >= 0; j--) {
			printf(" %X ", CACHEsym[i].Datos[j]);
		}

		printf("\n");
	}
}



int main(int argc, char** argv) {

	//El programa arranca correctamente, inicializa las variables, lee el fichero
	int i = 0, j = 0, contador = 0, numfallos = 0;
	char texto[100];
	float tiempomedio, tiempoglobal = 1.0;

	T_LINEA_CACHE CACHEsym[4];
	//Inicializamos la etiqueta de cada elemento del array a FF en hexadecimal y sus datos a 0
	for (int i = 0; i < 4; i++){
		CACHEsym[i].ETQ = 0xFF;
		for (int j = 0; j < 8; j++){
			CACHEsym[i].Datos[j] = 0x0;
		}
	}

	//Se lee el fichero RAM.bin y se almacena en unsigned char RAM[1024]
	FILE *f1 = fopen("RAM.bin", "rb");
	unsigned char RAM[1024];
	if(f1 == NULL){
		printf("EL fichero no existe");
		exit(-1);
	}else{
		fread(RAM, sizeof(char), 1025, f1);
	}
	fclose(f1);

	//Leer caché
	unsigned int letra = 0x0; //Traduce lo leido de RAM.bin a hexadecimal
	unsigned int direccionCache = 0x0;
	unsigned int palabra = 0x0;
	unsigned int linea = 0x0;
	unsigned int etiqueta = 0x0;
	unsigned int bloque = 0x0;
	char lecturaPosiciones[5];

	//Comprobamos que exista el archivo y se pueda abrir
	FILE *f2 = fopen("accesos_memoria.txt", "r+");
	if(f2 == NULL){
		printf("El fichero no existe");
		exit(-1);
	}
	else{
		for (int i=0; i<12; i++){
			//CACHEsym lee una dirección del fichero accesos_memoria.txt
			fread(lecturaPosiciones, sizeof(char), 5, f2);
			direccionCache = strtol (lecturaPosiciones, NULL, 16);
			palabra = direccionCache & 0b0000000111; //3 bit para palabra
			bloque = direccionCache >> 3;
			linea = bloque & 0b0000011;
			etiqueta = bloque >> 2;

			//Comprueba si etq de la dirección es igual a ETQ de la línea de la caché
			if (etiqueta == CACHEsym[linea].ETQ){
				//Imprimimos el contenido de la caché
				imprimirAcierto(CACHEsym, tiempoglobal, direccionCache, etiqueta, linea, palabra, bloque);
				strncat(texto, &RAM[bloque*8 + palabra], 1);

			}
			else {
				numfallos++;
				printf("\nT: %.1f, Fallo de CACHE %d, ADDR %04X ETQ %X linea %02X palabra %02X bloque %02X \n", tiempoglobal, numfallos, direccionCache, etiqueta, linea, palabra, bloque);
				tiempoglobal = tiempoglobal + 10;
				//Se copia el bloque correspondiente desde el array RAM y se imprime un mensaje indicando que se está cargando el bloque X en la línea Y
				printf("Se está cargando el bloque %02X en la linea %02X \n", bloque, linea);

				//Se actualizan tanto el campo ETQ como los 8 bytes de datos de la línea.
				CACHEsym[linea].ETQ = etiqueta;
				CACHEsym[linea] = copiaBloqueDeRAM(bloque, CACHEsym[linea], RAM);

				//Ordenamos de mayor a menor peso
				CACHEsym[linea] = ordenarDatos (CACHEsym[linea]);

				//Imprimimos el contenido de la caché de mayor a menor peso
				imprimirAcierto(CACHEsym, tiempoglobal, direccionCache, etiqueta, linea, palabra, bloque);
				strncat(texto, &RAM[bloque*8+palabra], 1); //añadimos el texto correspondiente al texto
			}

			tiempoglobal++;
			contador++;
			printf("\n\n\n");

			//Sleep de 2 segundos
			sleep(2);
		}
		fclose(f2);
	}
	printf("Se terminó de leer las direcciones de memoria \n");

	 //Variable para el tiempo
	tiempomedio = tiempoglobal / contador;
	printf("El numero de accesos es: %d \nEl tiempo medio es: %.2f \nEl numero de fallos es: %d \n", contador, tiempomedio, numfallos);
	printf("El texto leido es: %s\n", texto);
}
