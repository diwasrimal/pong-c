#include <raylib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500
#define PADDING 10

typedef struct {
    int width;
    int height;
    int x;
    int y;
} Board;

typedef struct {
    float radius;
    int x;
    int y;
    Vector2 vec;
} Ball;

Board boardInit(void) {
    Board b;
    b.width = 50;
    b.height = 10;
    return b;
}

int main(void) {
    int count = 0;
    int dummy;

    // Movement vectors for ball
    float ballSpeed = 2;
    Vector2 up = {.x = 0, .y = -ballSpeed};
    Vector2 down = {.x = 0, .y = ballSpeed};
    Vector2 topright = {.x = ballSpeed, .y = -ballSpeed};
    Vector2 topleft = {.x = -ballSpeed, .y = -ballSpeed};
    Vector2 bottomright = {.x = ballSpeed, .y = ballSpeed};
    Vector2 bottomleft = {.x = ballSpeed, .y = -ballSpeed};

    Ball ball;
    Board topBoard = boardInit();
    Board bottomBoard = boardInit();

    ball.radius = 6;
    ball.x = WINDOW_WIDTH / 2;
    ball.y = WINDOW_HEIGHT / 2;
    ball.vec = down;

    topBoard.x = WINDOW_WIDTH / 2 - topBoard.width / 2;
    topBoard.y = PADDING;

    bottomBoard.x = WINDOW_WIDTH / 2 - bottomBoard.width / 2;
    bottomBoard.y = WINDOW_HEIGHT - PADDING - bottomBoard.height;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_A)) topBoard.x -= 2;
        if (IsKeyDown(KEY_D)) topBoard.x += 2;
        if (IsKeyDown(KEY_LEFT)) bottomBoard.x -= 2;
        if (IsKeyDown(KEY_RIGHT)) bottomBoard.x += 2;

        if (ball.y == topBoard.y + PADDING)
            ball.vec = down;
        if (ball.y == bottomBoard.y)
           ball.vec = up;

        ball.x += ball.vec.x;
        ball.y += ball.vec.y;

        DrawRectangle(topBoard.x, topBoard.y, topBoard.width, topBoard.height, RAYWHITE);
        DrawRectangle(bottomBoard.x, bottomBoard.y, bottomBoard.width, bottomBoard.height, RAYWHITE);
        DrawCircle(ball.x, ball.y, ball.radius, RAYWHITE);

        EndDrawing();
        WaitTime(0.01);
        printf("count: %d\n", count++);
    }

    CloseWindow();
    return 0;
}