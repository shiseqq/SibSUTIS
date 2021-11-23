#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig){
  printf("\033[2J");
  printf("\033[=7F");
  printf("\033[?25h");
  printf("\033[0m");
  exit(10);
}

int main(){
  signal(SIGINT,handler);
  printf("\033[?25l");
  printf("\033[2J");
  while(1)
    for(int i=1;i<=25;i++){
      for(int j=1;j<=80;j++){
        printf("\033[%d;%dH",i,j);
        printf("#");
        fflush(stdout);
        usleep(25000);
        printf("\033[%d;%dH",i,j);
        printf(" ");
      }
    }
  return 0;
}
