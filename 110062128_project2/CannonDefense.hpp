#ifndef CannonDefense_hpp
#define CannonDefense_hpp

#include "Defense.hpp"
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include"PlayScene.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Resources.hpp"
#include "Collider.hpp"
class CannonDefense: public Defense {
public:
    CannonDefense(float x, float y);
    
    void CreateBullet(Engine::Point pt) override;
};

class Enemy2Defense : public Defense {
public:
    Enemy2Defense(float x, float y);
    void CreateBullet(Engine::Point pt) override;
};

//bool debug = false;

class TrapDefense : public Defense {
public:
    //std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
    TrapDefense(float x, float y);
    void CreateBullet(Engine::Point pt) override {};
    void Draw() const override{
        
        if (PlayScene::DebugMode) {
            Sprite::Draw();
            // Draw target radius.
            //debug = !debug;
            //al_draw_bitmap(al_load_bitmap("play/ice.png"), Position.x, Position.y, 0);
            //Engine::Resources::GetInstance().GetBitmap("play/trap2.png");
            al_draw_circle(Position.x, Position.y, shootRadius, al_map_rgb(0, 229, 124), 2);
        }
    }
    void Update(float deltaTime) override; 
    void Hit(float damage) override;
};

#endif /* CannonDefense_hpp */
