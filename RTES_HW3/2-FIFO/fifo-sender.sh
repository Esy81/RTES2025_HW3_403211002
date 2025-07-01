#!/bin/bash

FIFO_PATH="/home/esy/fifo/FIFO"

# Ensure FIFO exists
if [[ ! -p $FIFO_PATH ]]; then
    echo "FIFO does not exist. Please start the receiver first."
    exit 1
fi

while true
do
	# Read input from the user and send it to FIFO
	read -p "Enter message to send: " message
	echo "$message" > $FIFO_PATH
done

