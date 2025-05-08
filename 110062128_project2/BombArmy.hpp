#ifndef BombArmy_hpp
#define BombArmy_hpp

#include "Army.hpp"
#include"ExplosionEffect.hpp"
#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <string>
#include <limits>
#include "Defense.hpp"

class BombArmy: public Army {
public:
    BombArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

class SofaArmy :public Army {
public:
    SofaArmy(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override;
    void Hit(float damage) override;
};

class Ice_Spell:public Army {
public:
    ALLEGRO_TIMER* ice_counter;
    bool is_on = false;
    Ice_Spell(float x, float y);
    void Update(float deltaTime) override;
    void CreateBullet(Engine::Point pt) override {}
    void Hit(float damage) override {
        HP -= damage;
        for (auto& it : lockedDefenses) {
            it->set_reload(it->get_coolDown());
        }
        //for (auto& it : getPlayScene()->) {

  //      }
        if (HP <= 0) {
            //this->OnExplode_Ice();
            getPlayScene()->IceGroup->RemoveObject(objectIterator);
        }
        
    }
    //void OnExplode_Ice() {
       // getPlayScene()->EffectGroup->AddNewObject(new IceEffect(Position.x, Position.y));
    //}
};

#endif /* BombArmy_hpp */
