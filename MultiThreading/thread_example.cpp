#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue> // FIFO, pilas son LIFO
#include <semaphore.h>

#define MAX_QUEUE_SIZE    10
// producer-consumer problem
// race conditions
// dos threads accediendo y/o modificando un recurso compartido int flag, queue, list 

std::queue<int> myQueue;
sem_t semaphore_full;
sem_t semaphore_empty;
bool stop = false;

void* stop_producer(void* ptr) {
    sleep(20);
    stop = true;
}

void* producer(void* ptr) {
    sleep(2);
    pthread_t thread = pthread_self();
    char threadName[16];
    pthread_getname_np(thread, threadName, sizeof(threadName));
    std::cout << "Hello from " << std::string(threadName) << " with tid: " 
              << "0x" << std::hex << thread <<std::endl;
              
    // aqui comienza el trabajo real del thread
    int randomNumber = 0;
    while(!stop) {
        randomNumber = rand() % 100;   // genera un numero entero aleatorio entre 0 y 100
        std::cout << "PRODUCER: Generated random number is: " << randomNumber << std::endl;
        sem_wait(&semaphore_empty);     // stay here if the buffer is full, sem = 0
        myQueue.push(randomNumber);     // Introduce el numero aleatorio generado a la cola
        sem_post(&semaphore_full);      // increment the buffer counter for this semaphore
        sleep(1);
    }
    return NULL;
}

void* consumer(void* ptr) {
    sleep(1);
    pthread_t thread = pthread_self();
    char threadName[16];
    pthread_getname_np(thread, threadName, sizeof(threadName));
    std::cout << "CONSUMER: Hello from " << std::string(threadName) << " with tid: " 
              << "0x" << std::hex << thread << std::endl;
    
    // Extraer datos de la cola myQueue     
    int data = 0;
    while (!stop) {
        while (!myQueue.empty()) {
            sem_wait(&semaphore_full);        // Stay here if the buffer is empty
            data = myQueue.front();           // Obiene el elemento "mas viejo" de la cola FIFO
            myQueue.pop();                    // Remueve el elemento "mas viejo" de la cola
            std::cout << "CONSUMER: Printing data: " << data 
                      <<  " now the size of the queue is: " << myQueue.size() << std::endl;
            sem_post(&semaphore_empty);        // Incrementa el valor de este semaforo
        }
    }
    // la cola esta vacia
    std::cout << "CONSUMER: Queue empty, goodbye " << std::endl;
    return NULL;
}

int main() {
    std::cout << "hello from main" << std::endl;
    //Initialize sempahore
    sem_init(&semaphore_full, 0, 0);
    sem_init(&semaphore_empty, 0, MAX_QUEUE_SIZE);
    
    // creamos los trheads
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    
    // ejecutamos los threads
    pthread_create(&thread1, NULL, &producer, NULL);
    pthread_create(&thread2, NULL, &consumer, NULL);
    pthread_create(&thread3, NULL, &stop_producer, NULL);
    
    // nombramos los threads
    pthread_setname_np(thread1, "Producer thread");
    pthread_setname_np(thread2, "Consumer thread");
    pthread_setname_np(thread2, "Stop producer");
    
    // esperamos a que los trheads terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    return 0;
}