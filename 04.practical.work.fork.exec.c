#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(){
  int pid1, pid2;
  printf("This is the main before fork()\n");
  pid1 = fork();
  if(pid1 == 0){
    printf("\tFirst child running attemps \"ps -ef\"\n");
    char* args[] = {"/bin/ps", "-ef", NULL};
    if(execvp("/bin/ps", args) < 0){
      printf("First child failed \"ps -ef\"\n");
    }
  }
  else {
    waitpid(pid1, NULL, 0);
    printf("Parents after fork, child is %d\n\tContinue to create another child\n", pid1);
    pid2 = fork();
    if(pid2 == 0){
      printf("\tSecond child running attemps \"free -h\"\n");
      char* args[] = {"/usr/bin/free", "-h", NULL};
      if(execvp("/usr/bin/free", args) < 0){
        printf("Second child failed \"free -h\"\n");
      }
    }
    else {
      printf("These are the parents after 2 forks, second child is %d\nNothing to do more.\n", pid2);
      waitpid(pid2, NULL, 0);
    }
  }
  return 0;
}
