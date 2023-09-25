#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define W_WIDTH 800     // Window
#define W_HEIGHT 500
#define B_WIDTH 50      // Board
#define B_HEIGHT 10
#define PADDING 10

typedef struct {
    int x;
    int y;
} Board;

typedef struct {
    float radius;
    int x;
    int y;
    Vector2 vec;
} Ball;

Ball initBall(void);
Board initTopBoard(void);
Board initBottomBoard(void);

int main(void) {
    Ball ball;
    Board topBoard, bottomBoard;
    double waitTime;

    ball = initBall();
    topBoard = initTopBoard();
    bottomBoard = initBottomBoard();
    waitTime = 0.006;

    InitWindow(W_WIDTH, W_HEIGHT, "Pong");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Board control
        if (IsKeyDown(KEY_A)) topBoard.x -= 2;
        if (IsKeyDown(KEY_D)) topBoard.x += 2;
        if (IsKeyDown(KEY_LEFT)) bottomBoard.x -= 2;
        if (IsKeyDown(KEY_RIGHT)) bottomBoard.x += 2;

        // Restart
        if (IsKeyDown(KEY_R)) {
            ball = initBall();
            topBoard = initTopBoard();
            bottomBoard = initBottomBoard();
            waitTime = 0.006;
        }

        // Handle rebound directions, speed up after rebound
        bool hitsTop = ball.y == topBoard.y + B_HEIGHT && (topBoard.x <= ball.x && ball.x <= topBoard.x + B_WIDTH);
        bool hitsBottom = ball.y == bottomBoard.y && (bottomBoard.x <= ball.x && ball.x <= bottomBoard.x + B_WIDTH);
        bool hitsLeft = 0 + ball.radius == ball.x;
        bool hitsRight = ball.x + ball.radius == W_WIDTH;

        if (hitsTop || hitsBottom) {
            waitTime -= 0.0001;
            ball.vec.y = -ball.vec.y;
        }

        if (hitsLeft || hitsRight) {
            waitTime -= 0.0001;
            ball.vec.x = -ball.vec.x;
        }

        // Update ball position
        ball.x += ball.vec.x;
        ball.y += ball.vec.y;
        printf("ball.x: %d, ball.y: %d\n", ball.x, ball.y);
        printf("ball.vec.x: %f, ball.vec.y: %f\n\n", ball.vec.x, ball.vec.y);

        DrawRectangle(topBoard.x, topBoard.y, B_WIDTH, B_HEIGHT, RAYWHITE);
        DrawRectangle(bottomBoard.x, bottomBoard.y, B_WIDTH, B_HEIGHT, RAYWHITE);
        DrawCircle(ball.x, ball.y, ball.radius, GOLD);

        EndDrawing();
        WaitTime(waitTime);
    }

    CloseWindow();
    return 0;
}

Board initTopBoard(void)
{
    Board b;
    b.x = W_WIDTH / 2 - B_WIDTH / 2;
    b.y = PADDING;
    return b;
}

Board initBottomBoard(void)
{
    Board b;
    b.x = W_WIDTH / 2 - B_WIDTH / 2;
    b.y = W_HEIGHT - PADDING - B_HEIGHT;
    return b;
}

Ball initBall(void)
{
    Ball ball;
    ball.radius = 6;
    ball.x = W_WIDTH / 2;
    ball.y = W_HEIGHT / 2;
    ball.vec.x = 1;
    ball.vec.y = 1;
    return ball;
}