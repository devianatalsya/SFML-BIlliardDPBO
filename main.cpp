#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <memory>

// Utility class for physics calculations
class Physics
{
public:
    static float distance(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    static sf::Vector2f normalize(const sf::Vector2f &vec)
    {
        float len = std::sqrt(vec.x * vec.x + vec.y * vec.y);
        if (len > 0)
        {
            return sf::Vector2f(vec.x / len, vec.y / len);
        }
        return vec;
    }

    static float dot(const sf::Vector2f &a, const sf::Vector2f &b)
    {
        return a.x * b.x + a.y * b.y;
    }
};

// Ball class
class Ball
{
private:
    sf::Vector2f position;
    sf::Vector2f initialPosition;
    sf::Vector2f velocity;
    sf::Color color;
    bool isActive;
    int ballId;
    float radius;
    float friction;
    float minVelocity;
    bool isCueBall;

public:
    Ball(float x, float y, sf::Color ballColor, int id, float r = 10.f)
        : position(x, y), initialPosition(x, y), velocity(0, 0), color(ballColor),
          isActive(true), ballId(id), radius(r),
          friction(0.98f), minVelocity(0.1f), isCueBall(id == 0) {}

    // Getters
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    sf::Color getColor() const { return color; }
    bool getActive() const { return isActive; }
    int getId() const { return ballId; }
    float getRadius() const { return radius; }
    bool getIsCueBall() const { return isCueBall; }

    // Setters
    void setPosition(const sf::Vector2f &pos) { position = pos; }
    void setVelocity(const sf::Vector2f &vel) { velocity = vel; }
    void setActive(bool active) { isActive = active; }

    // Reset cue ball to initial position
    void resetToInitial()
    {
        position = initialPosition;
        velocity = sf::Vector2f(0, 0);
        isActive = true;
    }

    // Check if ball is moving
    bool isMoving() const
    {
        return std::abs(velocity.x) > 0.01f || std::abs(velocity.y) > 0.01f;
    }

    // Apply force to ball
    void applyForce(const sf::Vector2f &force)
    {
        velocity += force;
    }

    // Update ball physics
    void update(const std::vector<sf::Vector2f> &pockets, float tableLeft, float tableTop,
                float tableRight, float tableBottom)
    {
        if (!isActive)
            return;

        // Apply velocity
        position += velocity;

        // Apply friction
        velocity *= friction;

        // Stop if velocity too low
        if (std::abs(velocity.x) < minVelocity)
            velocity.x = 0;
        if (std::abs(velocity.y) < minVelocity)
            velocity.y = 0;

        // Check pocket collision
        for (const auto &pocket : pockets)
        {
            float dist = Physics::distance(position, pocket);
            if (dist < 15.f)
            {
                // If it's the cue ball (scratch), reset instead of removing
                if (isCueBall)
                {
                    velocity = sf::Vector2f(0, 0);
                    position = initialPosition;
                    return;
                }
                else
                {
                    // Regular balls disappear
                    isActive = false;
                    velocity = sf::Vector2f(0, 0);
                    return;
                }
            }
        }

        // Table boundary collision with cushion bounce
        if (position.x - radius < tableLeft || position.x + radius > tableRight)
        {
            velocity.x *= -0.8f;
            position.x = std::max(tableLeft + radius, std::min(tableRight - radius, position.x));
        }
        if (position.y - radius < tableTop || position.y + radius > tableBottom)
        {
            velocity.y *= -0.8f;
            position.y = std::max(tableTop + radius, std::min(tableBottom - radius, position.y));
        }
    }

    // Render ball
    void render(sf::RenderWindow &window) const
    {
        if (!isActive)
            return;

        sf::CircleShape shape(radius);
        shape.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
        shape.setFillColor(color);
        shape.setOutlineThickness(1);
        shape.setOutlineColor(sf::Color::Black);
        window.draw(shape);
    }
};

// Collision Manager
class CollisionManager
{
public:
    static void handleBallCollision(Ball &a, Ball &b)
    {
        if (!a.getActive() || !b.getActive())
            return;

        float dist = Physics::distance(a.getPosition(), b.getPosition());
        float minDist = a.getRadius() + b.getRadius();

        if (dist < minDist && dist > 0)
        {
            // Normalize collision vector
            sf::Vector2f normal = (b.getPosition() - a.getPosition()) / dist;

            // Separate balls
            float overlap = minDist - dist;
            a.setPosition(a.getPosition() - normal * (overlap / 2.f));
            b.setPosition(b.getPosition() + normal * (overlap / 2.f));

            // Calculate relative velocity
            sf::Vector2f relVel = a.getVelocity() - b.getVelocity();
            float velAlongNormal = Physics::dot(relVel, normal);

            if (velAlongNormal < 0)
                return;

            // Apply impulse
            sf::Vector2f impulse = normal * velAlongNormal;
            a.setVelocity(a.getVelocity() - impulse);
            b.setVelocity(b.getVelocity() + impulse);
        }
    }
};

// Table class
class Table
{
private:
    float width, height;
    float borderSize;
    sf::Color feltColor;
    sf::Color borderColor;
    std::vector<sf::Vector2f> pockets;

public:
    Table(float w, float h, float border = 50.f)
        : width(w), height(h), borderSize(border),
          feltColor(0, 100, 0), borderColor(139, 69, 19)
    {
        // Initialize pockets
        pockets = {
            {borderSize, borderSize},
            {width / 2, borderSize},
            {width - borderSize, borderSize},
            {borderSize, height - borderSize},
            {width / 2, height - borderSize}
            {width - borderSize, height - borderSize}};
    }

    const std::vector<sf::Vector2f> &getPockets() const { return pockets; }
    float getBorderSize() const { return borderSize; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    float getPlayAreaLeft() const { return borderSize; }
    float getPlayAreaTop() const { return borderSize; }
    float getPlayAreaRight() const { return width - borderSize; }
    float getPlayAreaBottom() const { return height - borderSize; }

    void render(sf::RenderWindow &window) const
    {
        // Draw table felt
        sf::RectangleShape felt(sf::Vector2f(width - 2 * borderSize, height - 2 * borderSize));
        felt.setPosition(sf::Vector2f(borderSize, borderSize));
        felt.setFillColor(feltColor);
        felt.setOutlineThickness(borderSize);
        felt.setOutlineColor(borderColor);
        window.draw(felt);

        // Draw pockets
        for (const auto &pocket : pockets)
        {
            sf::CircleShape pocketShape(15);
            pocketShape.setPosition(sf::Vector2f(pocket.x - 15, pocket.y - 15));
            pocketShape.setFillColor(sf::Color::Black);
            window.draw(pocketShape);
        }
    }
};

// Cue class
class Cue
{
private:
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    bool isAiming;
    float maxPower;

public:
    Cue() : isAiming(false), maxPower(30.f) {}

    void startAiming(const sf::Vector2f &pos)
    {
        startPos = pos;
        isAiming = true;
    }

    void updateAim(const sf::Vector2f &pos)
    {
        endPos = pos;
    }

    sf::Vector2f shoot()
    {
        if (!isAiming)
            return sf::Vector2f(0, 0);

        float dx = startPos.x - endPos.x;
        float dy = startPos.y - endPos.y;
        float power = std::sqrt(dx * dx + dy * dy) * 0.3f;
        power = std::min(power, maxPower);

        isAiming = false;

        if (power > 1.f)
        {
            float angle = std::atan2(dy, dx);
            return sf::Vector2f(std::cos(angle) * power, std::sin(angle) * power);
        }

        return sf::Vector2f(0, 0);
    }

    void cancelAim()
    {
        isAiming = false;
    }

    bool getIsAiming() const { return isAiming; }

    void render(sf::RenderWindow &window, const sf::Vector2f &ballPos) const
    {
        if (!isAiming)
            return;

        sf::Vertex line[] = {
            sf::Vertex{.position = ballPos, .color = sf::Color::White},
            sf::Vertex{.position = endPos, .color = sf::Color(255, 255, 255, 100)}};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
};

// Game class - main game controller
class BilliardGame
{
private:
    sf::RenderWindow window;
    Table table;
    Cue cue;
    std::vector<std::unique_ptr<Ball>> balls;

    void initializeBalls()
    {
        // Cue ball (white)
        balls.push_back(std::make_unique<Ball>(200, table.getHeight() / 2, sf::Color::White, 0));

        // Rack balls in triangle
        float startX = 550;
        float startY = table.getHeight() / 2;
        float spacing = 21.f;

        sf::Color colors[] = {
            sf::Color::Yellow, sf::Color::Blue, sf::Color::Red, sf::Color(128, 0, 128),
            sf::Color(255, 165, 0), sf::Color::Green, sf::Color(139, 69, 19),
            sf::Color(0, 0, 139), sf::Color::Black, sf::Color(255, 215, 0),
            sf::Color(0, 100, 0), sf::Color(220, 20, 60), sf::Color(255, 140, 0),
            sf::Color(75, 0, 130), sf::Color(184, 134, 11)};

        int ballIdx = 0;
        for (int row = 0; row < 5; ++row)
        {
            for (int col = 0; col <= row; ++col)
            {
                float x = startX + row * spacing * 0.866f;
                float y = startY + (col - row / 2.f) * spacing;
                balls.push_back(std::make_unique<Ball>(x, y, colors[ballIdx % 15], ballIdx + 1));
                ballIdx++;
            }
        }
    }

    bool areAnyBallsMoving() const
    {
        for (const auto &ball : balls)
        {
            if (ball->isMoving())
                return true;
        }
        return false;
    }

    void handleInput()
    {
        // SFML 3.0: pollEvent returns std::optional
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // SFML 3.0: New event handling pattern
            if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    if (!areAnyBallsMoving() && balls[0]->getActive())
                    {
                        sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x),
                                              static_cast<float>(mousePressed->position.y));
                        cue.startAiming(mousePos);
                    }
                }
            }

            if (const auto *mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
            {
                if (mouseReleased->button == sf::Mouse::Button::Left)
                {
                    if (cue.getIsAiming() && balls[0]->getActive())
                    {
                        sf::Vector2f force = cue.shoot();
                        balls[0]->setVelocity(force);
                    }
                }
            }
        }

        // Update cue aim position
        if (cue.getIsAiming())
        {
            // SFML 3.0: getPosition now returns sf::Vector2i directly
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            cue.updateAim(sf::Vector2f(static_cast<float>(mousePos.x),
                                       static_cast<float>(mousePos.y)));
        }
    }

    void update()
    {
        // Update all balls
        for (auto &ball : balls)
        {
            ball->update(table.getPockets(),
                         table.getPlayAreaLeft(),
                         table.getPlayAreaTop(),
                         table.getPlayAreaRight(),
                         table.getPlayAreaBottom());
        }

        // Handle collisions between all balls
        for (size_t i = 0; i < balls.size(); ++i)
        {
            for (size_t j = i + 1; j < balls.size(); ++j)
            {
                CollisionManager::handleBallCollision(*balls[i], *balls[j]);
            }
        }
    }

    void render()
    {
        window.clear(sf::Color(34, 139, 34));

        // Render table
        table.render(window);

        // Render cue line
        if (balls[0]->getActive())
        {
            cue.render(window, balls[0]->getPosition());
        }

        // Render all balls
        for (const auto &ball : balls)
        {
            ball->render(window);
        }

        window.display();
    }

public:
    BilliardGame()
        : window(sf::VideoMode({800, 400}), "SFML 3.0.2 Billiards - OOP"),
          table(800, 400)
    {
        window.setFramerateLimit(60);
        initializeBalls();
    }

    void run()
    {
        while (window.isOpen())
        {
            handleInput();
            update();
            render();
        }
    }
};

int main()
{
    BilliardGame game;
    game.run();
    return 0;
}