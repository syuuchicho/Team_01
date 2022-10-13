#pragma once
#include"Model.h"
#include"matWorld.h"
#include"assert.h"

/// <summary>
/// �V��
/// </summary>
class Skydome
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model*model);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���f��
	Model* model_ = nullptr;
	
};
