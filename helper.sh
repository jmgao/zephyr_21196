#!/bin/sh
g++ helper.cpp -lhidapi-libusb -o helper -Wall -Wextra && ./helper
