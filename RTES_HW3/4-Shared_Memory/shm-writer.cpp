#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

string make_costum_string(const string& buffer, int i) {
    // Use substr to extract substring from index i to j
    string s1 = buffer.substr(10 - i, 10);
    string s2 = buffer.substr(0, 10 - i);
    return (s1 + s2);
}

int main() {
    // Generate a unique key
    key_t key = 1234;
    if (key == -1) {
        std::cerr << "Failed to generate key\n";
        return 1;
    }

    // Create shared memory segment of size 1024 bytes
    int shmid = shmget(key, 10, 0666 | IPC_CREAT);
    if (shmid == -1) {
        std::cerr << "Failed to create shared memory\n";
        return 1;
    }

    // Attach shared memory segment to sender's address space
    char *str = (char*) shmat(shmid, nullptr, 0);
    if (str == (char*) -1) {
        std::cerr << "Failed to attach shared memory\n";
        return 1;
    }

    string data_in, buffer;
    int len;

    while (true) {
	cin >> data_in;
        buffer += data_in;
        len = buffer.length();
        if (len > 10)
        {
            buffer = make_costum_string(buffer.substr(buffer.length() - 10, buffer.length()), len % 10);
        }
        cout << buffer << '\n';
	
	// Copy message into shared memory
    	std::strcpy(str, buffer.c_str());

	std::cout << "Data written to shared memory: " << buffer << std::endl;
    }

    // Detach shared memory
    if (shmdt(str) == -1) {
        std::cerr << "Failed to detach shared memory\n";
        return 1;
    }

    return 0;
}
