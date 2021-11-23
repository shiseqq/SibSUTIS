#include <sys/neutrino.h>
#include <unistd.h>
#include <vingraph.h>
#include <stdio.h>
#include </root/labs/plates.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <iostream>
#include <vector>

#define ld long double
#define ff first
#define ss second

using namespace std;
int ammo = 0;

vector<ld> vec(600);

struct RCMstr{
  ld t;
  int id;
  int dir;
  ld ttc;
};

int dirRCM[2] = {RCMC_RIGHT,RCMC_LEFT};

void *shootRocket(void *arg){
  ld time = *((ld*)arg);
  usleep(time-100000);
  for(int i = 0;i<4;i++){
    putreg(RG_GUNS,GUNS_SHOOT);
    usleep(50000);
  }
}

void *RCM(void *arg){
  RCMstr tmp = *((RCMstr*)arg);
  ld time = tmp.t;
  int ammoid = tmp.id;
  int dir = tmp.dir;
  ld timeToCentre = tmp.ttc;
  putreg(RG_RCMN,ammoid);
  putreg(RG_RCMC,RCMC_START);
  usleep(time);
  putreg(RG_RCMN,ammoid);
  if(time > timeToCentre)
    putreg(RG_RCMC,dirRCM[dir]);
  else
    putreg(RG_RCMC,dirRCM[1-dir]);
}

void *leftSecondLoc(void *arg){
  int h = *((int*)arg);
  ld usec = vec[h];
  ld countDown;
  vec[h] = -1;
  ld targetCenterTime = 38.0 * usec;
  ld timeToFly = (570-h)*10000;
  if(timeToFly>targetCenterTime){
    countDown = 4000*(570 - h);
    if(ammo < 11){
      RCMstr tmp;
      tmp.t = countDown;
      tmp.id = ammo;
      tmp.ttc = targetCenterTime;
      tmp.dir = 0;
      pthread_create(0,0,&RCM,&tmp);
      ammo++;
    }
  }else{
    countDown = targetCenterTime - timeToFly;
    pthread_create(0,0,&shootRocket,&countDown);
  }
}

void *rightSecondLoc(void *arg){
  int h = *((int*)arg);
  ld usec = vec[h];
  ld countDown;
  vec[h] = -1;
  ld targetCenterTime = 38.0*usec;
  ld timeToFly = (570-h)*10000;
  if(timeToFly>=targetCenterTime){
    countDown = 4000*(570.0 - h);
    if(ammo < 11){
      RCMstr tmp;
      tmp.t = countDown;
      tmp.id = ammo;
      tmp.ttc = targetCenterTime;
      tmp.dir = 1;
      pthread_create(0,0,&RCM,&tmp);
      ammo++;
    }
  }
  else{
  countDown = targetCenterTime - timeToFly;
  pthread_create(0,0,&shootRocket,&countDown);
  }
}

void *loc(void *arg){
  struct timespec start,stop;
  struct sigevent event;
  SIGEV_INTR_INIT (&event);
  ThreadCtl(_NTO_TCTL_IO,0);
  int id = InterruptAttachEvent(LOC_INTR,&event,0);
  int cReg;
  int cH;
  while(1){
    InterruptWait(0,NULL);
    if(getreg(RG_LOCN)==1 && getreg(RG_LOCW)==3){
      clock_gettime(CLOCK_REALTIME,&start);
      ld usec = start.tv_sec*1000000 + start.tv_nsec/1000;
      int h = getreg(RG_LOCY);
      vec[h] = usec;
    }
    if(getreg(RG_LOCN)==2 && getreg(RG_LOCW)==3){
      clock_gettime(CLOCK_REALTIME,&stop);
      ld usec = stop.tv_sec*1000000 + stop.tv_nsec/1000;
      int h = getreg(RG_LOCY);
      if(vec[h]==-1||vec[h]>usec)continue;
      vec[h] = usec - vec[h];
      pthread_create(0,0,&leftSecondLoc,&h);

    }
    if(getreg(RG_LOCN)==4 && getreg(RG_LOCW)==3){
      clock_gettime(CLOCK_REALTIME,&start);
      ld usec = start.tv_sec*1000000 + start.tv_nsec/1000;
      int h = getreg(RG_LOCY);
      vec[h] = usec;
    }
    if(getreg(RG_LOCN)==3 && getreg(RG_LOCW)==3){
      clock_gettime(CLOCK_REALTIME,&stop);
      ld usec = stop.tv_sec*1000000 + stop.tv_nsec/1000;
      int h = getreg(RG_LOCY);
      if(vec[h]==-1||vec[h]>usec)continue;
        vec[h] = usec - vec[h];
        pthread_create(0,0,&rightSecondLoc,&h);
      }
    }
}

int main(){
  char c;
  for(int i=0;i<vec.size();i++){
    vec[i] = -1;
  }
  StartGame(3);
  //InterruptEnable_();
  pthread_create(0,0,&loc,0);
  InputChar();
  EndGame();
  return 0;
}
