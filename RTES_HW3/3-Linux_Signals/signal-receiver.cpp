#include <iostream>
#include <unistd.h>     // For getpid(), pause()
#include <csignal>      // For signal()
#include <map>

std::map<int, std::string> signalNames = {
    {SIGINT,  "SIGINT"},
    {SIGTERM, "SIGTERM"},
    {SIGKILL, "SIGKILL (cannot be caught)"},
    {SIGABRT, "SIGABRT"},
    {SIGFPE,  "SIGFPE"},
    {SIGHUP,  "SIGHUP"},
    {SIGQUIT, "SIGQUIT"},
    {SIGILL,  "SIGILL"},
    {SIGSEGV, "SIGSEGV"},
    {SIGUSR1, "SIGUSR1"},
    {SIGUSR2, "SIGUSR2"}
};

// Signal handler function
void handleSignal(int signal) {
    std::cout << "\nReceived signal: ";
    if (signalNames.count(signal)) {
        std::cout << signalNames[signal];
    } else {
        std::cout << "Unknown signal (" << signal << ")";
    }
    std::cout << std::endl;
}

int main() {
    pid_t pid = getpid();  // Get the process ID
    std::cout << "Process ID (PID): " << pid << std::endl;
    std::cout << "Waiting for signals..." << std::endl;

    // Register signal handlers
    for (const auto& [sig, name] : signalNames) {
        if (sig != SIGKILL) {  // SIGKILL cannot be caught or handled
            signal(sig, handleSignal);
        }
    }

    // Wait indefinitely for signals
    while (true) {
        pause();  // Suspend until a signal is received
    }

    return 0;
}

