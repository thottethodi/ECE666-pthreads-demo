all: seq-pi pthreads-demo pthreads-pi

debug: 
	gcc seq-pi.c -o seq-pi -D DEBUG -lm
	gcc pthreads-demo.c -o pthreads-demo -D DEBUG -lpthread
	gcc pthreads-pi.c -o pthreads-pi -lm -lpthread

seq-pi: seq-pi.c 
	gcc seq-pi.c -o seq-pi -lm

pthreads-pi: pthreads-pi.c 
	gcc pthreads-pi.c -o pthreads-pi -lm -lpthread

pthreads-demo: pthreads-demo.c
	gcc pthreads-demo.c -o pthreads-demo -lpthread

clean:
	rm pthreads-demo seq-pi pthreads-pi
