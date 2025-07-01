#!/bin/bash

PORT=80

while true
do
	RESPONSE="HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nCurrent date and time: $(date)"
	echo -e "$RESPONSE" | nc -l -k -q 1 $PORT
done

