#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) {
		// エラーが起きたら直ちに終了
		return -1;
	}

	int image; // ハンドルを受け取るためのint型変数を宣言
	image = LoadGraph("src/images/main_character.png"); // ハンドルを代入

	// 画像の表示
	//LoadGraphScreen(0, 0, "src/images/main_character.png", TRUE);
	DrawGraph(0, 0, image, FALSE);  //画像表示

	// キー入力待ち
	WaitKey();

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了 
	return 0;
}