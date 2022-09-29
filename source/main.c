#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

typedef struct {
	float x, y; // position
	float dx, dy; // velocity
	int width, height;
	u32 color;
} Player;

typedef struct {
	float x, y; // position
	float dx, dy; // velocity
	int width, height;
} Obstacle;

int main(int argc, char* argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	C3D_RenderTarget* topScreen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	u32 obstacleCornerColor = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
	u32 clearColor = C2D_Color32(0x33, 0x33, 0x33, 0x68);
	Player player = {
		.x = 20,
		.y = SCREEN_HEIGHT - 50,
		.dx = 0,
		.dy = 0,
		.width = 50,
		.height = 50,
		.color = C2D_Color32(0x00, 0xFF, 0x00, 0xFF)
	};

	// colisao com obstacle
	// cima -> y + height
	// baixo
	// esquerda
	// direita

	// entre x e x + width
	// entre y e y + height

	Obstacle obstacle = {
		.x = SCREEN_WIDTH,
		.y = SCREEN_HEIGHT - 30,
		.dx = -2,
		.dy = 0,
		.width = 30,
		.height = 30
	};

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		// u32 kHeld = hidKeysHeld();
		// u32 kUp = hidKeysUp();

		if (kDown == KEY_DUP && player.y == SCREEN_HEIGHT - player.height) {
			int JUMP_SPEED = -10;
			player.dy = JUMP_SPEED;
		}

		// if (kUp == KEY_DLEFT || kUp == KEY_DRIGHT) {
		// 	player.dx = 0;
		// }

		// if (kUp == KEY_DUP || kUp == KEY_DDOWN) {
		// 	player.dy = 0;
		// }

		// if (kHeld & KEY_DUP || kDown & KEY_DUP) {
		// 	if(player.y <= 0) { // prevent the player from escaping the screen
		// 		player.dy = 0;
		// 		player.y = 0;
		// 	} else if(player.dy != -player.maxVelocity) {
		// 		player.dy -= 0.2;
		// 	} 
		// }

		// if (kHeld & KEY_DDOWN || kDown & KEY_DDOWN) {
		// 	if(player.y >= SCREEN_HEIGHT - player.height) {
		// 		player.dy = 0;
		// 		player.y = SCREEN_HEIGHT - player.height;
		// 	} else if(player.dy != player.maxVelocity) {
		// 		player.dy += 0.2;
		// 	}
		// }

		// if (kHeld & KEY_DLEFT || kDown & KEY_DLEFT) {
		// 	if(player.x <= 0) { // prevent the player from escaping the screen
		// 		player.dx = 0;
		// 		player.x = 0;
		// 	} else if(player.dx != -player.maxVelocity) {
		// 		player.dx -= 0.2;
		// 	} 
		// }

		// if (kHeld & KEY_DRIGHT || kDown & KEY_DRIGHT) {
		// 	if(player.x >= SCREEN_WIDTH - player.width) {
		// 		player.dx = 0;
		// 		player.x = SCREEN_WIDTH - player.width;
		// 	} else if(player.dx != player.maxVelocity) {
		// 		player.dx += 0.2;
		// 	}
		// }

		// player.x = player.x + player.dx;
		player.y = player.y + player.dy;
		obstacle.x = obstacle.x + obstacle.dx;
		
		if(player.y != SCREEN_HEIGHT - player.height) {
			player.dy += 0.5;
		}

		if(player.y > SCREEN_HEIGHT - player.height) {
			player.y = SCREEN_HEIGHT - player.height;
		}

		bool colision = false;
		float playerBottom = player.y + player.height;
		float playerRight = player.x + player.width;
		float obstacleTop = obstacle.y;
		float obstacleLeft = obstacle.x;

		if(playerBottom >= obstacleTop && playerRight >= obstacleLeft) {
			colision = true;
		} 

		if(colision) {
			player.color = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
		} else {
			player.color = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
		}

		if(obstacle.x < -obstacle.width) {
			obstacle.dx += obstacle.dx*5/100;
			obstacle.x = SCREEN_WIDTH + 20;
		}


		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(topScreen, clearColor);
		C2D_SceneBegin(topScreen);
		C2D_DrawRectangle(player.x, player.y, 0, player.width, player.height, player.color, player.color, player.color, player.color);
		C2D_DrawRectangle(obstacle.x, obstacle.y, 0, obstacle.width, obstacle.height, obstacleCornerColor, obstacleCornerColor, obstacleCornerColor, obstacleCornerColor);
		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}

