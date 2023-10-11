#include "Game.h"
#include <algorithm>

namespace book
{
    Game::Game(int X, int Y, int word_x, int word_y) : 
        ActionTarget(Configuration::playerInputs), m_window(sf::VideoMode(X, Y), "04_Gravitris"), 
        m_currentPiece(nullptr), m_world(word_x, word_y)
    {
        bind(Configuration::PlayerInputs::HardDrop, [this](const sf::Event&) {
            m_currentPiece = m_world.newPiece();
            timeSinceLastFall = sf::Time::Zero;
            });

        bind(Configuration::PlayerInputs::TurnLeft, [this](const sf::Event&) {
            m_rotateDirection -= 1;
            });
        bind(Configuration::PlayerInputs::TurnRight, [this](const sf::Event&) {
            m_rotateDirection += 1;
            });

        bind(Configuration::PlayerInputs::MoveLeft, [this](const sf::Event&) {
            m_moveDirection -= 1;
            });

        bind(Configuration::PlayerInputs::MoveRight, [this](const sf::Event&) {
            m_moveDirection += 1;
            });

        m_stats.setPosition(BOOK_BOX_SIZE * (word_x + 3), BOOK_BOX_SIZE);

        m_currentPiece = m_world.newPiece();
    }

    void Game::run(int minimum_frames_per_second, int physics_frames_per_second)
    {
        sf::Clock clock;
        const sf::Time timePerFrame = sf::seconds(1.f / minimum_frames_per_second);
        const sf::Time timePerFramePhysics = sf::seconds(1.f / physics_frames_per_second);

        while (m_window.isOpen())
        {
            sf::Time time = clock.restart();
            processEvents();
            if (not m_stats.isGameOver())
            {
                update_physics(time, timePerFramePhysics);
                update(time, timePerFrame);
            }

            render();
        }
    }

    void Game::update(const sf::Time& deltaTime, const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate += deltaTime;
        timeSinceLastFall += deltaTime;

        if (timeSinceLastUpdate > timePerFrame)
        {
            if (m_currentPiece != nullptr)
            {
                m_currentPiece->rotate(m_rotateDirection * 3000);
                m_currentPiece->moveX(m_moveDirection * 5000);

                bool new_piece;
                {
                    int old_level = m_stats.getLevel();
                    m_stats.addLines(m_world.clearLines(new_piece, *m_currentPiece));
                    if (m_stats.getLevel() != old_level)
                        m_world.add(Configuration::Sounds::LevelUp);
                }

                if (new_piece or timeSinceLastFall.asSeconds() > std::max(1.0, 10.0 - m_stats.getLevel() * 0.2))
                {
                    m_currentPiece = m_world.newPiece();
                    timeSinceLastFall = sf::Time::Zero;
                }
            }

            m_world.update(timePerFrame);
            m_stats.setGameOver(m_world.isGameOver());
            timeSinceLastUpdate = sf::Time::Zero;
        }
        m_rotateDirection = 0;
        m_moveDirection = 0;
    }

    void Game::update_physics(const sf::Time& deltaTime, const sf::Time& timePerFrame)
    {
        static sf::Time timeSinceLastUpdate = sf::Time::Zero;

        timeSinceLastUpdate += deltaTime;
        m_world.updateGravity(m_stats.getLevel());

        while (timeSinceLastUpdate > timePerFrame)
        {
            m_world.updatePhysics(timePerFrame);
            timeSinceLastUpdate -= timePerFrame;
        }
    }

    void Game::processEvents()
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                m_window.close();
            else if (event.type == sf::Event::KeyPressed) //keyboard input
            {
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();
            }

            ActionTarget::processEvent(event);
        }
        ActionTarget::processEvents();
    }

    void Game::render()
    {
        m_window.clear();

        if (not m_stats.isGameOver())
        {
            m_window.draw(m_world);
        }
        m_window.draw(m_stats);

        m_window.display();
    }
}