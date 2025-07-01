#!/bin/bash

FIFO_PATH="/home/esy/fifo/FIFO"

# Create the FIFO if it doesn't exist
if [[ ! -p $FIFO_PATH ]]; then
    mkfifo $FIFO_PATH
fi

echo "Receiver is waiting for messages..."
while true; do
    if read line < $FIFO_PATH; then
        echo "Received: $line"
    fi
done

