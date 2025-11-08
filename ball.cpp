// ==============================================
// FILE: Ball.cpp
// PENANGGUNG JAWAB: DEVIA (update), NADINE & FATHYA (render)
// ==============================================
#include "Ball.h"
#include "Physics.h"

Ball::Ball(float x, float y, sf::Color c, int id, float r)
    : position(x, y), velocity(0, 0), color(c), ballId(id), radius(r), isActive(true) {}

// ===== BAGIAN DEVIA =====
void Ball::update(float deltaTime)
{
    // TODO DEVIA: Update posisi bola
    // HINT:
    // 1. position += velocity * deltaTime
    // 2. Terapkan friction: velocity = Physics::applyFriction(velocity, deltaTime)
    // 3. Kalau velocity sangat kecil (< 0.1), set jadi 0

    if (!isActive)
        return;

    // Step 1: Update posisi
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Step 2: Apply friction
    velocity = Physics::applyFriction(velocity, deltaTime);

    // Step 3: Stop kalau terlalu lambat
    if (std::abs(velocity.x) < 0.1f && std::abs(velocity.y) < 0.1f)
    {
        velocity = sf::Vector2f(0, 0);
    }
}

bool Ball::isMoving()
{
    // TODO DEVIA: Return true kalau velocity > 0
    return std::abs(velocity.x) > 0.01f || std::abs(velocity.y) > 0.01f;
}

// ===== BAGIAN NADINE & FATHYA =====
void Ball::render(sf::RenderWindow &window)
{
    // TODO NADINE & FATHYA: Gambar bola
    // HINT:
    // 1. Bikin sf::CircleShape dengan radius
    // 2. Set posisi (INGAT: posisi circle harus dikurangi radius!)
    // 3. Set warna sesuai this->color
    // 4. window.draw(circle)

    if (!isActive)
        return;

    sf::CircleShape circle(radius);
    circle.setPosition(position.x - radius, position.y - radius);
    circle.setFillColor(color);

    // BONUS: Tambahkan outline putih biar keliatan lebih bagus
    circle.setOutlineThickness(2.0f);
    circle.setOutlineColor(sf::Color::White);

    window.draw(circle);
}