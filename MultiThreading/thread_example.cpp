/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <pthread.h>
#include <unistd.h>

void* task1(void* ptr){
    sleep(3);
    std::cout << "hello from task 1" << std::endl;
    return NULL;
}

void* task2(void* ptr){
    std::cout << "hello from task 2" << std::endl;
    return NULL;
}

int main() {
    std::cout << "hello from main" << std::endl;
    // creamos los trheads
    pthread_t thread1;
    pthread_t thread2;
    
    
    // ejecutamos los trheads
    pthread_create(&thread1, NULL, &task1, NULL);
    pthread_create(&thread2, NULL, &task2, NULL);
    
    // esperamos a que los trheads terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    // task1();  // secuencial primero se eejecuta esto, 10 segundos
    //tast2();  // se va a ejecutar 10 segundos
    return 0;
}