#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "matWorld.h"
#include <assert.h>
#include<memory>
#include<list>
#include "playerBullet.h"

class Player
{
public:
	///<summary>
	///������
	/// </summary>
	/// <pragma name="model">���f��</param>
	/// <pragma name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, const Vector3& position);

	///<summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="">�r���[�v���W�F�N�V����</param>
	void Draw(ViewProjection& viewprjection);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	// �e���X�g���擾
	const std::list < std::unique_ptr<PlayerBullet >>& GetBullets() { return bullets_; }

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˔���
	void OnCollision();

	void ResetFlag();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏������邽��
	Input* input_ = nullptr;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	//�e
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	//���˃t���O
	bool shootFlag = 0;
	//�^�C�}�[
	float timer = 0;
	//�O���t���O
	bool changeFlag = 0;
	//���x
	Vector3 velocity_;
	//�e�̑��x
	float kBulletSpeed_Y = 0.1f; //Y�X�s�[�h
	float kBulletSpeed_X = 0.3f; //X�X�s�[�h
	//�c�@
	int hp = 3;
};