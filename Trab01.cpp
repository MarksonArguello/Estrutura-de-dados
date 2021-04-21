#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 8

using namespace std;
void init(int* &V, int &tamanho);
void insere(int* &V, int &tam, int &numElementos, int valor);
void overflow(int* &V, int &tamanho);
void mergeSort(int* &V, int inicio, int fim);
void merge(int* &V, int inicio, int meio, int fim);
void quickSort(int* &V, int ini, int tam);
void bubbleSort(int* &V, int numElementos);
void swap(int &i, int &j);
void mostra(int* &V, int numElementos);

int main(int argc, char *argv[]) {
    
    int* V;
    int valor, numElementos = 0, tamanho = 0;

    init(V, tamanho); 
    
    while(cin >> valor) {
        getchar();
        insere(V, tamanho, numElementos, valor);        
    }

    if (argc > 1 && strcmp(argv[1], "-q") == 0)
        quickSort(V, 0, numElementos);
    else if (argc > 1 && strcmp(argv[1], "-m") == 0)
        mergeSort(V, 0, numElementos);
    else 
        bubbleSort(V, numElementos);

    mostra(V, numElementos);
    return 0;
}

void init(int* &V, int &tamanho) {
    tamanho = TAM;
    V = (int *) malloc(tamanho * sizeof(int));
    if (V == NULL) {
        cout << "Vetor inváldio\n";
        return;
    }
}

void insere(int* &V, int &tam, int &numElementos, int valor) {
    if (numElementos == tam) {
        overflow(V, tam);
    }
    if (V == NULL) {
        cout << "Vetor inváldio\n";
        return;
    }
    V[numElementos++] = valor;
}

void overflow(int* &V, int &tamanho) {
    int* tmp = (int *) malloc(2 * tamanho * sizeof(int));
    if (tmp == NULL) { 
        cout << "Erro na alocação de memória" << endl;
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        tmp[i] = V[i];
    }
    free(V);
    V = tmp;
    tamanho <<= 1;
}

void mergeSort(int* &V, int inicio, int fim) {  
    if (inicio >= fim ) return;
    int meio = (fim + inicio) >> 1;
    mergeSort(V, inicio, meio);
    mergeSort(V, meio+1, fim);
    merge(V, inicio, meio, fim);  
}

void merge(int* &V, int inicio, int meio, int fim) {
    int tam = (fim - inicio + 1); 
    int* temp = (int *) malloc(tam * sizeof(int));
    int i = inicio, j = meio+1, elements = 0;
    while (i <= meio && j <= fim) {
        if (V[i] <= V[j]) {
            temp[elements++] = V[i++];
        } else {
            temp[elements++] = V[j++];
        }
    }
    while (i <= meio) {
        temp[elements++] = V[i++];
    }
    while (j <= fim) {
        temp[elements++] = V[j++];
    }
    for (int i = inicio; i <= fim; i++) {
        V[i] = temp[i - inicio];
    }
    free(temp);
}

void quickSort(int* &V, int ini, int tam) {
    int fim = tam - 1;
    int pivo = (ini + fim) >> 1;
    int i = ini, j = fim;
    while (i <= j) {
        while (i < tam && V[i] < V[pivo]) {
            i++;
        }
        while (j > ini && V[j] > V[pivo]) {
            j--;
        }
       if (i <= j) {
            swap(V[j], V[i]);
            i++;
            j--;
        }

    }
    if (ini < j)  {
        quickSort(V, ini, j+1);
    }
    if (i < fim) {
        quickSort(V, i, tam);
    }

}

void bubbleSort(int* &V, int numElementos) {
    for (int i = 0; i < numElementos - 1; i++) {
        for (int j = 0; j < numElementos - i - 1; j++) { 
            if (V[j] > V[j + 1]) {
                swap(V[j], V[j + 1]);
            }
        }
    }
}

void swap(int &i, int &j) {
    int tmp = i;
    i = j;
    j = tmp;
}

void mostra(int* &V, int numElementos) {
    for (int i = 0; i < numElementos; i++) {
        cout << V[i] << endl;
    }
}
