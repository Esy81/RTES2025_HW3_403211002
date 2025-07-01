#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>

int main() {
    // Generate the same key
    key_t key = 1234;
    if (key == -1) {
        std::cerr << "Failed to generate key\n";
        return 1;
    }

    // Locate the shared memory segment
    int shmid = shmget(key, 10, 0666);
    if (shmid == -1) {
        std::cerr << "Failed to find shared memory\n";
        return 1;
    }

    // Attach the shared memory segment to receiver's address space
    char *str = (char*) shmat(shmid, nullptr, 0);
    if (str == (char*) -1) {
        std::cerr << "Failed to attach shared memory\n";
        return 1;
    }

    // Read and print the data from shared memory
    std::cout << "Data read from shared memory: " << str << std::endl;

    // Detach shared memory
    if (shmdt(str) == -1) {
        std::cerr << "Failed to detach shared memory\n";
        return 1;
    }

    // Optional: Remove the shared memory segment
    //if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
        //std::cerr << "Failed to remove shared memory\n";
        //return 1;
    //}

    return 0;
}
