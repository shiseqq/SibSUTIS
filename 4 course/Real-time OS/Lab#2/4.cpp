#include <vingraph.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t mutex;
int id,a = 0,b = 0;

void *threadMove(void* arg){
	double phi =0,rho;
	while(1){
		pthread_mutex_lock(&mutex);
		rho = a*cos(phi) + b;
		pthread_mutex_unlock(&mutex);
		double x = rho * cos(phi);
		double y = rho * sin(phi);
		MoveTo(x*100+200,y*100+200,id);
		phi += 0.01;
		usleep(10000);
	}
}

void* threadChange(void* arg){
	while(1){
		char ch = InputChar();
		
		switch(ch){
			case 82:
				pthread_mutex_lock(&mutex);
				a++;
				pthread_mutex_unlock(&mutex);
				break;
			case 83:
				pthread_mutex_lock(&mutex);
				b++;
				pthread_mutex_unlock(&mutex);
				break;
			case 84:
				pthread_mutex_lock(&mutex);
				b--;
				pthread_mutex_unlock(&mutex);
				break;
			case 81:
				pthread_mutex_lock(&mutex);
				a--;
				pthread_mutex_unlock(&mutex);
				break;
			default:
				return NULL;
		}
	}
}

int main(){
	pthread_mutex_init(&mutex,NULL);
	pthread_t moveThread,changeThread;
	ConnectGraph();
	id = Rect(10,10,60,60);
	
	pthread_create(&moveThread,NULL,threadMove,NULL);
	pthread_create(&changeThread,NULL,threadChange,NULL);
	
	pthread_join(changeThread,NULL);
	
	CloseGraph();
	return 0;
	

}
