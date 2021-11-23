#include <vingraph.h>
#include <unistd.h>
#include <process.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>

int main(){
	ConnectGraph();
	
	int id = Rect(200,200,60,60);
	double phi =0,rho;
	
	int* a = (int*)mmap(0,128,PROT_WRITE|PROT_READ,MAP_SHARED,-1,0);
	int* b = (int*)mmap(0,128,PROT_WRITE|PROT_READ,MAP_SHARED,-1,0);
	
	pid_t proc;
	if(proc = fork()){
		while(1){
			char ch = InputChar();
			switch(ch){
				case 82: (*a)++;
					break;
				case 83: (*b)++;
					break;
				case 84: (*a)--;
					break;
				case 81: (*b)--;
					break;
				default:
					kill(proc,SIGINT);
					CloseGraph();
					return 0;
			}
		}
	}else{
		while(1){
			rho = (*a)*cos(phi)+(*b);
			double x = rho * cos(phi);
			double y = rho * sin(phi);
			MoveTo(x*50+200,y*50+200,id);
			phi+=0.01;
			usleep(10000);
		}
	}
}
