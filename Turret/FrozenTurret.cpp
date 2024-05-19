#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/IceBullet.hpp"
#include "Engine/Group.hpp"
#include "FrozenTurret.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int FrozenTurret::Price = 50 ;
FrozenTurret::FrozenTurret(float x, float y) :
    Turret("play/tower-base.png", "play/turret-4.png", x, y, 400, Price, 3) {
}

void FrozenTurret::CreateBullet(){
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new IceBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("ice.wav");
}