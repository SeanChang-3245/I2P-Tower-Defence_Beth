#ifndef FROZENTUREET_HPP
#define FROZENTUREET_HPP
#include "Turret.hpp"

class FrozenTurret: public Turret {
public:
    static const int Price;
    FrozenTurret(float x, float y);
    void CreateBullet() override;
};
#endif // FROZENTUREET_HPP