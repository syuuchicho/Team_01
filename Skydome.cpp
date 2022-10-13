#include"Skydome.h"

void Skydome::Initialize(Model* model)
{
	model_ = model;
	
	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
}

void Skydome::Update()
{

}

void Skydome::Draw()
{
	//3D���f���̕`��
	model_->Draw(worldTransform_, viewProjection_);
}