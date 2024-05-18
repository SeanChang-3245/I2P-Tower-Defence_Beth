#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "IceBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Turret;

IceBullet::IceBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
    Bullet("play/bullet-10.png", 300, 0, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void IceBullet::OnExplode(Enemy *enemy){
    //freeze the enemy for 1 second
    enemy->Freeze(1);
    
}