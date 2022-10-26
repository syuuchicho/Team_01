#include "Player.h"

// �A�t�B���s��Ăяo��
MatWorld* playerMatworld = nullptr;

//����������
void Player::Initialize(Model* model, const Vector3& position)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,-15,0 };//���W{x,y,z}

	//�������W���Z�b�g
	worldTransform_.translation_ = move;
}

//���[���h���W������ϐ�
Vector3 Player::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//�e�ƓG�������������̃t���O�̏�����
void Player::ResetFlag()
{
	shootFlag = 0;
	changeFlag = 0;
}

void Player::ResetBullet()
{
	sceneFlag = 0;
	shootFlag = 0;
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->OnCollision();
	}
}

//�Փ˔���
void Player::OnCollision(int& hp)
{
	hp -= 1;
}

//�v���C���[�̍U������
void Player::Attack()
{
	//�X�y�[�X���������猂��
	if (input_->TriggerKey(DIK_SPACE)&&sceneFlag==1)
	{
		//�e�̋O��
		if (changeFlag == 0)
		{
			changeFlag = 1;
		}
		else if (changeFlag == 1)
		{
			changeFlag = 0;
		}
		if (shootFlag == 0)
		{
			//�e�𐶐����A������
			std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(model_, worldTransform_.translation_); //���L�����̍��W

			//�e��o�^����
			bullets_.push_back(std::move(newBullet));
			shootFlag = 1; //���˃t���O		
		}
	}


	//�f�o�b�N�e�L�X�g
	debugText_->SetPos(80, 200);
	debugText_->Printf(
		"shootflag(%d)", shootFlag);
	//�f�o�b�N�e�L�X�g
	debugText_->SetPos(80, 260);
	debugText_->Printf(
		"changeflag(%d)", changeFlag);

}

//�A�b�v�f�[�g
void Player::Update()
{
	//�e�̈ʒu(�܂�����)
	velocity_.y = kBulletSpeed_Y;

	//�e�̈ʒu(�E�ɍs��)
	if (changeFlag == 1)
	{
		velocity_.x = kBulletSpeed_X;
	}
	//�e�̈ʒu(���ɍs��)
	if (changeFlag == 0)
	{
		velocity_.x = -kBulletSpeed_X;
	}

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();
		Attack();
		sceneFlag = 1;
	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update(velocity_, shootFlag, changeFlag);
	}
}

//�`�揈��
void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// �e�̕`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
}