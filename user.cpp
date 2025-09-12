#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <string>
using namespace std;

int main(int argc, char*argv[]){
    int iterations = stoi(argv[1]);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    for (int i = 0; i < iterations; i++){
        cout << "PID: " << pid << " PPID: " << ppid << " Iteration: " << i+1 << " before sleeping" << endl;
        sleep(1);
        cout << "PID: " << pid << " PPID: " << ppid << " Iteration: " << i+1 << " after sleeping" << endl;
    }

    return 0;
}