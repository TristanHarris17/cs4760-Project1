#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <sys/wait.h>
using namespace std;

int main(int argc, char*argv[]){
    /*
    -h help
    -n proc # of total children processes to create
    -s simul # of children processes to run simultaneously
    -t iter # of iterations each child process should run
    */
   int proc = -1;
   int simul = -1;
   int iter = -1;
   int opt;

   // parse command line arguments
    while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
       switch (opt) {
           case 'h':
               cout << "Help: \n"
                    << "This program creates child processes that run a specified number of iterations.\n"
                    << "Usage: " << argv[0] << " [-h] [-n proc] [-s simul] [-t iter]\n"
                    << "-h help\n"
                    << "-n proc # of total children processes to create\n"
                    << "-s simul # of children processes to run simultaneously\n"
                    << "-t iter # of iterations each child process should run\n"
                    << "All options -n, -s, and -t are required and must be positive integers." << endl;
               return 0;
            case 'n': {
                int val = stoi(optarg);
                if (val < 0) {
                    cerr << "Error: -n must be a non-negative integer." << endl;
                    return 1;
                }
                proc = val;
                break;
            }
            case 's': {
                int val = stoi(optarg);
                if (val < 0) {
                    cerr << "Error: -s must be a non-negative integer." << endl;
                    return 1;
                }
                simul = val;
                break;
            }
            case 't': {
                int val = stoi(optarg);
                if (val < 0) {
                    cerr << "Error: -t must be a non-negative integer." << endl;
                    return 1;
                }
                iter = val;
                break;
            }
           default: // unavailable option
               cerr << "Usage: " << argv[0] << " [-h] [-n proc] [-s simul] [-t iter]" << endl; 
               return 1;
       }
    }

    // check if all required arguments are provided
    if (proc < 0 || simul < 0 || iter < 0) {
         cerr << "Error: All options -n, -s, and -t are required and must be positive integers." << endl;
         return 1;
    }

    // fork on oss and exec on user with arguments
    int running = 0;
    int launched = 0;
    
    // loop until all processes are launched
    while (launched < proc) {
        // check if a new process can be launched
        if (running < simul){
            pid_t child_pid = fork();
            if (child_pid < 0) {
                cerr << "Fork failed." << endl;
                return 1;
            }
            if (child_pid == 0) {
                char* args[] = {(char*)"./user", (char*)to_string(iter).c_str(), NULL};
                execv(args[0], args);
                cerr << "Exec failed." << endl;
                exit(1);
            }
            else {
                running++;
                launched++;
                cout << "Parent process PID: " << getpid() << " created child PID: " << child_pid << endl;
            }
        }
        else {
            pid_t finished_pid = wait(NULL); // wait for one child process to finish
            running--;
            cout << "PID: " << finished_pid << " PPID: " << getpid() << " has completed." << endl;
        }
    }

    // wait for all remaining child processes to finish
    while (running > 0) {
        pid_t finished_pid = wait(NULL);
        running--;
        cout << "PID: " << finished_pid << " PPID: " << getpid() << " has completed." << endl;
    }

    cout << "All child processes have completed." << endl;
    cout << "Total children launched = " << launched << endl;
    
    return 0;
}