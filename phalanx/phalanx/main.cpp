#include "DxLib.h"
#include"Player.h"
#include"Enemy.h"
#include"Friend.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "�h�q����t�@�����N�X";

// �E�B���h�E����
const int WIN_WIDTH = 1280;

// �E�B���h�E�c��
const int WIN_HEIGHT = 800;	

int Enemy::EnemyCount;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0xF0, 0xF0, 0xF0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
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
	
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 255; i++)
		{
			oldkeys[i] = keys[i];
		}
		
		oldMousePosX = MousePosX;
		oldMousePosY = MousePosY;
		oldMouseLeft = MouseLeft;

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//
		// �X�V����

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
		
		// �`�揈��
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

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();	

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}