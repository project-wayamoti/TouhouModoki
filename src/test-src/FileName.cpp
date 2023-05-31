#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) {
		// エラーが起きたら直ちに終了
		return -1;
	}

	// 点を打つ
	DrawPixel(320, 240, GetColor(255, 255, 255));

	// キー入力待ち
	WaitKey();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了 
	return 0;
}