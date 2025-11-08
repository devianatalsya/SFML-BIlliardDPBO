// ==============================================
// FILE: Ball.h
// PENANGGUNG JAWAB: SEMUA (header)
// ==============================================
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float radius;
    int ballId;
    bool isActive;

public:
    Ball(float x, float y, sf::Color c, int id, float r = 15.0f);

    // TODO DEVIA: Update posisi bola berdasarkan velocity
    void update(float deltaTime);

    // TODO NADINE & FATHYA: Gambar bola ke layar
    void render(sf::RenderWindow &window);

    // TODO DEVIA: Cek apakah bola masih bergerak
    bool isMoving();

    // Getter & Setter (SUDAH SELESAI, jangan diubah)
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    float getRadius() const { return radius; }
    int getId() const { return ballId; }
    bool getIsActive() const { return isActive; }

    void setPosition(sf::Vector2f pos) { position = pos; }
    void setVelocity(sf::Vector2f vel) { velocity = vel; }
    void setActive(bool active) { isActive = active; }
};

#endif