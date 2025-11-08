// ==============================================
// FILE: Physics.h
// PENANGGUNG JAWAB: DEVIA
// ==============================================
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Physics
{
public:
    // TODO DEVIA: Hitung jarak antara dua titik
    static float distance(sf::Vector2f a, sf::Vector2f b);

    // TODO DEVIA: Normalisasi vector (ubah jadi panjang 1)
    static sf::Vector2f normalize(sf::Vector2f v);

    // TODO DEVIA: Terapkan friction (perlambatan) ke velocity
    static sf::Vector2f applyFriction(sf::Vector2f velocity, float deltaTime);

    // TODO DEVIA: Dot product untuk collision
    static float dot(sf::Vector2f a, sf::Vector2f b);
};

#endif