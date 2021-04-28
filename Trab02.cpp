#include <bits/stdc++.h>
#define MAXELEMENTS 1000010
#define MAXTEAMS 1010
using namespace std;

struct QUEUE{
    int value;
    QUEUE* next;
    QUEUE* prev;
};

void init(QUEUE** &currentQueue);
void initQueue(QUEUE* &currentQueue);
void push(QUEUE* &currentQueue, int element);
int pop(QUEUE* &currentQueue);
void showQueue(QUEUE* &currentQueue);
void clearQueue(QUEUE* &currentQueue);
void readTeams(short* &teamOf, int numTeams);
void enqueue(short* teamOf, QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue);
void dequeue(QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue);
void clearAll(QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue);

int main() {
    QUEUE* teamQueue;
    initQueue(teamQueue);

    QUEUE** elementsQueue;
    init(elementsQueue);



    string str;
    int scenario = 1, numTeams;
    short* teamOf = (short *) malloc(MAXELEMENTS * sizeof(short));
    cin >> numTeams;

    while(numTeams) {
        bool* teamInQueue = (bool *)malloc(sizeof(bool) * (numTeams + 1));
        for (int i = 0; i < numTeams; i++)
            *(teamInQueue + i) = false;
        if (scenario > 1) cout << endl;
        cout << "Scenario #" << scenario++ << endl;

        readTeams(teamOf, numTeams);

        cin >> str;
        while (str != "STOP") {
            if (str[0] == 'E')
                enqueue(teamOf, elementsQueue, teamQueue, teamInQueue);
            else
                dequeue(elementsQueue, teamQueue, teamInQueue);

            getchar();
            cin >> str;
        }
        clearAll(elementsQueue, teamQueue, teamInQueue);
        cin >> numTeams;
        free(teamInQueue);
    }
    return 0;
}

void init(QUEUE** &currentQueue) {
    currentQueue = (QUEUE **) malloc(MAXTEAMS * sizeof(QUEUE *));
    if (currentQueue  == NULL) {
        cout << "Erro ao iniciar fila" << endl;
        return;
    }
    for (int i = 0; i < MAXTEAMS; i++) {
        initQueue(*(currentQueue + i));
    }
}

void initQueue(QUEUE* &currentQueue) {
    currentQueue = (QUEUE *) malloc(sizeof(QUEUE));
    if (currentQueue  == NULL) {
        cout << "Erro ao iniciar fila" << endl;
        return;
    }
    currentQueue -> next = currentQueue;
    currentQueue -> prev = currentQueue;
}

void push(QUEUE* &currentQueue, int element) {
    if (currentQueue  == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    QUEUE* finalQueue = (QUEUE *) malloc(sizeof(QUEUE));
    finalQueue -> value = element;
    finalQueue -> next = currentQueue;
    finalQueue -> prev = currentQueue -> prev;
    (currentQueue -> prev) -> next = finalQueue;
    currentQueue -> prev = finalQueue;
    if (currentQueue -> next == currentQueue)
        currentQueue -> next = finalQueue;
}

int pop(QUEUE* &currentQueue) {
    if (currentQueue -> next == currentQueue) {
        cout << "Erro: tentando retirar elemento de fila vazia" << endl;
        return -1;
    }
    QUEUE* frontQueue = currentQueue -> next;
    int element = frontQueue -> value;
    currentQueue -> next = frontQueue -> next;
    (frontQueue -> next) -> prev = currentQueue;
    free(frontQueue);
    return element;
}

void showQueue(QUEUE* &currentQueue) {
    if (currentQueue  == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    while (currentQueue -> next != currentQueue) {
        cout << pop(currentQueue) << endl;
    }
}

void clearQueue(QUEUE* &currentQueue) {
    if (currentQueue  == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    while (currentQueue -> next != currentQueue) {
        pop(currentQueue);
    }
}

void readTeams(short* &teamOf, int numTeams) {
    int element;
    int numElements;

    for (int i = 0; i < numTeams; i++) {
        cin >> numElements;
        while(numElements--) {
            cin >> element;
            *(teamOf + element) = i;
        }
    }
}

void enqueue(short* teamOf, QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue) {
    if (elementsQueue  == NULL || teamQueue == NULL ||  teamInQueue == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    int element;
    cin >> element;
    int team = *(teamOf + element);
    push(*(elementsQueue + team), element);

    if (*(teamInQueue + team) == false) {
        push(teamQueue, team);
        *(teamInQueue + team) = true;
    }
}

void dequeue(QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue) {
    if (elementsQueue  == NULL || teamQueue == NULL ||  teamInQueue == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    int team = (teamQueue -> next) -> value;
    QUEUE* someQueue = *(elementsQueue + team);
    cout << pop(someQueue) << endl;

    if (someQueue -> next == someQueue) {
        pop(teamQueue);
        *(teamInQueue + team) = false;
    }
}

void clearAll(QUEUE** &elementsQueue, QUEUE* &teamQueue, bool* &teamInQueue) {
    if (elementsQueue  == NULL || teamQueue == NULL ||  teamInQueue == NULL) {
        cout << "Erro ao acessar fila (fila vazia)" << endl;
        return;
    }
    while(teamQueue -> next != teamQueue) {
        int team = (teamQueue -> next) -> value;
        clearQueue(*(elementsQueue + team));
        pop(teamQueue);
        *(teamInQueue + team) = false;
    }
}
