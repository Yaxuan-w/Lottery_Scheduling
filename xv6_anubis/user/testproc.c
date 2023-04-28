#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
  int pid = 0;
  int num_child;
  int x = 0;
  // Check input validation
  if (argc < 2) {
    // No user input, set default
    num_child = 4;
  }else if (argc == 2) {
    // Set number of child according to user input
    num_child = atoi(argv[1]);
  }else {
    // Error message
    printf(2, "Only two arguments: [testproc] [number of child]\n");
    exit();
  }
  // Check the boundry. If exceeds, set default
  if (num_child < 0 || num_child > 15) {
    num_child = 4;
  }
  // Creating children
  for (int i = 0; i < num_child; i++) {
    pid = fork();
    if (pid > 0) {
      // Parent process
      printf(1, "Parent--%d creating child--%d\n", getpid(), pid);
    }else if (pid == 0) {
      // Child process
      printf(1, "Child--%d created\n", getpid());
      // Simulate CPU time
      for (int n = 0; n < 4000000000; n++) {
        x = x + 3.14*89.64;
      }
      break;
    }else {
      // Error message
      printf(2, "Process %d failed in fork!\n", getpid());
    }
  }
  exit();

}