#pragma once

#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
#include"matWorld.h"
#include"player.h"

class Enemy
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	//�Փ˔���
	void OnCollision();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;
	//�f�X�t���O
	bool isDead_ = false;
	
};