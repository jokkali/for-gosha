#include <iostream>
#include "raylib.h"

#define WINDOW_X 1920
#define WINDOW_Y 1080

float GetVLen(float X, float Y) {
	float Path = sqrt((X * X) + (Y * Y));
	return Path;
}
Vector2 Scal(float X, float Y, float scal) {
	Vector2 Res = { (X * scal), (Y * scal) };
	return Res;
}
float Scal(float X, float Y, float scalX, float scalY) {
	float Res = (X * scalX) + (Y * scalY);
	return Res;
}
Vector2 normalize(Vector2 V1) {
	Vector2 v2 = Scal(V1.x, V1.y, (1 / GetVLen(V1.x, V1.y)));
	return v2;
}
int main() {
	
	InitWindow(WINDOW_X, WINDOW_Y, "Chasing Ball");
	SetTargetFPS(90);
	
	float k = 1;
	
	float BallRadius = 5.f;

	Texture2D Baka = LoadTexture("baka.png");

	Vector2 BufferVec = { 0,0 };
	Vector2 BallCenter = { 0.f,0.f };
	Vector2 MouseCoord = { WINDOW_X - 1, WINDOW_Y - 1 };
	Vector2 ToMouse = { normalize(MouseCoord) };

	SetMousePosition(WINDOW_X - 1, WINDOW_Y - 1);
	ToggleFullscreen();
	
	while (!WindowShouldClose())
	{
		
		BeginDrawing();
		ClearBackground({ 0,0,0,255 });
		DrawTextureEx(Baka, { BallCenter.x - 50,BallCenter.y - 50 }, 0, 0.1, WHITE);
		DrawCircleV(BallCenter, BallRadius, RED);
		
		

		EndDrawing();
		if ((abs(MouseCoord.x - BallCenter.x) > 0.1) || (abs(MouseCoord.y - BallCenter.y) > 0.1)) {
			MouseCoord = GetMousePosition();
			BufferVec = { MouseCoord.x - BallCenter.x, MouseCoord.y - BallCenter.y };
			ToMouse = { normalize(BufferVec) };
			BallCenter.x += ToMouse.x * k;
			BallCenter.y += ToMouse.y * k;
		
		}
		else {
			BeginDrawing();
			DrawText("CATCHED!", WINDOW_X / 2, WINDOW_Y / 2, 50, RED);
			EndDrawing();
			UnloadTexture(Baka);
			CloseWindow();
			for (;;);
		}
	}
}