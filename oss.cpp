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
                    << "-h help\n"
                    << "-n proc # of total children processes to create\n"
                    << "-s simul # of children processes to run simultaneously\n"
                    << "-t iter # of iterations each child process should run\n"
                    << "All options -n, -s, and -t are required and must be positive integers." << endl;
               return 0;
            case 'n':
                proc = stoi(optarg);
                break;
            case 's':
                simul = stoi(optarg);
                break;
            case 't':
                iter = stoi(optarg);
                break;
           default:
               cerr << "Usage: " << argv[0] << " [-h] [-n proc] [-s simul] [-t iter]" << endl;
               return 1;
       }
    }

    // check if all required arguments are provided
    if (proc < 0 || simul < 0 || iter < 0) {
         cerr << "Error: All options -n, -s, and -t are required and must be positive integers." << endl;
         return 1;
    }

    cout << "Total children processes to create: " << proc << endl;
    cout << "Children processes to run simultaneously: " << simul << endl;
    cout << "Iterations each child process should run: " << iter << endl;

    // fork on oss and exec on user with arguments
    pid_t child_pid = fork();
    if (child_pid == 0){
        cout << "Child process created with PID: " << getpid() << endl;

        char *args[] = {(char *)"./user", (char *)to_string(iter).c_str(), NULL};
        int status = execvp(args[0], args);
        if (status == -1) {
            cerr << "Error executing user process." << endl;
            return 1;
        }
        
        cerr << "Execv failed." << endl;
    }
    else {
        cout << "Parent process PID: " << getpid() << " created child PID: " << child_pid << endl;
        wait(0);
        cout << "Child process with PID: " << child_pid << " has completed." << endl;
    }

    return 0;
}