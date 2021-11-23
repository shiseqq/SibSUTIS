#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

struct termios savetty;
struct termios tty;

void handler (int sig){
  exit(10);
}

int main(){
  if( !isatty(0) ){
    fprintf(stderr, "stdin not terminal\n");
    exit(1);
  }
  tcgetattr(0,&tty);
  savetty=tty;
  tty.c_lflag &= ~(ICANON|ECHO|ISIG);
  tty.c_cc[VMIN]=1;
  tcsetattr(0,TCSAFLUSH, &tty);

  char ch;
  signal (SIGINT, handler);
  printf("\033[2J\033[12;32H%s\033[;H\n","Press any key");
  while(1){
    read(0,&ch,1);
    if(ch==3)break;
    printf("\033[2J\033[12;40H%d\033[;H\n",ch);
  }

  tcsetattr(0, TCSAFLUSH, &savetty);
  printf("\033[2J");
  return 0;
}
