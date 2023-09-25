LIBS = `pkg-config --libs raylib`
CFLAGS = `pkg-config --cflags raylib`

pong: pong.c
	clang -o pong pong.c $(CFLAGS) $(LIBS)
