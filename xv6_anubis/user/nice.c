#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf(2, "Invalid input. Input required 3 arguments(nice pid priority): \n");
        exit();
    }
    int pid = atoi(argv[1]);
    int priority;
    if (*argv[2] == '-') {
        argv[2]++;
        priority = atoi(argv[2])*-1;
    }else {
        priority = atoi(argv[2]);
    }
    if (priority == 0) {
        if (*argv[2] != '0') {
            printf(2, "Invalid input. Input must be number in [-20, 19]\n");
            exit();
        }
    }
      // Check nice value validation
    if ((priority < -20) || (priority > 19)) {
        printf(2, "Invalid input. Input boundary: [-20, 19]\n");
        exit();
    }
    if (chnice(pid, priority) < -21) {
        printf(2, "Didn't find target process...");
    }
    exit();
}