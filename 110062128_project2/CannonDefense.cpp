#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <utility>
#include "CannonDefense.hpp"
#include "AudioHelper.hpp"
#include "CannonBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"
#include "Defense.hpp"
#include "GameEngine.hpp"
#include "Collider.hpp"

//Defense(std::string imgDefense, float x, float y, float radius, float coolDown, int hp, int id, float shootRadius);
CannonDefense::CannonDefense(float x, float y) :
    Defense("play/cannon.png", x, y, 20, 1, 50, 2, 425) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

Enemy2Defense::Enemy2Defense(float x, float y) :
    Defense("play/enemy-4.png", x, y, 20, 0.7, 50, 3, 500) {
    Anchor.y += 2.0f / GetBitmapHeight();
}

TrapDefense::TrapDefense(float x, float y) : 
    Defense("play/trap2.png", x, y, 20, 1, 50, 2, 100) {  
    Anchor.y += 2.0f / GetBitmapHeight();
}

void TrapDefense::Update(float deltatime) {
    PlayScene* scene = getPlayScene();
    if (!Target) {
        int ey;
        for (auto& it : scene->ArmyGroup->GetObjects()) {
            ey = static_cast<int>(floor(it->Position.y / PlayScene::BlockSize));
            if (InShootingRange(it->Position)) {
                Target = dynamic_cast<Army*>(it);
                if (Target->id == 3) {                   
                    Target = nullptr;
                    break;
                }
                break;
            }
        }
    }
    if (Target) {
        //if (Engine::Collider::IsCircleOverlap(Position, shootRadius, Target->Position, Target->CollisionRadius)) {
        Target->Hit(INFINITY);
        Hit(INFINITY); 
        //}
    }
}

void TrapDefense::Hit(float damage) {
    HP -= damage;
    OnExplode();
    for (auto& it : lockedArmies) {
        it->Target = nullptr;
    }
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    getPlayScene()->ClearMapState(x, y);
    getPlayScene()->TrapGroup->RemoveObject(objectIterator);
    AudioHelper::PlayAudio("explosion.wav");
}

void CannonDefense::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new CannonBullet(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}



void Enemy2Defense::CreateBullet(Engine::Point pt) {
    int dx = pt.x - Position.x;
    int dy = pt.y - Position.y;
    double len = sqrt(pow(dx, 2) + pow(dy, 2));
    Engine::Point diff = Engine::Point(dx / len, dy / len);
    Engine::Point rotateDiff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(rotateDiff.y, rotateDiff.x) + ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new Enemy_2Bullet(Position, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
