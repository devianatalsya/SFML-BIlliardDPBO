// ==============================================
// FILE: Table.h
// PENANGGUNG JAWAB: NADINE & FATHYA
// ==============================================
#ifndef TABLE_H
#define TABLE_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Pocket
{
    sf::Vector2f position;
    float radius;

    Pocket(float x, float y, float r) : position(x, y), radius(r) {}
};

class Table
{
private:
    float width;
    float height;
    std::vector<Pocket> pockets;

public:
    Table(float w, float h);

    // TODO NADINE & FATHYA: Gambar meja billiard
    void render(sf::RenderWindow &window);

    // Getter (SUDAH SELESAI)
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    std::vector<Pocket> getPockets() const { return pockets; }
};

#endif