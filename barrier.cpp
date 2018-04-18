/*
 * Mike Verdicchio
 * Thread Synchronization
 * barrier.cpp
 * 
 * This class is an implementation of a barrier
 * using binary semaphores as counting semaphores.
 */

#include <semaphore.h>
using namespace std;

class Barrier
{
  private:
    sem_t mutex;
    sem_t waiter;
    sem_t handshake;
    int counter;
    int max;

  public:
    Barrier(int number)
    {
        max = number;
        counter = 0;
        sem_init(&mutex, 0, 1);
        sem_init(&waiter, 0, 0);
        sem_init(&handshake, 0, 0);
    };

    void wait()
    {
        sem_wait(&mutex);
        counter++;

        if (counter == max)
        {
            counter = 0;
            for (int i = 0; i < max - 1; i++)
            {
                sem_post(&waiter);
                sem_wait(&handshake);
            }
            sem_post(&mutex);
            return;
        }

        sem_post(&mutex);
        sem_wait(&waiter);
        sem_post(&handshake);
        return;
    };
};