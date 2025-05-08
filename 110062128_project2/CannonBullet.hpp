#ifndef CannonBullet_hpp
#define CannonBullet_hpp

#include "Bullet.hpp"

class Army;
class Defense;
namespace Engine {
struct Point;
}  // namespace Engine

class CannonBullet : public Bullet {
public:
    explicit CannonBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

class Enemy_2Bullet : public Bullet {
public:
    explicit Enemy_2Bullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Defense* parent);
};

#endif /* CannonBullet_hpp */
