#!/bin/bash

# Configuration
SSID="Esy"
PASSWORD="13811381"
INTERFACE="wlan0"
LOGFILE="/home/esy/auto-connect.log"
SCRIPT_PATH="/home/esy/wifi2.sh"
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

# Step 1: Check if script is already in crontab
crontab -l 2>/dev/null | grep -F "$SCRIPT_PATH" > /dev/null

if [ $? -ne 0 ]; then
    # Add the script to crontab to run every minute and on reboot
    (crontab -l 2>/dev/null; echo "* * * * * $SCRIPT_PATH"; echo "@reboot $SCRIPT_PATH") | crontab -
    echo "Cron job added for $SCRIPT_PATH"
fi

# Ensure Wi-Fi radio is on
nmcli radio wifi on

# Log current Wi-Fi status
echo "[$TIMESTAMP] Checking connection status..." >> "$LOGFILE"
nmcli -t -f ACTIVE,SSID dev wifi | grep '^yes' > /dev/null

if [ $? -ne 0 ]; then
    echo "[$TIMESTAMP] ❌ Not connected. Attempting to connect to $SSID..." >> "$LOGFILE"
    nmcli device wifi connect "$SSID" password "$PASSWORD" >> "$LOGFILE" 2>&1

    if [ $? -eq 0 ]; then
        echo "[$TIMESTAMP] ✅ Connected to $SSID." >> "$LOGFILE"
    else
        echo "[$TIMESTAMP] ❌ Failed to connect to $SSID." >> "$LOGFILE"
    fi
else
    echo "[$TIMESTAMP] ✅ Already connected to a network." >> "$LOGFILE"
fi

# Log list of available networks
echo "[$TIMESTAMP] 📡 Available Wi-Fi networks:" >> "$LOGFILE"
nmcli device wifi list >> "$LOGFILE" 2>&1
echo "----------------------------------------------------" >> "$LOGFILE"

