// ==============================================
// FILE: Physics.cpp
// PENANGGUNG JAWAB: DEVIA
// ==============================================
#include "Physics.h"

// TODO DEVIA: Implementasi distance
float Physics::distance(sf::Vector2f a, sf::Vector2f b)
{
    // HINT: sqrt((b.x - a.x)^2 + (b.y - a.y)^2)
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}

// TODO DEVIA: Implementasi normalize
sf::Vector2f Physics::normalize(sf::Vector2f v)
{
    // HINT: Bagi x dan y dengan panjang vector
    // JANGAN LUPA: Cek kalau length = 0!
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length > 0.001f)
    {
        return sf::Vector2f(v.x / length, v.y / length);
    }
    return sf::Vector2f(0, 0);
}

// TODO DEVIA: Implementasi friction
sf::Vector2f Physics::applyFriction(sf::Vector2f velocity, float deltaTime)
{
    // HINT: Kalikan velocity dengan nilai < 1 (misal 0.98)
    float friction = 0.98f;
    return sf::Vector2f(velocity.x * friction, velocity.y * friction);
}

// TODO DEVIA: Implementasi dot product
float Physics::dot(sf::Vector2f a, sf::Vector2f b)
{
    // HINT: a.x * b.x + a.y * b.y
    return a.x * b.x + a.y * b.y;
}