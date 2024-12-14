#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define MAX 10 // Tamaño máximo de la matriz

// Prototipos de funciones relacionadas con funciones matemáticas
long double f1(long double x);
long double f2(long double x);
long double f3(long double x);
long double f4(long double x);
long double secante(long double p0, long double p1, long double (*f)(long double), int kmax, long double eps);
long double biseccion(long double a, long double b, long double (*f)(long double), int kmax, long double eps);

// Prototipos de funciones relacionadas con matrices
void leerMatriz(float matriz[MAX][MAX], float vector[MAX], int n);
void mostrarMatriz(float matriz[MAX][MAX], float vector[MAX], int n);
int esDominanteDiagonal(float matriz[MAX][MAX], int n);
float calcularDeterminante(float matriz[MAX][MAX], int n);
void corregirElemento(float matriz[MAX][MAX], int n);

// Prototipo del método Jacobi
void metodoJacobi(float A[MAX][MAX], float b[MAX], float x[MAX], int n, int kmax, float eps);

// Prototipo del método de potencias
void metodoPotencias(float matriz[MAX][MAX], float vectorInicial[MAX], int n, float tol, int iterMax);

int main() {
	cout << "Universidad  Nacional Autonoma de Mexico\n";
	cout << "Facultad de Estudios Superiores Acatlan\n";
	cout << "Metodos numericos I\n";
	cout << "Ultimo paquete de programas\n";
	cout << "Programa hecho por Garcia Reyes Arely Lizeth, Hernandez Barraza Alejandro y Lozano Perez Johan Andres\n";
	cout << "\n";
	cout << "\n";
    bool continuar = true;
    while (continuar) {
        int opcion;
        
        cout << "Seleccione una opcion:\n";
        cout << "1. Operaciones con funciones matematicas\n";
        cout << "2. Operaciones con matrices\n";
        cout << "3. Metodo de potencias\n";
        cout << "4. Salir\n";
        cin >> opcion;

        if (opcion == 1) {
            // Operaciones con funciones matemáticas
            int metodo, kmax, funcion;
            long double p0, p1, a, b, eps, raiz;

            cout << "Seleccione el metodo para encontrar la raiz:\n";
            cout << "1. Metodo de la secante\n";
            cout << "2. Metodo de biseccion\n";
            cin >> metodo;

            cout << "Seleccione la funcion:\n";
            cout << "1. f(x) = x^2 * cos(x) - 2x\n";
            cout << "2. f(x) = (6 - 2/x^2) * (e^(2+x)/4) + 1\n";
            cout << "3. f(x) = x^3 - 3*sin(x^2) + 1\n";
            cout << "4. f(x) = x^3 + 6x^2 + 9.4x + 2.5\n";
            cin >> funcion;

            long double (*f)(long double);
            switch (funcion) {
                case 1: f = f1; break;
                case 2: f = f2; break;
                case 3: f = f3; break;
                case 4: f = f4; break;
                default:
                    cout << "Funcion no valida.\n";
                    continue;
            }

            if (metodo == 1) { // Secante
                cout << "Ingrese el intervalo inicial (p0 y p1):\n";
                cin >> p0 >> p1;
                cout << "Ingrese la tolerancia de error (eps):\n";
                cin >> eps;
                cout << "Ingrese el maximo numero de iteraciones (kmax):\n";
                cin >> kmax;
                raiz = secante(p0, p1, f, kmax, eps);
                cout << "La raiz aproximada encontrada es: " << raiz << endl;
            } else if (metodo == 2) { // Biseccion
                cout << "Ingrese el intervalo (a y b):\n";
                cin >> a >> b;
                cout << "Ingrese la tolerancia de error (eps):\n";
                cin >> eps;
                cout << "Ingrese el maximo numero de iteraciones (kmax):\n";
                cin >> kmax;
                raiz = biseccion(a, b, f, kmax, eps);
                cout << "La raiz aproximada encontrada es: " << raiz << endl;
            } else {
                cout << "Metodo no valido.\n";
            }
        } else if (opcion == 2) {
            // Operaciones con matrices
            float matriz[MAX][MAX], vector[MAX];
            int n;

            cout << "Introduce la dimension de la matriz (n x n): ";
            cin >> n;
            leerMatriz(matriz, vector, n);

            char subopcion;
            do {
                cout << "Seleccione una operacion:\n";
                cout << "a. Mostrar la matriz y el vector\n";
                cout << "b. Verificar si la matriz es dominante diagonal\n";
                cout << "c. Calcular el determinante\n";
                cout << "d. Corregir un elemento de la matriz\n";
                cout << "e. Resolver el sistema de ecuaciones con el metodo de Jacobi\n";
                cout << "f. Regresar al menu principal\n";
                cin >> subopcion;

                switch (subopcion) {
                    case 'a':
                        mostrarMatriz(matriz, vector, n);
                        break;
                    case 'b':
                        if (esDominanteDiagonal(matriz, n)) {
                            cout << "La matriz es dominante diagonal.\n";
                        } else {
                            cout << "La matriz no es dominante diagonal.\n";
                        }
                        break;
                    case 'c': {
                        float determinante = calcularDeterminante(matriz, n);
                        cout << "Determinante: " << determinante << endl;
                        break;
                    }
                    case 'd':
                        corregirElemento(matriz, n);
                        break;
                    case 'e': {
                        float x[MAX] = {0}; // Vector de incógnitas inicial
                        int kmax;
                        float eps;
                        cout << "Ingrese el numero maximo de iteraciones (kmax): ";
                        cin >> kmax;
                        cout << "Ingrese la tolerancia de error (eps): ";
                        cin >> eps;
                        metodoJacobi(matriz, vector, x, n, kmax, eps);
                        break;
                    }
                    case 'f':
                        break;
                    default:
                        cout << "Opcion no valida.\n";
                }
            } while (subopcion != 'f');
        } else if (opcion == 3) {
            // Metodo de potencias
            float matriz[MAX][MAX], vectorInicial[MAX];
            int n;
            float tol;
            int iterMax;

            cout << "Introduce la dimension de la matriz (n x n): ";
            cin >> n;
            leerMatriz(matriz, vectorInicial, n);

            cout << "Ingrese el vector inicial:\n";
            for (int i = 0; i < n; ++i) {
                cout << "Elemento [" << i + 1 << "]: ";
                cin >> vectorInicial[i];
            }
            cout << "Ingrese la tolerancia (tol): ";
            cin >> tol;
            cout << "Ingrese el numero maximo de iteraciones: ";
            cin >> iterMax;
            metodoPotencias(matriz, vectorInicial, n, tol, iterMax);
        } else if (opcion == 4) {
            continuar = false;
        } else {
            cout << "Opcion no valida. Intente nuevamente.\n";
        }
    }

    return 0;
}

// Implementación de funciones relacionadas con matrices
void leerMatriz(float matriz[MAX][MAX], float vector[MAX], int n) {
    cout << "Ingrese los elementos de la matriz (fila por fila):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matriz[i][j];
        }
    }

    cout << "Ingrese los elementos del vector independiente:\n";
    for (int i = 0; i < n; i++) {
        cout << "Elemento [" << i + 1 << "]: ";
        cin >> vector[i];
    }
}

void mostrarMatriz(float matriz[MAX][MAX], float vector[MAX], int n) {
    cout << "Matriz (A|b):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "| " << vector[i] << endl;
    }
}

int esDominanteDiagonal(float matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        float sumaFila = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sumaFila += fabs(matriz[i][j]);
            }
        }
        if (fabs(matriz[i][i]) <= sumaFila) {
            return 0;
        }
    }
    return 1;
}

float calcularDeterminante(float matriz[MAX][MAX], int n) {
    float det = 1;
    for (int i = 0; i < n; i++) {
        if (matriz[i][i] == 0) {
            return 0;
        }
        det *= matriz[i][i];
    }
    return det;
}

void corregirElemento(float matriz[MAX][MAX], int n) {
    int fila, columna;
    float nuevoValor;
    cout << "Ingrese la fila y columna del elemento a corregir (1-based):\n";
    cin >> fila >> columna;
    cout << "Ingrese el nuevo valor: ";
    cin >> nuevoValor;
    matriz[fila - 1][columna - 1] = nuevoValor;
}

// Implementación del método Jacobi
void metodoJacobi(float A[MAX][MAX], float b[MAX], float x[MAX], int n, int kmax, float eps) {
    float xNuevo[MAX];
    for (int iter = 0; iter < kmax; iter++) {
        for (int i = 0; i < n; i++) {
            float suma = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    suma += A[i][j] * x[j];
                }
            }
            xNuevo[i] = (b[i] - suma) / A[i][i];
        }

        float error = 0;
        for (int i = 0; i < n; i++) {
            error = max(error, fabs(xNuevo[i] - x[i]));
            x[i] = xNuevo[i];
        }

        if (error < eps) {
            cout << "El metodo de Jacobi convergio en " << iter + 1 << " iteraciones.\n";
            break;
        }
    }

    cout << "Solucion aproximada: ";
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
}

// Implementación del método de potencias
void metodoPotencias(float matriz[MAX][MAX], float vectorInicial[MAX], int n, float tol, int iterMax) {
    float vectorAnterior[MAX], vectorNuevo[MAX];
    float lambdaAnterior = 0, lambdaNuevo = 0;

    for (int i = 0; i < n; ++i) {
        vectorAnterior[i] = vectorInicial[i];
    }

    for (int iter = 0; iter < iterMax; ++iter) {
        // Multiplicación matriz por vector
        for (int i = 0; i < n; ++i) {
            vectorNuevo[i] = 0;
            for (int j = 0; j < n; ++j) {
                vectorNuevo[i] += matriz[i][j] * vectorAnterior[j];
            }
        }

        // Calcular el valor propio aproximado (lambdaNuevo)
        lambdaNuevo = vectorNuevo[0];
        for (int i = 1; i < n; ++i) {
            if (fabs(vectorNuevo[i]) > fabs(lambdaNuevo)) {
                lambdaNuevo = vectorNuevo[i];
            }
        }

        // Normalizar el vector nuevo
        for (int i = 0; i < n; ++i) {
            vectorNuevo[i] /= lambdaNuevo;
        }

        // Calcular el error
        float error = fabs(lambdaNuevo - lambdaAnterior);
        cout << "Iteracion " << iter + 1 << " - Lambda: " << lambdaNuevo << " - Error: " << error << endl;

        if (error < tol) {
            cout << "Metodo de potencias convergio en " << iter + 1 << " iteraciones.\n";
            break;
        }

        lambdaAnterior = lambdaNuevo;
        for (int i = 0; i < n; ++i) {
            vectorAnterior[i] = vectorNuevo[i];
        }
    }

    cout << "Valor propio aproximado: " << lambdaNuevo << endl;
    cout << "Vector propio aproximado: [";
    for (int i = 0; i < n; ++i) {
        cout << vectorNuevo[i] << (i < n - 1 ? ", " : "]\n");
    }
}

// Implementación de funciones matemáticas
long double f1(long double x) {
    return x * x * cos(x) - 2 * x;
}

long double f2(long double x) {
    return (6 - 2 / (x * x)) * (exp(2 + x) / 4) + 1;
}

long double f3(long double x) {
    return pow(x, 3) - 3 * sin(pow(x, 2)) + 1;
}

long double f4(long double x) {
    return pow(x, 3) + 6 * x * x + 9.4 * x + 2.5;
}

long double secante(long double p0, long double p1, long double (*f)(long double), int kmax, long double eps) {
    for (int k = 0; k < kmax; k++) {
        long double q0 = f(p0);
        long double q1 = f(p1);
        if (fabs(q1 - q0) < eps) {
            cout << "Division por cero detectada.\n";
            return p1;
        }

        long double p = p1 - q1 * (p1 - p0) / (q1 - q0);
        if (fabs(p - p1) < eps) {
            return p;
        }

        p0 = p1;
        p1 = p;
    }

    cout << "El metodo no convergio tras " << kmax << " iteraciones.\n";
    return p1;
}

long double biseccion(long double a, long double b, long double (*f)(long double), int kmax, long double eps) {
    if (f(a) * f(b) >= 0) {
        cout << "El intervalo inicial no es valido.\n";
        return a;
    }

    for (int k = 0; k < kmax; k++) {
        long double c = (a + b) / 2;
        if (fabs(f(c)) < eps || fabs(b - a) / 2 < eps) {
            return c;
        }

        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    cout << "El metodo no convergio tras " << kmax << " iteraciones.\n";
    return (a + b) / 2;
}

