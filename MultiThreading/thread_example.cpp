#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue> // FIFO, pilas son LIFO

#define MAX_QUEUE_SIZE    10
// producer-consumer problem
// race conditions
// dos threads accediendo y/o modificando un recurso compartido int flag, queue, list 

std::queue<int> myQueue;

void* producer(void* ptr) {
    usleep(100000);
    pthread_t thread = pthread_self();
    char threadName[16];
    pthread_getname_np(thread, threadName, sizeof(threadName));
    std::cout << "Hello from " << std::string(threadName) << " with tid: " 
              << "0x" << std::hex << thread <<std::endl;
              
    // aqui comienza el trabajo real del thread
    int randomNumber = 0;
    while (myQueue.size() < MAX_QUEUE_SIZE) {
        randomNumber = rand() % 100;
        std::cout << "Generated random number is: " << randomNumber << std::endl;
        myQueue.push(randomNumber);
    }
    return NULL;
}

void* consumer(void* ptr) {
    usleep(100000);
    pthread_t thread = pthread_self();
    char threadName[16];
    pthread_getname_np(thread, threadName, sizeof(threadName));
    std::cout << "Hello from " << std::string(threadName) << " with tid: " 
              << "0x" << std::hex << thread << std::endl;
    
    // Extraer datos de la cola myQueue     
    int data = 0;
    while (!myQueue.empty()) {
        data = myQueue.front();
        myQueue.pop();
        std::cout << "Printing data: " << data 
                  <<  " now the size of the queue is: " << myQueue.size() << std::endl;
    }
    // la cola esta vacia
    std::cout << "Queue empty, goodbye " << std::endl;
    return NULL;
}

int main() {
    std::cout << "hello from main" << std::endl;
    // creamos los trheads
    pthread_t thread1;
    pthread_t thread2;
    
    // ejecutamos los threads
    pthread_create(&thread1, NULL, &producer, NULL);// este esta corriendo
    pthread_create(&thread2, NULL, &consumer, NULL);
    
    // nombramos los threads
    pthread_setname_np(thread1, "Producer thread"); /// task1 ya acabo
    pthread_setname_np(thread2, "Consumer thread");
    
    // esperamos a que los trheads terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}
