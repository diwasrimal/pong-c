#!/bin/sh

set -xe

cc -o pong pong.c $(pkg-config --cflags --libs raylib)