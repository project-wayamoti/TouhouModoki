#include "DxLib.h"

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    // ウィンドウモード設定
    ChangeWindowMode(TRUE);

    // 画面サイズ設定
    int width = 1280;
    int height = 720;
    SetGraphMode(width, height, 32);

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }



    //## 環境に応じて設定
    // 移動物体の箱サイズ
    int size = 60;

    // 減衰値
    // ※液晶のフレームレートによって変化することがわかっているため
    // 動きが早すぎる場合やおそすぎる場合はこの数値を調整すること。
    float decay = 60 = 0.97; // 60=0.97 300=0.9925 or 0.99

    // キー入力時の移動速度
    int moveSpeed = 15;

    // 除法数値
    // ※液晶のフレームレートによって変化することがわかっているため
    // 動きが早すぎる場合やおそすぎる場合はこの数値を調整すること。
    float divisor = 0.25; // 60=0.25 300=0.01



    //## 固有の設定
    // 箱のサイズの半分を計算
    int sizeCenter = size / 2;

    // 色の設定
    unsigned int mainColor = GetColor(0, 0, 255);
    unsigned int subColor = GetColor(255, 0, 0);

    // 移動物体初期座標設定
    int x = width / 2;
    int y = height / 2;

    // 中央物体初期座標設定
    int centerX = width / 2;
    int centerY = height / 2;

    // マウス座標取得
    int mouseX = 0;
    int mouseY = 0;

    // 運動ベクタ系統格納
    int RelativeX = 0;
    int RelativeY = 0;
    float MotionX = 0;
    float MotionY = 0;

    // 当たり判定をつけたオブジェクトの格納
    bool obj = false;
    int objX = 100;
    int objY = 400;



    // メインループ（描画処理）
    while (ProcessMessage() == 0) {
        // 画面の更新
        ClearDrawScreen();



        //##### ここから 移動物体の処理
        // 中心との相対ベクターの取得
        RelativeX = centerX - x;
        RelativeY = centerY - y;

        // 加速成分を運動ベクタに累積加算
        MotionX += RelativeX * divisor;
        MotionY += RelativeY * divisor;

        // 運動ベクタを使って移動
        x += MotionX;
        y += MotionY;

        // ボールの運動ベクタを減衰させる
        MotionX *= decay;
        MotionY *= decay;



        //##### ここから 中央物体の処理
        // マウス座標の取得
        GetMousePoint(&mouseX, &mouseY);

        // マウスクリックで中心物体の座標と色を変更
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
            subColor = GetColor(0, 255, 0);
            centerX = mouseX - sizeCenter; // マウス座標は左上が原点なので、中心座標に合わせるために図形の2分の1だけ引く
            centerY = mouseY - sizeCenter;
        }
        else {
            subColor = GetColor(255, 0, 0);
        }

        // キーで移動させる
        int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        if (input & PAD_INPUT_RIGHT) {
            centerX += moveSpeed;
        }
        if (input & PAD_INPUT_LEFT) {
            centerX -= moveSpeed;
        }
        if (input & PAD_INPUT_UP) {
            centerY -= moveSpeed;
        }
        if (input & PAD_INPUT_DOWN) {
            centerY += moveSpeed;
        }

        // 中心物体は解像度外に出さない
        if (centerX < 0) {
            centerX = 0;
        }
        if (centerX > width - size) {
            centerX = width - size;
        }
        if (centerY < 0) {
            centerY = 0;
        }
        if (centerY > height - size) {
            centerY = height - size;
        }



        //##### ここから 描画処理
        // 四角を描画 DrawBox(左上X座標, 左上Y座標, 右下X座標, 右下Y座標, 色, 塗りつぶしフラグ)

        // 破壊可能なオブジェクトをまず1つだけ用意。
        // 移動物体と特定の位置に設置されたオブジェクトが触れたら色を変える
        if (x + size > objX && x < objX + (size * 3) && y + size > objY && y < objY + (size * 3)) obj = true;
        if (!obj) DrawBox(objX, objY, objX + (size * 3), objY + (size * 3), GetColor(255, 255, 255), TRUE);

        // 中心物体描画
        DrawBox(centerX, centerY, centerX + size, centerY + size, subColor, TRUE);
        // 移動物体描画
        DrawBox(x, y, x + size, y + size, mainColor, TRUE);
        // 物体の中心と中心を線で結ぶ
        DrawLine(x + sizeCenter, y + sizeCenter, centerX + sizeCenter, centerY + sizeCenter, GetColor(255, 255, 255));

        // デバッグ用
        printfDx("x:%d y:%d\n", x, y);
        printfDx("centerX:%d centerY:%d\n", centerX, centerY);
        printfDx("RelativeX:%d RelativeY:%d\n", RelativeX, RelativeY);
        printfDx("MotionX:%f MotionY:%f\n", MotionX, MotionY);

        // 画面の更新（必須）
        ScreenFlip();
        clsDx(); // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}