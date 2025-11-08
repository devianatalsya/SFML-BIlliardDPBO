// ==============================================
// FILE: BilliardGame.cpp
// PENANGGUNG JAWAB: KAMU (LEADER)
// ==============================================
#include "BilliardGame.h"

BilliardGame::BilliardGame()
    : window(sf::VideoMode(1200, 700), "Billiard Game OOP"),
      table(1200, 700)
{

    window.setFramerateLimit(60);
    initializeBalls();
}

void BilliardGame::initializeBalls()
{
    // TODO KAMU: Buat 16 bola (1 cue ball putih + 15 colored balls)
    // HINT: Cue ball di kiri, 15 balls diatur segitiga di kanan

    // Cue ball (putih)
    balls.push_back(Ball(300, 350, sf::Color::White, 0));
    cueBall = &balls[0];

    // 15 Colored balls (segitiga)
    // Baris 1
    balls.push_back(Ball(800, 350, sf::Color::Yellow, 1));

    // Baris 2
    balls.push_back(Ball(830, 335, sf::Color::Blue, 2));
    balls.push_back(Ball(830, 365, sf::Color::Red, 3));

    // Baris 3
    balls.push_back(Ball(860, 320, sf::Color::Magenta, 4));
    balls.push_back(Ball(860, 350, sf::Color::Black, 8)); // 8-ball
    balls.push_back(Ball(860, 380, sf::Color::Cyan, 5));

    // Baris 4 & 5 (tambahkan sendiri kalau mau lengkap)
    // ...
}

void BilliardGame::run()
{
    // TODO KAMU: Game loop utama
    // HINT:
    // 1. Bikin sf::Clock untuk deltaTime
    // 2. Loop selama window terbuka
    // 3. Panggil handleInput(), update(), render()

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        handleInput();
        update(deltaTime);
        render();
    }
}

void BilliardGame::handleInput()
{
    // TODO KAMU: Handle input mouse & keyboard
    // HINT:
    // 1. Handle window close event
    // 2. Kalau mouse pressed & semua bola diam, mulai aiming
    // 3. Kalau mouse moving, update aim
    // 4. Kalau mouse released, shoot cue ball

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && allBallsStopped())
        {
            cue.startAiming(cueBall->getPosition());
        }

        if (event.type == sf::Event::MouseButtonReleased && cue.getIsAiming())
        {
            // Hitung velocity berdasarkan power & direction
            sf::Vector2f direction = cue.getDirection();
            float power = cue.getPower();
            cueBall->setVelocity(direction * power * 2.0f);
            cue.stopAiming();
        }
    }

    // Update aim kalau sedang aiming
    if (cue.getIsAiming())
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);
        cue.updateAim(mousePos);
    }
}

void BilliardGame::update(float deltaTime)
{
    // TODO KAMU: Update semua objek
    // HINT: Loop semua balls dan panggil ball.update(deltaTime)

    for (auto &ball : balls)
    {
        ball.update(deltaTime);
    }

    // TODO NANTI: Tambahkan collision detection
}

void BilliardGame::render()
{
    // TODO KAMU: Render semua objek
    // HINT:
    // 1. window.clear()
    // 2. table.render(window)
    // 3. Loop balls dan panggil ball.render(window)
    // 4. cue.render(window, cueBall position)
    // 5. window.display()

    window.clear(sf::Color::Black);

    table.render(window);

    for (auto &ball : balls)
    {
        ball.render(window);
    }

    cue.render(window, cueBall->getPosition());

    window.display();
}

bool BilliardGame::allBallsStopped()
{
    for (const auto &ball : balls)
    {
        if (ball.isMoving())
        {
            return false;
        }
    }
    return true;
}
