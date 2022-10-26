#include "Hp.h"

MatWorld* HpMatWorld = nullptr;

void Hp::Initialize(Model* model, const Vector3& position)
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("EnemyP.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//Vector3 move = { -20,-20,0 };
	//�������W���Z�b�g
	worldTransform_.translation_ = position;

}

void Hp::Update()
{

	//�s��̌v�Z
	worldTransform_.matWorld_ = HpMatWorld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Hp::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}