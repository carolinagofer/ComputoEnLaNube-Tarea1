//Suma de arreglos en paralelo con OpenMP
//Nombre: Carolina Gómez Fernández
//Matrícula: A01305369

//#include "pch.h"  // Se comenta pch.h porque no es necesario si el proyecto no usa precompiled headers
#include <iostream> // Biblioteca estándar para entrada y salida
#include <omp.h>	// Biblioteca de OpenMP usada para la programación paralela
#include <vector>	// Biblioteca para poder utilizar la clase vector
#include <cstdlib>  // Biblioteca que permite usar rand() y srand()
#include <ctime>    // Biblioteca que permite usar time() para semilla aleatoria
using namespace std;

// Declaración de las constantes
#define CHUNK 100 // Tamaño del bloque de iteraciones asignado a cada hilo
#define SHOW 10 // Cantidad de elementos a mostrar al imprimir los datos

//Función que imprime los elementos del arreglo o vector
void imprimirVector(const vector<int> &d) {
	int limite = min((int)d.size(), SHOW);
	for (int i = 0; i < limite; i++) {
		cout << d[i] << " - ";
	}
	cout << endl;
}

// -- FUNCIÓN PRINCIPAL --
int main(){
	cout << "Suma de arreglos (vectores) en paralelo" << endl << endl;

	int n; // Variable en donde se guardará el número que indique el usuario

	cout << endl;
	
	cout << "Indicar el tamanio de los arreglos: ";
	cin >> n;

	if (n <= 0) { // Validación para que el número dado por el usuario no sea menor o igual a 0
		cout << "El tamanio debe ser mayor que 0." << endl;
		return 0;
	}

	// Inicializa la semilla para números aleatorios
	srand(time(NULL));

	cout << endl;

	// Verificación de soporte OpenMP en tiempo de compilación
	#ifdef _OPENMP
		cout << "OpenMP disponible. Max threads: " << omp_get_max_threads() << endl;
	#else
		cout << "OpenMP NO disponible." << endl;
	#endif

	// Vectores dinámicos (tamaño definido por el usuario)
	vector<int> a(n), b(n), c(n);

	// Llena los vectores con valores aleatorios
	// rand()%100 genera números entre 0 y 99
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 100;   // valores aleatorios para A
		b[i] = rand() % 100;   // valores aleatorios para B
	}

	// Variable que define el tamaño de los bloques de trabajo
	int pedazos = CHUNK;

	// SECCIÓN PARALELA
	// Se paraleliza el ciclo for usando OpenMP
	// Cada hilo calcula un subconjunto de índices del arreglo
	#pragma omp parallel for default (none) shared (a,b,c, pedazos) schedule (static, pedazos) 

	for (int i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}

	cout << endl;

	// Impresión de los resultados
	cout << "Imprime los " << SHOW << " primeros elementos del vector a " << endl;
	imprimirVector(a);

	cout << "Imprime los " << SHOW << " primeros elementos del vector b " << endl;
	imprimirVector(b);

	cout << endl;
	cout << "Imprime los " << SHOW << " primeros elementos del vector c " << endl;
	imprimirVector(c);

	return 0;
}


