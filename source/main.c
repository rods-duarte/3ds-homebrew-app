#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

int main(int argc, char* argv[])
{
	// Init libs
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	C3D_RenderTarget* topScreen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	u32 squareCornerColor = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clearColor = C2D_Color32(0x33, 0x33, 0x33, 0x68);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; 
		printf("\x1b[2;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[3;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
		printf("\x1b[4;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(topScreen, clearColor);
		C2D_SceneBegin(topScreen);
		C2D_DrawRectangle(SCREEN_WIDTH - 50, 0, 0, 50, 50, squareCornerColor, squareCornerColor, squareCornerColor, squareCornerColor);
		C3D_FrameEnd(0);
	}

	// Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
