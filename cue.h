// ==============================================
// FILE: Cue.h
// PENANGGUNG JAWAB: NADINE & FATHYA
// ==============================================
#ifndef CUE_H
#define CUE_H

#include <SFML/Graphics.hpp>

class Cue
{
private:
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    bool isAiming;
    float power;

public:
    Cue();

    void startAiming(sf::Vector2f ballPos);
    void updateAim(sf::Vector2f mousePos);
    void stopAiming();

    // TODO NADINE & FATHYA: Gambar garis bidik dari bola ke mouse
    void render(sf::RenderWindow &window, sf::Vector2f ballPos);

    // Getter
    bool getIsAiming() const { return isAiming; }
    float getPower() const { return power; }
    sf::Vector2f getDirection() const;
};

#endif