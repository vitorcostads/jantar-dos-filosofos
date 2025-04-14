#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5 // Numero de filosofos

char estado[N]={'P','P','P','P','P'};
pthread_mutex_t LOCK; // variavel mutex com nome lock
sem_t sem_filosofo[N]; // variavel semaforo

int esquerda(int i){//função para verificar valor do vetor anterior a esqueda
    return ((i + N -1) % N);
}

int direita(int i){ //função para verificar o valor do proximo vetor a direita
    return (i+1)%N;
}

void mostra(){
    for (int i=0; i<N; i++){
    
        printf("%c", estado[i]);
    }
    printf("\n");
        
}

void testar(int i){//Verifica os dois lados, libera o semaforo para comer
    int valor = i;
    if(estado[i]=='F' && estado[esquerda(i)]!= 'C' && estado[direita(i)] != 'C'){
        estado [i]='C';
        mostra();
        sem_post(&sem_filosofo[i]);
    }
}

void pegar_garfo(int i){// pega garfo e muda estado para comendo
    pthread_mutex_lock(&LOCK); //Zona critica

    estado[i]='F';
    mostra();
    testar(i);

    pthread_mutex_unlock(&LOCK);//Fim da zona critica

    sem_wait(&sem_filosofo[i]); // Caso nao tenha liberado no testar, só testa novamente quando vizinho largar o garfo
}

void larga_garfo(int i){
    pthread_mutex_lock(&LOCK);// Zona critica
    estado[i]='P';
    mostra();
    testar(direita(i)); // testa e libera da direita e esquerda, caso estejam parados no semaforo
    testar(esquerda(i)); 
    pthread_mutex_unlock(&LOCK); // Fim da zona critica
    
}

void* filosofo(void* arg) {
    int id = *(int*)arg;
    int cont=0;
    while (cont<5){
        sleep(rand()%3 +1);//pensa por no max 3 seg
        pegar_garfo(id);
        sleep(rand()%3 +1);//come por no max 2 seg
        larga_garfo(id);
        cont++;
    }
    return NULL;
}

int main (){

    pthread_t treads[N];
    int ids[N];

    srand(time(NULL));

    pthread_mutex_init(&LOCK, NULL);

    for (int i = 0;i<N;i++) sem_init(&sem_filosofo[i],0,0); //Inicializa Semaforo
    
    for (int i = 0;i<N;i++){
        ids[i]=i;
        pthread_create(&treads[i], NULL, filosofo, &ids[i]); // Inicializa Thread
    }
    for (int i = 0;i<N;i++) pthread_join(treads[i],NULL); // Começa as threads  

    printf("Fim de simulação");
    return 0;

}


    
    
