#include "Player.h"

// アフィン行列呼び出し
MatWorld* playerMatworld = nullptr;

//初期化処理
void Player::Initialize(Model* model)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	//自キャラの弾モデルの生成
	modelPlayerBullet_ = Model::CreateFromOBJ("bullet", true);
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//キャラクターの移動ベクトル
	Vector3 move = { 0,-15,0 };//座標{x,y,z}

	//初期座標をセット
	worldTransform_.translation_ = move;
}

//ワールド座標を入れる変数
Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//弾と敵が当たった時のフラグの初期化
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

//衝突判定
void Player::OnCollision(int& hp)
{
	hp -= 1;
}

//プレイヤーの攻撃処理
void Player::Attack()
{
	//スペースを押したら撃つ
	if (input_->TriggerKey(DIK_SPACE)&&sceneFlag==1)
	{
		//弾の軌道
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
			//弾を生成し、初期化
			std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(modelPlayerBullet_, worldTransform_.translation_); //自キャラの座標

			//弾を登録する
			bullets_.push_back(std::move(newBullet));
			shootFlag = 1; //発射フラグ		
		}
	}


	//デバックテキスト
	debugText_->SetPos(80, 200);
	debugText_->Printf(
		"shootflag(%d)", shootFlag);
	//デバックテキスト
	debugText_->SetPos(80, 260);
	debugText_->Printf(
		"changeflag(%d)", changeFlag);

}

//アップデート
void Player::Update()
{
	//弾の位置(まっすぐ)
	velocity_.y = kBulletSpeed_Y;

	//弾の位置(右に行く)
	if (changeFlag == 1)
	{
		velocity_.x = kBulletSpeed_X;
	}
	//弾の位置(左に行く)
	if (changeFlag == 0)
	{
		velocity_.x = -kBulletSpeed_X;
	}

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//行列の計算
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();
		Attack();
		sceneFlag = 1;
	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update(velocity_, shootFlag, changeFlag);
	}
}

//描画処理
void Player::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
	// 弾の描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
}