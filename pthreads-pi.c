#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>


//#define DEBUG

#ifdef DEBUG
#define N 4
#define NUM_THREADS 2 
#endif

#ifndef DEBUG
#define N (128*1024*1024)
#define NUM_THREADS 2 
#endif

int Cin[NUM_THREADS] = {0};


int trial() {
   double x, y, dist;
   x = drand48();
   y = drand48();
   dist = sqrt(x*x+y*y);

#ifdef DEBUG
   printf("Point (%5.3f,%5.3f) is %5.3f away from the origin.\n", x, y, dist);
#endif

   if (dist <1.0) return 1; 
   else return 0;
}

void * worker_function(void *tid) {
   int i,local_sum=0;
   for(i=0; i<(N/NUM_THREADS); i++) {
     local_sum += trial();
   };
   Cin[*(int *) tid] += local_sum;
}

int main() {

   int i =0;
   int tid[NUM_THREADS];
   pthread_t worker_threads[NUM_THREADS-1];
   

#ifndef DEBUG
   srand48(time(NULL)); // randomize seed
#endif
   tid[0] = 0;
   for(i=1; i< NUM_THREADS; i++) {
     tid[i] = i;
     if(pthread_create(&worker_threads[i-1], NULL, worker_function, &tid[i])) {
       fprintf(stderr, "Error creating thread %d\n",i);
     }
   }

   worker_function(&tid[0]);
   for(i=0; i< NUM_THREADS-1; i++) {
     pthread_join(worker_threads[i], NULL); 
   }
   for(i=0; i< NUM_THREADS-1; i++) {
     Cin[0]+= Cin[i+1];
   }

   printf("Pi estimate : %5.6f\n", (double)Cin[0]*4.0/N);

}


