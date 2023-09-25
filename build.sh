#!/bin/sh

set -xe

clang -o pong pong.c $(pkg-config --cflags --libs raylib)