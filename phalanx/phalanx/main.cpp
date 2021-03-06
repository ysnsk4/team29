#include "DxLib.h"
#include"Player.h"
#include"Enemy.h"
#include"Friend.h"
#include"SceneManager.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "防衛戦線ファランクス";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;	

//int Enemy::EnemyCount;

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
	SetBackgroundColor(0, 0, 0);

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

	SceneManager* scenemanager = new SceneManager();

	Player* player = new Player(300, 300, 32, 16, 64);

	int EnemyArmy[9][8] = {
		{1,0,1,0,1,0,1,0},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,0,0,1,1,1},
		{1,1,0,0,0,0,1,1},
		{1,1,1,0,0,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{0,1,0,1,0,1,0,1}
	};

	Enemy* EnemySolder[72];
	for (int i = 0; i < 72; i++)
	{
		EnemySolder[i] =  new Enemy(32, 32, 32, 2, 10, 3, 8, 64, 0);
	}

	int EnemyNum = 0;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 8; j++)
			{

				int randamX = rand() % 16 - 8;
				int randamY = rand() % 16 - 8;
				EnemySolder[EnemyNum]->setPosX(2 * EnemySolder[EnemyNum]->getRadius() +j *3*EnemySolder[EnemyNum]->getRadius()+randamX);
				EnemySolder[EnemyNum]->setPosY(2 * EnemySolder[EnemyNum]->getRadius() +i *-3*EnemySolder[EnemyNum]->getRadius()+randamY);
				EnemySolder[EnemyNum]->setisAlive(EnemyArmy[i][j]);
				EnemyNum++;
			}
		}

	Friend* FriendSolder[64];

	for (int i = 0; i < 64; i++)
	{
		FriendSolder[i] = new Friend(0,0,32,32,200,6,5,32);
	}

	for (int i = 0; i < 8; i++)
	{
		FriendSolder[i]->setPosX(2*FriendSolder[i]->getRadius() + i * 3*FriendSolder[i]->getRadius());
		FriendSolder[i]->setPosY(400);//WIN_HEIGHT - FriendSolder[i]->getRadius()
	}

	for (int i = 8; i < 64; i++)
	{
		int randamX = rand() % 32-16;
		int randamY = rand() % 32-16;
		FriendSolder[i]->setPosX(WIN_WIDTH - 300+randamX);
		FriendSolder[i]->setPosY(WIN_HEIGHT - 100+randamY);
	}
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

		//// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//// 画面クリア
		ClearDrawScreen();
		////---------  ここからプログラムを記述  ----------//

		scenemanager->change(keys, oldkeys, player, EnemySolder, FriendSolder, MousePosX, MousePosY, MouseLeft, WIN_WIDTH, WIN_HEIGHT);
	
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
	InitGraph();
	InitSoundMem();
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}