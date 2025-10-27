#include <stdio.h>
#include <unistd.h>
#include "cs50.h"


typedef struct ObjectStruct
{
	int x;
	int y;
	double vx;
	double vy;
} Object;

typedef struct ConfigStruct 
{
    int fps;
    int width;
    int height;
    double vx;
    double vy;
} Config;

void draw(int width, int height, char grid[height][width]);
void init(int width, int height, char grid[height][width]);
int calc(double loss, double g, double dt, Object* ball, int height, int width, char grid[height][width]);
Config input(void);
int loop(int fps, int width, int height, double initvx, double initvy);

int main(void)
{
	printf("\033[?25l");
	Config cfg = input();
    return loop(cfg.fps, cfg.width, cfg.height, cfg.vx, cfg.vy);
}

Config input(void)
{
	Config cfg;
    cfg.fps = get_int("FPS: ");
    cfg.width = get_int("Width: ");
    cfg.height = get_int("Height: ");
    cfg.vx = get_double("Initial x velocity: ");
    cfg.vy = get_double("Initial y velocity: ");
    if (cfg.width < 5) cfg.width = 5;
    if (cfg.height < 5) cfg.height = 5;
    return cfg;
}

int loop(int fps, int width, int height, double initvx, double initvy)
{
	printf("\033[2J\033[1;1H");
	int delay = (int)(1.0 / fps * 1000000);
	double dt = 0.5;
	double loss = 0.8;
	double g = 0.9;
	Object ball;
	ball.x = (width - 1) / 2;
	ball.y = (height - 1);
	ball.vx = initvx;
	ball.vy = initvy;
	char grid[height][width];
	init(width, height, grid);
	while (true)
	{
		printf("\033[H");
		int status = calc(loss, g, dt, &ball, height, width, grid);
		if (status != 0) { return 0; }
		draw(width, height, grid);
		usleep(delay);
	}
	return 0;
}

int calc(double loss, double g, double dt, Object* ball, int height, int width, char grid[height][width])
{
	init(width, height, grid);
	ball->vy = ball->vy + g * dt;
	ball->x = ball->x + ball->vx * dt;
	ball->y = ball->y + ball->vy * dt;
	if (ball->y <= 0)
	{
		ball->y = 1;
		ball->vy = (ball->vy * -1) * loss;
	}
	if (ball->y >= (height - 1))
	{
		ball->y = height - 2;
		ball->vy = (ball->vy * -1) * loss;
	}
	if (ball->x >= (width - 1))
	{
		ball->x = ball->x - 1;
		ball->vx = (ball->vx * -1) * loss;
	}
	if (ball->x <= 0)
	{
		ball->x = ball->x + 1;
		ball->vx = (ball->vx * -1) * loss;
	}
	int by = (int)ball->y;
	int bx = (int)ball->x;
	grid[by][bx] = 1;
	return 0;
}

void draw(int width, int height, char grid[height][width])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (x == 0)
			{
				printf("▓");
			}
			else if (x == (width - 1))
			{
				printf("▓");
			}
			else if (y == 0)
			{
				printf("▓");
			}
			else if (y == (height - 1))
			{
				printf("▓");
			}
			else if (grid[y][x] == 0)
			{
				printf(" ");
			}
			else
			{
				printf("");
			}
		}
		printf("\n");
	}
}

void init(int width, int height, char grid[height][width])
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			grid[y][x] = 0;
		}
	}
}
