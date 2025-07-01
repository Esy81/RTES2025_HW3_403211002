#include <iostream>
#include <csignal>
#include <map>
#include <string>
#include <unistd.h>  // For pid_t and kill()
#include <cstdlib>   // For exit()

int main() {
    std::map<int, std::string> signals = {
        {SIGINT,  "SIGINT  - Interrupt from keyboard (Ctrl+C)"},
        {SIGTERM, "SIGTERM - Termination signal"},
        {SIGKILL, "SIGKILL - Force kill (cannot be caught)"},
        {SIGABRT, "SIGABRT - Abnormal termination"},
        {SIGFPE,  "SIGFPE  - Floating-point exception"},
        {SIGHUP,  "SIGHUP  - Hangup detected"},
        {SIGQUIT, "SIGQUIT - Quit from keyboard"},
        {SIGILL,  "SIGILL  - Illegal instruction"},
        {SIGUSR1, "SIGUSR1 - User-defined signal 1"}
    };

    pid_t pid;
    int sig_id;

    while (true)
    {

    	std::cout << "Enter the process ID: ";
    	std::cin >> pid;

    	std::cout << "\nAvailable Signals:\n";
    	for (const auto& pair : signals) {
        	std::cout << pair.first << " -> " << pair.second << '\n';
    	}

    	std::cout << "\nEnter the signal number to send: ";
    	std::cin >> sig_id;

    	if (signals.find(sig_id) == signals.end()) {
        	std::cerr << "Invalid signal ID.\n";
    	}

    	if (kill(pid, sig_id) == 0) {
        	std::cout << "Signal " << sig_id << " sent successfully to process " << pid << ".\n";
    	} else {
        	perror("Failed to send signal");
    	}
   }

    return 0;
}
