#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "matWorld.h"
#include "DebugText.h"

class PlayerBullet {
public:

	void Initialize(Model* model, const Vector3& position);

	void Update(Vector3& velocity, bool& shootFlag, bool& changeFlag);

	void Draw(const ViewProjection& viewProjection);

	//�Փ˔���
	void OnCollision();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

private:

	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	// ���x
	Vector3 velocity_;

	//�f�X�t���O
	bool isDead_ = false;

};