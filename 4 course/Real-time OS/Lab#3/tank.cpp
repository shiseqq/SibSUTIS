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

int chidCarTank = ChannelCreate(0);
int chidBoilerCar = ChannelCreate(0);
int chidBoilers[m];
int pid = getpid();
int pidBoilers;

void* car(void* arg){
	int offset = *((int*)arg);
	int id = Rect(15,10 + offset*OFFSET,30,30);
	int x = 20;
	Fill(id,RGB(34,156,187));
	int toX;
	int i = 0;
	int speed = 3;
	int mark = 0;
	int buffer[4];
	int boilerid = 0;
	int rcvid;
	int coid = ConnectAttach(0,pid,chidCarTank,0,0);
	int coidB[m];
	for(int i=0;i<m;i++){
		coidB[i] = ConnectAttach(0,pidBoilers,chidBoilers[i],0,0);
	}
	while(1){
		rcvid = MsgReceive(chidBoilerCar,&buffer,sizeof(buffer),0);
		if(rcvid<0)continue;
		if(rcvid==0)
			boilerid = buffer[2];
		else
			boilerid = buffer[0];
		MsgSend(coid,0,0,&mark,sizeof(int));
		toX = 220 + 70*boilerid;
		while(1){
			Move(id,speed,0);
			usleep(10000);
			tPoint tmp = GetPos(id);
			if(tmp.x>=toX+x/2){MoveTo(toX+x/2,tmp.y,id); break;}
		}
		int a;
		if(rcvid==0) MsgSend(coidB[boilerid],&mark,sizeof(mark),&a,sizeof(int));
		else if(rcvid>0)MsgReply(rcvid,0,&mark,sizeof(int));
		usleep(50000*(mark+1));
		while(1){
			Move(id,-speed,0);
			usleep(10000);
			tPoint tmp = GetPos(id);
			if(tmp.x<=x){MoveTo(x,tmp.y,id); break;}
		}
	}
}

void* fuelTankThread(void* arg){
	srand(time(0));
	int count = 0;
	int mark = rand()%7+4;
	vector<int> a;
	int rcvid;
	Line(10,10 + OFFSET*n,220+70 * m - 20 ,10+OFFSET*n);
	Line(10,15 + OFFSET*n,10+50,15+OFFSET*n);
	while(1){
		if(count < mark){
			int id = Rect(10,20 + OFFSET*n + count*25,50,20);
			a.push_back(id);
			Fill(id,RGB(34,156,87));
			count ++;
		}
		else{
			rcvid = MsgReceive(chidCarTank,0,0,0);
			for(int i=0;i<mark;i++){
				Delete(a.back());
				a.pop_back();
				usleep(50000);
			}
			MsgReply(rcvid,0,&mark,sizeof(int));
			count = 0;
			mark = rand()%7+4;
		
		}
		usleep(100000);
	}
}

int main(){
	ConnectGraph(NAME);
	int fd = open ("/dev/shmem/EPLANT", O_CREAT+O_RDWR, 0666);
	write (fd, &pid, 4);
	write (fd, &chidCarTank,sizeof(int));
	write (fd, &chidBoilerCar, sizeof(int));
	int num1[n];
	for(int i=0;i<n;i++){
		num1[i] = i;
	}
	int rcvid = MsgReceive(chidCarTank,&pidBoilers,sizeof(int),0);
	MsgReply(rcvid,0,0,0);
	rcvid = MsgReceive(chidCarTank,chidBoilers,sizeof(int)*m,0);
	MsgReply(rcvid,0,0,0);
	pthread_create(0,0,fuelTankThread,0);
	for(int i=0;i<n;i++){
		pthread_create(0,0,car,&num1[i]);
	}
	InputChar();
	CloseGraph();
	return 0;
}
