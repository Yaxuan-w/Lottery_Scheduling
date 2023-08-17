# Lottery_Scheduling

## Modules

### "nice"

#### Implementation

In `sysproc.c`: Retrieve arguments under `sys_chnice` function and return error if having trouble. 

In `proc.c`: Lock the current process. First iterate the ptable by for loop and discover the target process by comparing pid. Change the priority, since in this project we design tickets based on the priority of the current process, when the priority changes, the tickets of that process will also change. Release the lock after modification and return the priority, or if the target process is not found, release the lock, and print the error message.

In `nice.c`: Check the validation of number of user inputs and whether the target process is found in `nice.c`. If not, output an error message.

#### How to test

1.  Use `testproc` command to create several processes, and use `status` command to list all process with priority (nice value)
```bash
testproc
status
```
2.  Use the `nice` command in the terminal to modify the priority of the target process.
```bash
// Example
nice 4 0
status
```

### Random Number Generator 

#### Algorithm - QuickTaus

One special case of the XORShift algorithm — LFSR is used to generate a pseudo-random number generator. This generator is implemented by QuickTaus algorithm which uses a trinomial recurrence $P(z) = z! - z^n - 1$ to generate a bit stream in blocks of 18, 2, 7, 13(respectively) bits according to $b_(n+k) = b_(n+q) + b_n$. In this case, bit size is 32, bits. z1-z4 are the LFSR initial seeds. 4294967294, 4294967288, 4294967280, 4294967168 are the masks of 31, 29, 27, 25(respectively) ones, then 1, 3, 4, 7(respectively) zeros.

For more detailed, I intercept one part of the code to elaborate:

```C
a = z1 << 6;          // step forward 6, 𝑧6
b = a ^ z1;            // by the construction, 𝑧0 +𝑧6
c = b >> 13;           // tail = new block of
z1 = z1 & 4294967294;  // make room for new block in z1
z1 = z1 << 18;         // pop 18 bits
z1 = z1 ^ c;           // combine bitwise: z1+y mod 2
```

Finally, the four values obtained do XOR to obtain the final random number.

#### How to test

A new command line `rtest` and the user program named `rtest.c` under user folder are designed for testing PRNG. In this part of the code, the user has the option to enter a specific maximum value of random numbers or to use the default maximum (100). It first checks if the user input is legal, then it runs 10 times based on the maximum value, prints the random number each time and at the end it calculates the average, the minimum value, and the maximum value. The final results are relatively uniformly distributed (since the average is basically the middle value).

### Scheduler 

#### Data Structure

Use natively implemented linked list for the p-table as the data structure to manage our lottery scheduler. Implemented process specific values (nice value, tickets, and run times) that the scheduler relies on within the process control block which acts as linked list nodes.

#### Handle a process leaving or entering a syscall while maintaining the policy

When a process is creaeted, three parameters are initialized in the `allocproc` function. The initial value of `priority` is set to 11, `tickets` to 9, and `rtime` to 0. The parent process are designed to have higher priority than the child process. When the test file forks child process, the priority of the child process is modified by calling `chnice` system call.

A function `totalTickets()` is implemented to calculate the total tickets. Every time the function is called, the entire ptable is traversed, and the sum is calculated based on the number of votes of each process. In the scheduler function, `totalTickets()` is called again every time the loop is entered to calculated the total number of tickets, so the process leaving or entering is taken into account.

#### Map

tickets = nice value * (-1) + 20

#### What if the target process is not found

If the scheduler does not find the target process at the end, it will end this traversal, enter the next loop, recalculate winner ticket and then search for the target process.

#### How to test

`rtime` is designed to show how many times the process was run in order to reflect the accuracy of the lottery algorithm, since the process with high nice value/low tickets should be scheduled less often and the process with zero tickets should never be scheduled. A user command called `status` is implemented in order to track the process status of each of the running process. This command will present the name, pid, state, nice value, number of tickets, and number of times scheduled. In test file, `testproc.c`, manually set tickets to 0 for two processes to confirm that the lottery scheduler will not schedule those processes.
