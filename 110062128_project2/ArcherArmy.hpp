#ifndef ArcherArmy_hpp
#define ArcherArmy_hpp

#include "Army.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Army.hpp"

class ArcherArmy: public Army {
public:
    ArcherArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
};

class  PowerArmy :public Army {
public:
    PowerArmy(int x, int y);
    void CreateBullet(Engine::Point pt) override;
    //void Update(float deltaTime) override;
};

#endif /* ArcherArmy_hpp */
