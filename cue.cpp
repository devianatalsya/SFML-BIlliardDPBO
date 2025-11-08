
// ==============================================
// FILE: Cue.cpp
// PENANGGUNG JAWAB: NADINE & FATHYA
// ==============================================
#include "Cue.h"
#include "Physics.h"

Cue::Cue() : isAiming(false), power(0) {}

void Cue::startAiming(sf::Vector2f ballPos)
{
    isAiming = true;
    startPos = ballPos;
}

void Cue::updateAim(sf::Vector2f mousePos)
{
    endPos = mousePos;
    power = Physics::distance(startPos, endPos);
    if (power > 300.0f)
        power = 300.0f; // Max power
}

void Cue::stopAiming()
{
    isAiming = false;
}

sf::Vector2f Cue::getDirection() const
{
    sf::Vector2f dir = startPos - endPos; // Arah dari mouse ke bola
    return Physics::normalize(dir);
}

void Cue::render(sf::RenderWindow &window, sf::Vector2f ballPos)
{
    // TODO NADINE & FATHYA: Gambar garis bidik
    // HINT:
    // 1. Kalau isAiming == false, jangan gambar apa-apa
    // 2. Bikin garis dari ballPos ke endPos (mouse position)
    // 3. Gunakan sf::Vertex array dengan 2 titik
    // 4. Warna merah kalau power > 200, kuning kalau > 100, hijau kalau < 100

    if (!isAiming)
        return;

    // Tentukan warna berdasarkan power
    sf::Color lineColor;
    if (power > 200)
        lineColor = sf::Color::Red;
    else if (power > 100)
        lineColor = sf::Color::Yellow;
    else
        lineColor = sf::Color::Green;

    // Gambar garis
    sf::Vertex line[] = {
        sf::Vertex(ballPos, lineColor),
        sf::Vertex(endPos, lineColor)};
    window.draw(line, 2, sf::Lines);

    // BONUS: Gambar lingkaran kecil di ujung mouse
    sf::CircleShape dot(5);
    dot.setPosition(endPos.x - 5, endPos.y - 5);
    dot.setFillColor(lineColor);
    window.draw(dot);
}