#include <stdio.h>
#include <pthread.h>

#define NUM_RECTS 1000000
#define NUM_THREADS 4

double gArea = 0.0;
pthread_mutex_t gLock;

void *threadFunction(void *pArg)
{
       int i;
       int myNum = *((int *)pArg);
       double partialHeight=0.0, lWidth=1.0/NUM_RECTS, x;

       for(i=myNum; i<NUM_RECTS; i+= NUM_THREADS)
       {
               x = (i + 0.5f) / NUM_RECTS;
               partialHeight += 4.0 / (1.0f + x*x);
       }

       pthread_mutex_lock(&gLock);
       gArea += partialHeight * lWidth;
       pthread_mutex_unlock(&gLock);
}

int main(int argc, char* argv[])
{
       int i, j;
       pthread_t tHandles[NUM_THREADS];
       int tNum[NUM_THREADS];

       pthread_mutex_init(&gLock, NULL);
       for(i=0; i<NUM_THREADS; i++)
       {
               tNum[i] = i;
               pthread_create(&tHandles[i], NULL, threadFunction, (void *)&tNum[i]);
       }

       for(j=0; j<NUM_THREADS; j++)
       {
               pthread_join(tHandles[j], NULL);
       }

       pthread_mutex_destroy(&gLock);
       printf("Computed value of Pi: %f\n", gArea);

       return 0;
}

