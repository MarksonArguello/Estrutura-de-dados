#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void init(int N, int** conj, int** tam){
    *conj = (int *)malloc((N+1) * sizeof(int));
    *tam = (int *)malloc((N+1) * sizeof(int));
    for (int i = 1; i <= N; i++) {
        *(*tam+i) = 1;
        *(*conj+i) = i;
    }


}

int count(int visitados[], int i, int* conj){
    if (visitados[i] != 0) return 0;
    visitados[i] = 1;
    if (i != conj[i]) {
        return count(visitados, i, conj);
    }
    return 1;
}


int find (int a, int* conj) {
    if (a != conj[a]) {
        conj[a] = find(conj[a], conj);
    }
    return conj[a];
}

void une(int a, int b, int* conj, int* tam) {
    a = find(a, conj);
    b = find(b, conj);
    if (a != b) {
        if (tam[a] <= tam[b]) {
            conj[a] = conj[b];
            tam[b] += tam[a];
        }
        else {
            conj[b] = conj[a];
            tam[a] += tam[b];
        }
    }
}


int main() {
    int * conj;
    int * tam;
    int n, m, a, b, answer, cases = 1;
    scanf("%d%d", &n, &m);
    while (n && m){
        init(n, &conj, &tam);
        while (m--) {
            scanf("%d%d", &a, &b);
            une(a,b, conj, tam);
        }

        answer = 0;
        int visitados[n+1];
        for (int i = 1; i <= n; i++)
            visitados[i] = 0;
        for (int i = 1; i <= n; i++) {
            answer += count(visitados,i, conj);
        }
        printf("Case %d: %d\n", cases++, answer);
        scanf("%d%d", &n, &m);
    }
    return 0;
}
