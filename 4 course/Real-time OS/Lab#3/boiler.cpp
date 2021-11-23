#include <vingraph.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <sys/neutrino.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sched.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define NAME "plant"
#define OFFSET 35

using namespace std;

const int full = 10;

const int n = 3;
const int m = 5;

int chidCarTank;
int chidBoilerCar;
int chidBoilers[m];

int pid;
int pidBoilers;

void* boilerThread(void* arg){
	int num = *((int*)arg);
	int buffer[4];
	buffer[0] = num;
	int mark = 0;
	int markPulse = 0;
	bool error = false;
	vector<int> a;
	int coid = ConnectAttach(0,pid,chidBoilerCar,0,0);
	int pulseID = 0;
	Line(220 + 70*num,15 + OFFSET*n,220+70*num+50,15+OFFSET*n);
	while(MsgSend(coid,&buffer,sizeof(buffer),&mark,sizeof(int))){
		usleep(500000);
	}
	while(1){
		if(pulseID == -1)MsgSend(coid,&buffer,sizeof(buffer),&mark,sizeof(int));
		//MsgReceive(chidBoilers[num],&mark,sizeof(int),0);
		for(int j=0;j<mark;j++){
			int id = Rect(220 + 70*num,20 + OFFSET*n +j*25,50,20);
			Fill(id,RGB(156,156,87));
			a.push_back(id);
			usleep(50000);
		}
		
		while(mark>0){
			if(mark == 2){
				pulseID = MsgSendPulse(coid,10,_PULSE_CODE_MINAVAIL+1+num,num);
			}
			sleep(1);
			mark--;
			Delete(a.back());
			a.pop_back();
		}
		if(pulseID == -1) continue;
		int rcvid = MsgReceive_r(chidBoilers[num],&mark,sizeof(mark),0);
		MsgReply(rcvid,0,0,0);
		usleep(10000);
	}
}

int main(){
	ConnectGraph(NAME);
	pidBoilers = getpid();
	int fd = open ("/dev/shmem/EPLANT", O_RDWR);
	read (fd, &pid, sizeof(int));
	read (fd, &chidCarTank,sizeof(int));
	read (fd, &chidBoilerCar, sizeof(int));
	int num[m];
	for(int i=0;i<m;i++){
		num[i] = i;
	}
	for(int i=0;i<m;i++){
		chidBoilers[i] = ChannelCreate(0);
	}
	int coid = ConnectAttach(0,pid,chidCarTank,0,0);
	MsgSend(coid,&pidBoilers,sizeof(int),0,0);
	MsgSend(coid,chidBoilers,sizeof(int)*m,0,0);
	for(int i=0;i<m;i++){
		pthread_create(0,0,boilerThread,&num[i]);
	}
	InputChar();
	CloseGraph();
	return 0;
}
