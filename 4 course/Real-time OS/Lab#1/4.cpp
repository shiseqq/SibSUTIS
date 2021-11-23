#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#define FLAGS 3

struct Argument{
  char command[10];
  char* value;
};

void handler(int sig){
  printf("\033[=7F");
  printf("\033[?25h");
  printf("\033[0m");
  printf("\033[2J");
  exit(10);
}

int main(int argc, char* argv[]){

  signal(SIGINT,handler);

  int dx = 1;
  int dy = 1;
  int delay = 0;
  int color = 0;

  struct Argument flags[FLAGS] = {{"-dir",NULL},
                  {"-delay",NULL},
                  {"-clr",NULL}};

  if(argc%2){
    for(int i=1;i<argc;i+=2){
      char isArg = 0;
      for(int j=0;j<FLAGS;j++){
        if(flags[j].value==NULL && !strcmp(argv[i],flags[j].command)){
          flags[j].value = argv[i+1];
          isArg = 1;
        }else if(flags[j].value!=NULL && !strcmp(argv[i],flags[j].command)){
          printf("Argument \"%s\" has already been used\n",argv[i]);
          exit(1);
        }
      }
      if(!isArg){
        printf("Unknown argument \"%s\"\n",argv[i]);
        exit(2);
      }
    }
  }else{
    printf("Count of arguments must be even");
    exit(3);
  }

  if(flags[0].value != NULL){

    char* choose = flags[0].value;

    if(!strcmp(choose,"N")){
      dx=0;
      dy=-1;
    }else if(!strcmp(choose,"E")){
      dx=-1;
      dy=0;
    }else if(!strcmp(choose,"S")){
      dx=0;
      dy=1;
    }else if(!strcmp(choose,"W")){
      dx=1;
      dy=0;
    }else if(!strcmp(choose,"NE")){
      dx=1;
      dy=-1;
    }else if(!strcmp(choose,"SE")){
      dx=1;
      dy=1;
    }else if(!strcmp(choose,"SW")){
      dx=-1;
      dy=1;
    }else if(!strcmp(choose,"NW")){
      dx=-1;
      dy=-1;
    }else{
      printf("Wrong value \"%s\" of argument \"%s\"\n",flags[0].value,flags[0].command);
      exit(4);
    }
  }
  if(flags[1].value != NULL){

  char* choose = flags[1].value;

    for(int i=0;i<strlen(choose);i++){
      if(!isdigit(choose[i])){
        printf("Wrong value \"%s\" for argument \"%s\"\n",flags[1].value,flags[1].command);
        exit(5);
      }
    }

    delay = atoi(choose);

  }
  if(flags[2].value != NULL){
    char* choose = flags[2].value;

    if(strlen(choose)!=1 || !isdigit(choose[0])){
      printf("Wrong value \"%s\" for argument \"%s\"\n",flags[2].value,flags[2].command);
      exit(6);
    }

    color = atoi(choose);

    if(color<0 || color>7){
      printf("Wrong value \"%s\" for argument \"%s\", color must be in range [0...7]\n",flags[2].value,flags[2].command);
      exit(7);
    }

  }

  //printf("Dx=%d,Dy=%d,S=%d,C=%d\n",dx,dy,delay,color);

  int x=0,y=0;
  int bx=80,by=25;

  printf("\033[?25l");
  printf("\033[2J");
  while(1){

    printf("\033[=%dF",color);

    printf("\033[%d;%dH#",y+1,x+1);

    fflush(stdout);
    usleep(delay);
    printf("\033[%d;%dH ",y+1,x+1);
    fflush(stdout);

    if(dx==0 && dy==-1 && (by+y+dy)%by==24){
      x++;
    }
    if(dx==0 && dy==1 && (by+y+dy)%by==0){
      x--;
    }
    if(dx==1 && dy==0 && (bx+x+dx)%bx==0){
      y++;
    }
    if(dx==-1 && dy==0 && (bx+x+dx)%bx==79){
      y--;
    }
    x=(bx+x+dx)%bx;
    y=(by+y+dy)%by;
  }


  return 0;
}
