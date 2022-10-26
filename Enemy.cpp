#include "Enemy.h"
#include "matWorld.h"

MatWorld* enemyMatworld = nullptr;

//�ڋ߃t�F�[�Y
void Enemy::Approach(float& appSpeed, float goal)
{
	//���̂�
	m += -appSpeed;
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_.y += appSpeed;
	//�w��̍��W�ɓ��B�����玟�t�F�[�Y��
	if (m >= 5
		&& worldTransform_.translation_.x <= 0) {
		phase_ = Enemy::Phase::MoveLeft;
		m = 0;
		if (changeFlagL == 1)//�O�̃t�F�[�Y�ŉE�ړ������Ă��Ȃ�
		{
			phase_ = Enemy::Phase::MoveRight;
			changeFlagL = 0;
			m = 0;
		}
	}
	if (m >= 5
		&& worldTransform_.translation_.x >= 0)
	{
		phase_ = Enemy::Phase::MoveRight;
		m = 0;
		if (changeFlagR == 1)//�O�̃t�F�[�Y�ō��ړ������Ă��Ȃ�
		{
			phase_ = Enemy::Phase::MoveLeft;
			changeFlagR = 0;
			m = 0;
		}
	}
}

void Enemy::MoveLeft(float& appSpeed)
{
	//���̂�
	n += appSpeed;
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_.x -= appSpeed;
	if (worldTransform_.translation_.x <= 0)
	{
		changeFlagL = 1;
	}
	if (n > 5)
	{
		phase_ = Enemy::Phase::Approach;
		n = 0;
	}
}

void Enemy::MoveRight(float& appSpeed)
{
	//���̂�
	n += appSpeed;
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_.x += appSpeed;
	if (worldTransform_.translation_.x >= 0)
	{
		changeFlagR = 1;
	}
	if (n > 5)
	{
		phase_ = Enemy::Phase::Approach;
		n = 0;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("EnemyP.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�������W���Z�b�g
	worldTransform_.translation_ = position;

	float goal = 0;

	//���x��������
	float speed = 0.05f;
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

void Enemy::UpdateW1()
{
	float speed = -0.05f;

	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_.y += speed;

	//�s��̓]��
	worldTransform_.TransferMatrix();

}
void Enemy::UpdateW2(int& left)
{
	//���x��������
	float speedY = -0.05f;
	float speedX = 0.05f;
	//�ړ��p�^�[��
	switch (phase_) {
	case Phase::Approach://�ڋ�
		Approach(speedY, 15);//15 = ��ʒ[
		break;
	case Phase::MoveLeft://���ړ�
		MoveLeft(speedX);
		break;
	default:
		MoveRight(speedX);//�E�ړ�
		break;
	}
	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//�s��̓]��
	worldTransform_.TransferMatrix();
}
void Enemy::UpdateW3()
{

}
//�Փ˔���
void Enemy::OnCollision(int& deadEnemyNum)
{
	isDead_ = true;
	deadEnemyNum += 1;
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//if (flag == 0)
	//{
		//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//}
}