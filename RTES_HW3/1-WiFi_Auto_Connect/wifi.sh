#!/bin/bash

# Configuration
SSID="Esy"
WIFI_PASSWORD="13811381"
INTERFACE="wlan0"
LOGFILE="/var/log/auto-connect.log"  # Absolute path for cron

# Commands
nmcli device >> "$LOGFILE" 2>&1
nmcli radio wifi on >> "$LOGFILE" 2>&1
nmcli device wifi connect "$SSID" password "$WIFI_PASSWORD" >> "$LOGFILE" 2>&1
