#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// �c�w���C�u��������������
	if (DxLib_Init() == -1) {
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	int image; // �n���h�����󂯎�邽�߂�int�^�ϐ���錾
	image = LoadGraph("src/images/main_character.png"); // �n���h������

	// �摜�̕\��
	//LoadGraphScreen(0, 0, "src/images/main_character.png", TRUE);
	DrawGraph(0, 0, image, FALSE);  //�摜�\��

	// �L�[���͑҂�
	WaitKey();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I�� 
	return 0;
}