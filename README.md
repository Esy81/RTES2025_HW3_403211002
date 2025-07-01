# RTES2025_HW3_403211002
# 📚 Embedded Linux Exercise 3 – OrangePi Zero 2 Plus

This repository contains the solutions for Exercise 3 of the Embedded Linux course, focused on using the **OrangePi Zero 2 Plus** board. The tasks include automatic Wi-Fi setup, IPC mechanisms, and a basic web server implementation.

---

## 📦 Submission Contents

Ensure your final ZIP file is named: `RTES2025_HW3_{student_number}.zip`  
**Example**: `RTES2025_HW3_401234567.zip`

Directory structure inside the ZIP:

```
RTES2025_HW3_401234567/
├── HW3.mp4           # Video recorded with phone camera (not screen recording)
├── repolink.txt      # Contains the GitHub repo URL (one line only)
└── RTES2025_HW3/     # The actual GitHub repository
    ├── auto-wifi-connect/
    ├── ipc/
    ├── webserver/
    └── README.md     # This file with answers
```

---

## 🛠️ 1. Board Setup

OrangePi Zero 2 Plus was configured using the instructional video. The board successfully booted into Linux, and I gained access through SSH.

---

## 🌐 2. Wi-Fi and SSH Setup

- Created a 2.4 GHz Wi-Fi hotspot via mobile.
- Used `nmcli` to connect the board to the network.
- Accessed the board via SSH using:
  - **VS Code Remote – SSH extension** for development
  - Or **PuTTY** as an alternative SSH client

---

## 📂 3. Git Repository Usage

- Cloned the starter GitHub repository using SSH:
  ```bash
  git clone git@github.com:myusername/RTES2025_HW3.git
  ```
- Committed and pushed all completed scripts and code to the repo.

---

## 📡 4. Automatic Wi-Fi Connection

Created a shell script (`auto-connect.sh`) that:
- Checks Wi-Fi connection status
- If not connected, attempts to reconnect using `nmcli`
- Logs output to `auto-connect.log`

### 🕒 Scheduled Execution:
- **Every minute** using a cron job:
  ```bash
  * * * * * /path/to/auto-connect.sh
  ```
- **At boot** using:
  ```bash
  @reboot /path/to/auto-connect.sh
  ```

📁 **Location**: `auto-wifi-connect/`

---

## 🔗 5. Inter-Process Communication (IPC)

### 📥📤 5.1 FIFO

Implemented:
- `fifo-sender.sh`: Writes input to FIFO
- `fifo-receiver.sh`: Reads from FIFO and prints input

✔ FIFO is created if it doesn’t exist.

📁 **Location**: `ipc/fifo/`

---

### ⚡ 5.2 Linux Signals

#### Programs:
- `signal-receiver.cpp`: 
  - Prints PID
  - Waits for incoming signals
  - Logs received signals to a file
- `signal-sender.cpp`:
  - Takes PID and signal number as input
  - Sends signal to target process

📁 **Location**: `ipc/signals/`

#### ❓ Answers:

- **What is the difference between SIGINT and SIGKILL?**
  - `SIGINT` (signal 2) can be caught or ignored by a process. It is typically sent when the user presses `Ctrl+C`.
  - `SIGKILL` (signal 9) cannot be caught or ignored. It forcefully terminates the process.

- **Which signals can be caught or handled by a process?**
  - All signals except `SIGKILL` and `SIGSTOP` can be caught and handled.

- **How many signals are defined in Linux?**
  - Linux defines **64 signals** (numbered 1 to 64), though the exact number may vary by system.

---

### 🗄️ 5.3 Shared Memory

#### Programs:
- `shm-writer.cpp`: Writes user input into a 10-character circular buffer using shared memory.
- `shm-reader.cpp`: Reads the current contents of the buffer.

📁 **Location**: `ipc/shared-memory/`

#### ❓ Answer:

- **What are the key differences between FIFO and shared memory for IPC?**

  | Feature         | FIFO                          | Shared Memory                        |
  |-----------------|-------------------------------|--------------------------------------|
  | Communication   | Unidirectional (by default)   | Bidirectional (with sync)            |
  | Speed           | Slower                        | Faster                               |
  | Storage         | Kernel-managed pipe file      | Memory segment shared between processes |
  | Synchronization | Not required (stream-based)   | Required (e.g., semaphores)          |

---

## 🌍 6. Basic Web Server

Created a shell script (`webserver.sh`) that:
- Listens on **port 80** using `nc` (netcat)
- Responds with the current **date and time**
- Also prints the response to the terminal

### 🧩 systemd Service (`webserver.service`)
Configured a service file that:
- Starts **after the network is online**
- Restarts **automatically** on failure (5-second delay)
- Logs output to the **system journal**
- Runs **at boot**

📝 Service file is placed after the script in both the repository and ZIP submission.

📁 **Location**: `webserver/`

---

## 🔗 7. References

- OrangePi Wiki: http://www.orangepi.org/orangepiwiki/
- nmcli Documentation: https://networkmanager.dev/docs/api/latest/nmcli.html
- Git SCM Docs: https://git-scm.com/doc
- Systemd Services: https://www.freedesktop.org/software/systemd/man/systemd.service.html
- Beej’s Guide to IPC: https://beej.us/guide/bgipc/
- Netcat Manual: http://nc110.sourceforge.net/

---

✅ All tasks completed and tested.  
🎥 Demonstration video provided in `HW3.mp4`.  
🔗 GitHub repository link provided in `repolink.txt`.

Happy coding! 🚀
