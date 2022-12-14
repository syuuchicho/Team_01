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
	///初期化
	/// </summary>
	/// <pragma name="model">モデル</param>
	/// <pragma name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model);

	///<summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="">ビュープロジェクション</param>
	void Draw(ViewProjection& viewprjection);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	// 弾リストを取得
	const std::list < std::unique_ptr<PlayerBullet >>& GetBullets() { return bullets_; }

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突判定
	void OnCollision(int& hp);

	void ResetFlag();

	void ResetBullet();
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform hp;
	WorldTransform hp2;
	WorldTransform hp3;

	// モデル
	Model* model_ = nullptr;
	Model* modelPlayerBullet_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 入力処理するため
	Input* input_ = nullptr;
	// デバッグテキスト
	DebugText* debugText_ = nullptr;
	//弾
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	//発射フラグ
	bool shootFlag = 0;
	//タイマー
	float timer = 0;
	//軌道フラグ
	bool changeFlag = 0;
	//速度
	Vector3 velocity_;
	//弾の速度
	float kBulletSpeed_Y = 0.1f; //Yスピード
	float kBulletSpeed_X = 0.3f; //Xスピード
	//残機
	//int hp = 3;
	int sceneFlag = 0;
};