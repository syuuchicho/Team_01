#pragma once

#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
#include"matWorld.h"
#include"player.h"

class Enemy
{
public:

	//�s���t�F�[�Y
	enum class Phase
	{
		Approach,	//�ڋ߂���
		MoveLeft,	//���ړ�
		MoveRight,	//�E�ړ�
		MoveLeft2,	//���ړ�
		MoveRight2,	//�E�ړ�
		Leave,		//���E����
	};

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void UpdateW1();
	void UpdateW2(int&left);
	void UpdateW3();

	//�ڋ�
	void Approach(float& appSpeed, float goal);

	//���ړ�
	void MoveLeft(float& appSpeed);

	//�E�ړ�
	void MoveRight(float& appSpeed);

	//���ړ�
	void MoveLeft2(float& appSpeed);

	//�E�ړ�
	void MoveRight2(float& appSpeed);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	//�Փ˔���
	void OnCollision(int& deadEnemyNum);

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	//�G�̔ԍ����擾
	int GetEnemyNum();

	bool IsDead() const { return isDead_; }
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
	//���x
	Vector3 velocity_;
	
	//���̂�
	float m = 0;
	float n = 0;
	float m2 = 0;
	float n2 = 0;
	int count = 5;
	int count2 = 5;
	float time = 0.5f;
	float time2 = 0.5f;
	int timer = 120;

	//���x��������
	float speedY = -0.05f;
	float speedX = 0.05f;
	float speedX2 = 0.03f;



	bool changeFlagL = 0;
	bool changeFlagR = 0;
	//�f�X�t���O
	bool isDead_ = false;
	//�ړI�n
	float goal = 0;
};