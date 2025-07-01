#!/bin/bash

# Check network connectivity by trying to connect to google.com:80
while ! nc -zw1 google.com 80; do
  echo "No internet connection. Waiting..." >&2
  sleep 5
done

echo "Internet is up. Running http2.sh..." >&2
exec /home/esy/http2.sh

