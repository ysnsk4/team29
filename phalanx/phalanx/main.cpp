#include "DxLib.h"
#include"Player.h"
#include"Enemy.h"
#include"Friend.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "防衛戦線ファランクス";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;	

int Enemy::EnemyCount;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0xF0, 0xF0, 0xF0);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	int PlayerPosX = WIN_WIDTH / 2;
	int PlayerPosY = WIN_HEIGHT / 2;
	int PlayerR = 32;
	int PlayerSpeed = 4;
	int EnemyCountNum = 0;

	int MousePosX = 0;
	int MousePosY = 0;
	int MouseLeft = 0;
	int oldMousePosX;
	int oldMousePosY;
	int oldMouseLeft;

	Player* player = new Player(300, 300, 32, 16, 64);

	int EnemyArmy[9][9] = {
		{1,0,1,0,1,0,1,0,1},
		{1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1},
		{1,1,1,0,0,0,1,1,1},
		{1,1,0,0,1,0,0,1,1},
		{1,1,1,0,0,0,1,1,1},
		{1,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,1,1,1,1},
		{0,1,0,1,0,1,0,1,0}
	};

	Enemy* EnemySolder[81];
	for (int i = 0; i < 81; i++)
	{
		EnemySolder[i] =  new Enemy(32, 32, 32, 8, 10, 3, 8, 64, 0);
	}

	int EnemyNum = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				EnemySolder[EnemyNum]->setPosX(2 * EnemySolder[EnemyNum]->getRadius() +j *3*EnemySolder[EnemyNum]->getRadius());
				EnemySolder[EnemyNum]->setPosY(2 * EnemySolder[EnemyNum]->getRadius() +i *-3*EnemySolder[EnemyNum]->getRadius());
				EnemySolder[EnemyNum]->setisAlive(EnemyArmy[i][j]);
				EnemyNum++;
			}
		}

	Friend* FriendSolder[9];
	
	for (int i = 0; i < 9; i++)
	{
		FriendSolder[i] = new Friend(0,0,32,32,10,6,5,32);
	}

	for (int i = 0; i < 8; i++)
	{
		FriendSolder[i]->setPosX(2*FriendSolder[i]->getRadius() + i * 3*FriendSolder[i]->getRadius());
		FriendSolder[i]->setPosY(WIN_HEIGHT - FriendSolder[i]->getRadius());
	}

	FriendSolder[8]->setPosX(WIN_WIDTH - 300);
	FriendSolder[8]->setPosY(WIN_HEIGHT - 100);
	
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 255; i++)
		{
			oldkeys[i] = keys[i];
		}
		
		oldMousePosX = MousePosX;
		oldMousePosY = MousePosY;
		oldMouseLeft = MouseLeft;

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		// 更新処理

		GetMousePoint(&MousePosX, &MousePosY);
		GetMouseInput();
		MouseLeft = MOUSE_INPUT_LEFT;

		player->move(keys, WIN_WIDTH, WIN_HEIGHT);

		player->grabFriend(FriendSolder);
		
		/*if(GetMouseInput()&&MOUSE_INPUT_LEFT!=0)
		{
		}*/
		for (int i = 0; i < 9; i++)
		{	
			FriendSolder[i]->update(EnemySolder);
		}

		for (int i = 0; i < 81; i++)
		{
			EnemySolder[i]->update(FriendSolder);
		}
		
		// 描画処理
		DrawBox(WIN_WIDTH - 400, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 255, 200), true);
		for (int i = 0; i < 81; i++)
		{
			EnemySolder[i]->draw();
		}
		for (int i = 0; i < 9; i++) {
			FriendSolder[i]->draw();
		}
		/*if (
			(FriendSolder[8]->getPosX() - MousePosX) * (FriendSolder[8]->getPosX() - MousePosX) + (FriendSolder[8]->getPosY() - MousePosY) * (FriendSolder[8]->getPosY() - MousePosY)
			<= FriendSolder[8]->getRadius()* FriendSolder[8]->getRadius()
		)
		{
			DrawFormatString(5, 5, GetColor(0, 200, 0), "grab now");
		}
		else
		{
			DrawFormatString(5, 5, GetColor(100, 0, 0), "free hand");
		}*/
		player->draw();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();	

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}