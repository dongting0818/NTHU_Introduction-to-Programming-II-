#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>
#include <limits>
#include "LOG.hpp"
#include "AudioHelper.hpp"
#include "Collider.hpp"
#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "BombArmy.hpp"
#include "Defense.hpp"



//Army(std::string img, float x, float y, float radius, float coolDown, float speed, float hp, int id, float shootRadius);
BombArmy::BombArmy(float x, float y) :
    Army("play/bombs.png", x, y, 20, 0, 80, 15, 1, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

SofaArmy::SofaArmy(float x, float y) :
    Army("play/enemy-2.png", x, y, 20, 0, 80, 30, 2, 0) {
    // Move center downward, since we the army head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

Ice_Spell::Ice_Spell(float x, float y):
    Army("play/ice.png", x, y, 20, 0, 0, 30, 3, 3) {
    Anchor.y += 8.0f / GetBitmapHeight();
    ice_counter = al_create_timer(1.0f / 60);
}   

void BombArmy::Update(float deltaTime) {
    // PlayScene
    PlayScene* scene = getPlayScene();

    if (isPreview) return ;
    
    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));
    
    if (!Target) {
        // Lock closet target
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        
        // TODO 2 (6/8): Lock the closet wall. If there's no wall on the map, it will lock the closet defense.
        // For the simplicity, we use manHattan distance to measure the distance bewteen objects. You can use the ManHattanDistance() function in Army class directly for calculation.
        int maxDis = INT_MAX;
        Defense* tgt = nullptr;
      
        for (auto& it : scene->WallGroup->GetObjects()) {
            int dis = ManHattanDistance(it->Position);
            if (dis < maxDis) {
                maxDis = dis;
                tgt = dynamic_cast<Defense*>(it);
            }
            movingToWall = true;
        }

        maxDis = INT_MAX;

        if (tgt == nullptr) {
            movingToWall = false;
            for (auto& it : scene->DefenseGroup->GetObjects()) {
                int dis = ManHattanDistance(it->Position);
                if (dis < maxDis) {
                    maxDis = dis;
                    tgt = dynamic_cast<Defense*>(it);
                }
            }
        }
        
        if (tgt) {
            Target = tgt;
            Target->lockedArmies.push_back(this);
            lockedArmyIterator = std::prev(Target->lockedArmies.end());
        }
        
        
        // TODO 2 (7/8): Store the closet target in Target, and update lockedArmyIterator. You can imitate the same part in Defense::Update().
        // Also, record the target is wall or a noraml defense.
        //movingToWall = true;
        
    }
    if (Target) {
        Rotation = UpdateRotation(deltaTime, Target->Position);
        // Bomb cannot shoot, so the reload time just set as coolDown.
        reload = coolDown;
        
        // TODO 2 (8/8): If bomb army is on the same block with target. Explode itself to deal damage to the target. Otherwise, move toward the target.
        //if (false /* need to modify */) {
            // Notice that bomb army deals different damage to wall and normal target.
            
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, Target->Position, Target->CollisionRadius)) {
            if (movingToWall) {
                Target->Hit(500); 
            }
            else {
                Target->Hit(10); 
            }
            Hit(INFINITY);
        }
        //}
        else {
            int dx = Target->Position.x - Position.x;
            int dy = Target->Position.y - Position.y;
            double len = sqrt(pow(dx, 2) + pow(dy, 2));
            Velocity = speed * Engine::Point(dx / len, dy / len);
        }
        
    }

    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;
}

void Ice_Spell::Update(float deltaTime) {

    PlayScene* scene = getPlayScene();
    if (isPreview) return;
    //bool end = false;

    if (is_on == false) {
        al_start_timer(ice_counter);
        AudioHelper::PlayAudio("ice!.wav");
        is_on = true;
    }
    
    if (al_get_timer_count(ice_counter) / 60.0 >= 2.0) {
        al_stop_timer(ice_counter);
        is_on = false;
        al_destroy_timer(ice_counter);
        Hit(INFINITY);
        return;
    }



    //getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
    // position
    int x = static_cast<int>(floor(Position.x / PlayScene::BlockSize));
    int y = static_cast<int>(floor(Position.y / PlayScene::BlockSize));

    Defense* tgt = nullptr;
    //Engine::LOG() << "Ice Spell " << Position.x / PlayScene::BlockSize << " " << Position.y / PlayScene::BlockSize;

    for (auto& it : scene->DefenseGroup->GetObjects()) {
    
        
        
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x - PlayScene::BlockSize, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x + PlayScene::BlockSize, Position.y - PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x - PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x , Position.y));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x + PlayScene::BlockSize, Position.y));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x - PlayScene::BlockSize, Position.y + PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x, Position.y + PlayScene::BlockSize));
        getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x + PlayScene::BlockSize, Position.y + PlayScene::BlockSize));
        
        float sz = getPlayScene()->BlockSize;
        if ((it->Position.x - Position.x <= sz && it->Position.x - Position.x >= sz * -1) && (it->Position.y - Position.y <= sz && it->Position.y - Position.y >= sz * -1)) {
            // Engine::Collider::IsCircleOverlap(Position, CollisionRadius, Target->Position, Target->CollisionRadius)
            tgt = dynamic_cast<Defense*>(it);
            tgt->set_reload(INT_MAX);
            lockedDefenses.push_back(tgt);
        }
    }
    //if (end == true) {
        //tgt->set_reload(0);
        //return;
    //}

    if (tgt) {
        Target = tgt;
    }
    
}

void SofaArmy::Update(float deltaTime) {
    reload = coolDown;
    PlayScene* scene = getPlayScene();

    if (isPreview) return;
}

// Since the bomb army cannot shoot, the function doesn't need to do anything.
void BombArmy::CreateBullet(Engine::Point pt) {}
void SofaArmy::CreateBullet(Engine::Point pt) {}

//  (5/8): You can imitate the hit function in Army class. Notice that the bomb army won't have explosion effect.
void BombArmy::Hit(float damage) {
    HP -= damage;
    //if (damage == 2.5) {
        //this->s;
        
    //}
    if (damage == 2.5) {
        this->speed = 30;
        //LOG(2) << "INNNNNNNNNNNNNNNNNNNNNNNNNN"<<std::endl;
    }
    if (HP <= 0) {
        //OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it : lockedDefenses)
            it->Target = nullptr;
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
    }
}

void SofaArmy::Hit(float damage) {
    HP -= damage;
    if (damage == 2.5) {
        this->speed = 30;
        //LOG(2) << "INNNNNNNNNNNNNNNNNNNNNNNNNN"<<std::endl;
    }
    if (HP <= 0) {
        OnExplode();
        // Remove all Defense's reference to target.
        for (auto& it : lockedDefenses)
            it->Target = nullptr;
        getPlayScene()->ArmyGroup->RemoveObject(objectIterator);
    }
}



