#include "Stage.h"
#include "../object/Player.h"
#include "../object/Star.h"
#include "../Load.h"
#include "../object/enemy/smallenemy/NormalEnemy.h"
#include "../Collision.h"
#include "../object/Bullet.h"



const int STAR_NUM = 80;

CStage::CStage(Random &random){
	m_player = std::make_unique<CPlayer>();
	for (u_int i = 0; i < STAR_NUM; i++){
		m_star.emplace_back(std::make_unique<CStar>(random));
	}
	CLoad::stage_bgm[0]->looping(true);
	CLoad::stage_bgm[0]->play();
	count = 0;
}

CStage::~CStage(){
	CLoad::stage_bgm[0]->stop();
}

void CStage::Update(AppEnv &app_env,Random &random){
	count++;
	for (auto &Star : m_star){
		Star->Update(app_env, random);
	}
	for (auto &Enemy : m_enemy){
		Enemy->Update(app_env, random);
	}
	m_player->Update(app_env,random);
	CreateEnemy();
	Collision();
	if (app_env.isPushKey(GLFW_KEY_ENTER)){
		CSceneManager::SlectScene(CSceneManager::Scene::TITLE);
	}
}

void CStage::Draw(AppEnv &app_env){
	app_env.bgColor(color256(0, 103, 192));
	for (auto &Star : m_star){
		Star->Draw(app_env);
	}
	for (auto &Enemy : m_enemy){
		Enemy->Draw(app_env);
	}
	m_player->Draw(app_env);
}

void CStage::CreateEnemy(){
	if (count == 60){
		m_enemy.emplace_back(std::make_unique<CNormalEnemy>(Vec2f(0, 400)));
	}
}

void CStage::Collision(){
	for (auto &Enemy : m_enemy){
		if (Enemy->GetState() == Object::State::LIVE){
			if (m_player->GetState() == Object::State::LIVE){
				if (Collision::isCollision(Enemy->GetPos(), m_player->GetPos(), Enemy->GetR(), m_player->GetR())){
					Enemy->SetHit(true);
				}
			}
		}
	}

	for (auto &Enemy : m_enemy){
		if (Enemy->GetState() == Object::State::LIVE){
			for (auto & Bullet : m_player->m_bullet){
				if (Bullet->GetState() == Object::State::LIVE){
					if (Collision::isCollision(Enemy->GetPos(), Bullet->GetPos(), Enemy->GetR(), Bullet->GetR())){
						Enemy->SetHit(true);
						Bullet->SetHit(true);
					}
				}
			}
		}
	}
}