#include <vingraph.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <process.h>
#include <signal.h>

int dy;

void MoveCircle(int circle){
	dy = 3;
	while(1){
		Move(circle,0,dy);
		tPoint pos = GetPos(circle);
		if(pos.y>100||pos.y<0)dy = -dy;
		usleep(10000);
	}
}

void MoveRect(int rect){
	dy = 1;
	while(1){
		Move(rect,0,dy);
		tPoint pos = GetPos(rect);
		if(pos.y>100||pos.y<0)dy = -dy;
		usleep(10000);
	}
}

int main(){
	ConnectGraph();
	int rect = Rect (10, 10, 60, 60);
	int circle = Ellipse (70, 10, 60, 60);
	
	pid_t proc1,proc2;
	if(proc1 = fork()){
	if(proc2 = fork()){
	
	}else{
		MoveCircle(circle);
	}
	}else{
		MoveRect(rect);
	}
	InputChar();
	kill(proc1,SIGINT);
	kill(proc2,SIGINT);
	CloseGraph();
	return 0;
}
