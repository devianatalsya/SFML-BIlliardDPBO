// ==============================================
// FILE: BilliardGame.h
// PENANGGUNG JAWAB: KAMU (LEADER)
// ==============================================
#ifndef BILLIARD_GAME_H
#define BILLIARD_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Table.h"
#include "Cue.h"

class BilliardGame
{
private:
    sf::RenderWindow window;
    Table table;
    Cue cue;
    std::vector<Ball> balls;
    Ball *cueBall;

public:
    BilliardGame();

    // TODO KAMU: Game loop utama
    void run();

    // TODO KAMU: Handle input mouse & keyboard
    void handleInput();

    // TODO KAMU: Update semua objek
    void update(float deltaTime);

    // TODO KAMU: Render semua objek
    void render();

    // Helper function
    void initializeBalls();
    bool allBallsStopped();
};

#endif