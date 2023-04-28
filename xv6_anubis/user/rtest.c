#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]){
    int upl = 0;
    // Check validation of user input
    if (argc > 2) {
        // Error message
        printf(2, "Enter following the mode [rtest] [uplevel]: \n");
        exit();
    }else if (argc == 1) {
        // Set default uplevel value
        upl = 100; 
    }else {
        // Get uplevel value
        upl = atoi(argv[1]);
        if (upl == 0) {
            // Error message
            printf(2, "Enter a number as up level:\n");
            exit();
        }
    }
    int max = 0;
    int min = 0;
    int sum = 0;
    int a[upl];    
    for (int i = 0; i < 100; i++) {
        a[i] = prng(upl);
        if (prng(upl) > upl) {
            printf(2, "Error");
            exit();
        }
        if (max < a[i]) {max = a[i];}
        if (min > a[i]) {min = a[i];}
        sum = sum + a[i];
        printf(1, "random number:\t%d\n", a[i]);
    }
    int ave = sum / 100;
    printf(1, "Max value:\t%d\n", max);
    printf(1, "Min value:\t%d\n", min);
    printf(1, "Sum value:\t%d\n", sum);
    printf(1, "Average value: %d\n", ave);
    exit();
}