#include "Enemy.h"
#include "matWorld.h"

MatWorld* enemyMatworld = nullptr;

void Enemy::Initialize(Model* model, const Vector3& position) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("EnemyP.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,20,0 }; //���W{x,y,z}

	//�������W���Z�b�g
	worldTransform_.translation_ = position;
}

Vector3 Enemy::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Update()
{
	float speed = 0.05f;

	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_.y -= speed;

	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�Փ˔���
void Enemy::OnCollision()
{
	isDead_ = true;
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//if (flag == 0)
	//{
		//���f���̕`��
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//}
}