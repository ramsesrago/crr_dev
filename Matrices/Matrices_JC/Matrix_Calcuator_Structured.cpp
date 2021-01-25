#include "iostream"
#include "stdio.h"
#include "string"

typedef enum {
    SQUARE = 0,
    NXM
}matrix_type;

struct datos_matriz
{
    int rows;
    int cols;
    char nombre_matriz;
} ;

typedef struct {
    int** A;
    int rows;
    int cols;
    char nombre_matriz;
} Matriz;

datos_matriz configurar_matriz(char nombre, matrix_type tipo)  // 1- cuadrada  2- nxm   comentario usar enum par definir valore numericos 
{
    datos_matriz datos;
    datos.nombre_matriz = nombre;
    datos.rows=0;
    datos.cols=0;
    
    if(tipo == SQUARE)
    { 
        do
        {
        std::cout << std::endl;
        std::cout << "El valor de las filas y las columnas devera ser mayor a 0" << std::endl;
        std::cout << "Cuantas filas y columnas tendra la matriz " << datos.nombre_matriz << "? ";
        std::cin >> datos.rows;      
        datos.cols = datos.rows;
        } 
        while (datos.rows == 0); 
    }

    else if (tipo == NXM)
    {
        do
        {
        std::cout << std::endl;
        std::cout << "El valor de las filas devera ser mayor a 0" << std::endl;
        std::cout << "Cuantas filas tendra la matriz " << datos.nombre_matriz << "? ";
        std::cin >> datos.rows;
        }
        while (datos.rows == 0);

        do
        {
        std::cout << std::endl;
        std::cout << "El valor de las columnas devera ser mayor a 0" << std::endl;
        std::cout << "Cuantas columnas tendra la matriz " << datos.nombre_matriz << "? ";
        std::cin >> datos.cols;
        }
        while (datos.cols == 0);
    }
    std::cout << std::endl;
    return datos;
}

Matriz* Matriz_Nula(struct datos_matriz datos)
{
        Matriz* matriz = new Matriz;
        matriz->nombre_matriz = datos.nombre_matriz;
        matriz->rows = datos.rows;
        matriz->cols = datos.cols;

        matriz->A = new int* [matriz->rows];
        for (int i = 0; i < matriz->rows; i++) {
            matriz->A[i] = new int[matriz->cols];
            for (int j = 0; j < matriz->cols; j++) {
                matriz->A[i][j] = 0;
            }
        }
        return  matriz;  
}

Matriz* diagonalmayor(Matriz* matriz, char nombre )
{
    Matriz* diagonalmayor = new Matriz;
    diagonalmayor->nombre_matriz = nombre;
    diagonalmayor->rows = 1;
    diagonalmayor->cols = matriz->cols;

    diagonalmayor->A = new int* [diagonalmayor->rows];
    diagonalmayor->A[1] = new int[diagonalmayor->cols];
    for (int i = 0; i < matriz->rows; i++)
    {
        for (int j = 0; j < matriz->cols; j++)
        {
           if (i = j) {
                diagonalmayor->A[1][j] = matriz->A[i][j];
            }
        }
    }
    return diagonalmayor;
}

void imprime_matriz(Matriz* matriz)
{
    std::cout << "Los valores de la matriz " << matriz->nombre_matriz << " son:\n";

    for (int i = 0; i < matriz->rows; i++)
    {
        std::cout << std::endl;

        for (int j = 0; j < matriz->cols; j++)
        {
            std::cout << " " << matriz->A[i][j];
        }
    }
    std::cout << std::endl << std::endl;
}

void Valores_matriz (Matriz* matriz_new)
{
    std::cout << std::endl;
    for (int i = 0; i < matriz_new->rows; i++) {
        matriz_new->A[i] = new int[matriz_new->cols];
        for (int j = 0; j < matriz_new->cols; j++) {
            std::cout << "Ingrese el valor[" << i + 1 << "][" << j + 1 << "] de la matriz " << matriz_new->nombre_matriz << ": ";
            std::cin >> matriz_new->A[i][j];
        }
    }
    std::cout << std::endl;
    //return matriz_new;
}


Matriz* suma_matriz(Matriz* matrizA, Matriz* matrizB, char nombre_res )
{
    if (matrizA->rows == matrizB->rows && matrizA->cols == matrizB->cols)
    {
        datos_matriz datos_R;
        datos_R.rows = matrizB->rows;
        datos_R.cols = matrizA->cols;
        datos_R.nombre_matriz = nombre_res;

        Matriz* R = Matriz_Nula(datos_R);

        for (int i = 0; i < matrizA->rows; i++) {
            for (int j = 0; j < matrizA->cols; j++) {
                R->A[i][j] = matrizA->A[i][j] + matrizB->A[i][j];
            }
        } 
        return R;
    }
    else
    {
        std::cout << "Para sumar matrices, las matrices deben ser de el mismo tamano";
        return 0;
    }
}

Matriz* Producto_escalar(Matriz* matrizA, int num_escalar)
{
        datos_matriz datos_R;
        datos_R.rows = matrizA->rows;
        datos_R.cols = matrizA->cols;
        datos_R.nombre_matriz = matrizA->nombre_matriz;

        Matriz* R = Matriz_Nula(datos_R);

        for (int i = 0; i < matrizA->rows; i++) {
            for (int j = 0; j < matrizA->cols; j++) {
                R->A[i][j] = matrizA->A[i][j]* num_escalar;
            }
        }
        return R;
   
}

Matriz* multipica_matriz(Matriz* matrizA, Matriz* matrizB, char nombre_res)
{
    if (matrizA->cols == matrizB->rows)
    {
        datos_matriz datos_R;
        datos_R.rows = matrizA->rows;
        datos_R.cols = matrizB->cols;
        datos_R.nombre_matriz = nombre_res;

        Matriz* R = Matriz_Nula(datos_R);

                for (int k = 0; k < matrizA->rows; k++) {

                    for (int m = 0; m < matrizB->cols; m++) {

                        for (int l = 0; l< matrizA->cols; l++) {

                              R->A[k][m] = R->A[k][m] + (matrizA->A[k][l] * matrizB->A[l][m]);
                            
                        }
                    }
                } 

        return R;
    }
    else
    {
        std::cout << "Para Multiplicar matrices, el numero de columnas de la matriz A debe ser igual al numero de filas de la Matriz B";
        return 0;
    }
}


void imprime_menu() {
    int i = 1;
    std::cout << std::endl;
    std::cout << "Por favor seleccione la opcion deseada: \n\n";
    std::cout << i++ << ")  Crear una Matriz Nula \n";
    std::cout << i++ << ")  Obtener la diagonal Mayor o Pricipal \n";
    std::cout << i++ << ")  Obtener la diagonal Menor \n";
    std::cout << i++ << ")  Obtener la Traza de una matriz \n";
    std::cout << i++ << ")  Obtener la Matriz Traspuesta \n";
    std::cout << i++ << ")  Suma \n";
    std::cout << i++ << ")  Resta\n";
    std::cout << i++ << ")  Multiplicacion\n";
    std::cout << i++ << ")  Divicion\n";
    std::cout << i++ << ")  Producto por un escalar\n";
   // std::cout << i++ << ")  \n";
   // std::cout << i++ << ")  \n";
   // std::cout << i++ << ")  \n";
   // std::cout << i++ << ")  \n";
   // std::cout << i++ << ")  \n";
   // std::cout << i++ << ")  \n"; 
   // std::cout << i++ << ")  \n";
    std::cout << i++ << ")  Mostrar de nuevo el menu\n";
    std::cout << i << ")  Terminar el programa\n";
    std::cout << std::endl;
}

int main()
{
    int opcion;

    std::cout << "Bienvenido a trabajando con Matrices \n";
    

    do
    {
        imprime_menu();
        std::cin >> opcion;
        switch (opcion)
        {
        case 1: //Matriz Nula
        {
            std::cout << "Usted ha seleccionado crear una Matriz Nula " << std::endl;

            datos_matriz datos_A = configurar_matriz('A', NXM);
            Matriz* A = Matriz_Nula(datos_A);
            imprime_matriz(A);

            delete A;
        }
        break;

        case 2: //Diagonal Mayor
        {
            std::cout << "Usted ha seleccionado obtener la Diagnonal Principal o mayor de una matriz " << std::endl;

            datos_matriz datos_A = configurar_matriz('A', SQUARE);
            Matriz* A = Matriz_Nula(datos_A);
            Valores_matriz(A);
            imprime_matriz(A);
            Matriz* diagonalmayorA = diagonalmayor (A,'D');
            imprime_matriz(diagonalmayorA);
            delete diagonalmayorA;
            delete A;
        }
        break;

        case 3: //Diagonal Menor
        {

        }
        break;

        case 4: //Traza
        {

        }
        break;

        case 5: //Traspuesta
        {

        }
        break;

        case 6: //Suma de matrices
        {
            std::cout << "Usted ha seleccionado la opcion suma " << std::endl;

            datos_matriz datos_A = configurar_matriz('A', NXM);
            Matriz* A = Matriz_Nula(datos_A);
            Valores_matriz(A);
            imprime_matriz(A);

            datos_matriz datos_B = configurar_matriz('B',NXM);
            Matriz* B = Matriz_Nula(datos_B);
            Valores_matriz(B);
            imprime_matriz(B);

            Matriz* C = suma_matriz(A, B, 'C');
            imprime_matriz(C);

            delete A;
            delete B;
            delete C;
        }
            break;

        case 7: // Resta de matrices
            {
            std::cout << "Usted ha seleccionado la opción resta " << std::endl;

            datos_matriz datos_A = configurar_matriz('A', NXM);
            Matriz* A = Matriz_Nula(datos_A);
            Valores_matriz(A);
            imprime_matriz(A);

            datos_matriz datos_B = configurar_matriz('B', NXM);
            Matriz* B = Matriz_Nula(datos_B);
            Valores_matriz(B);
            imprime_matriz(B);
            Matriz* B_negativa = Producto_escalar(B,-1);
            imprime_matriz(B_negativa);

            Matriz* C = suma_matriz(A, B_negativa, 'C');
            imprime_matriz(C);
            }
            break;

        case 8:  // Multiplicacion de matrices
            {
            std::cout << "Usted ha seleccionado la opcion multiplicacion " << std::endl;
            datos_matriz datos_A = configurar_matriz('A', NXM);
            Matriz* A = Matriz_Nula(datos_A);
            Valores_matriz(A);
            imprime_matriz(A);

            datos_matriz datos_B = configurar_matriz('B', NXM);
            Matriz* B = Matriz_Nula(datos_B);
            Valores_matriz(B);
            imprime_matriz(B);

            Matriz* C = multipica_matriz(A, B, 'C');
            imprime_matriz(C);
            }

            break;
        case 9: std::cout << "Usted ha seleccionado la opción division ";
            break;
        case 10: std::cout << "Usted ha seleccionado la opcion Producto por un escalar";
            break;
        case 11: imprime_menu();
            break;
        case 12: std::cout << "Gracias por trabajar con Matrices ";
            break;

        default: std::cout << "Ingrese un valor valido de el menu ";
        }
    } while (opcion != 12);

   system("pause");

   return 0;
}
