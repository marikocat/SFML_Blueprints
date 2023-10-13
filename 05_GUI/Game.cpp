#include "Game.h"
#include "Configuration.h"
#include "Piece.h"

#include <sstream>
#include <algorithm>

#include <SFGUI/Label.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Entry.hpp>
#include <SFGUI/Table.hpp>

namespace book
{
    Game::Game(int X, int Y, int word_x, int word_y) : 
        ActionTarget(Configuration::playerInputs), 
        m_window(sf::VideoMode(X, Y), "04_Gravitris"), 
        m_currentPiece(nullptr), 
        m_world(word_x, word_y),
        m_mainMenu(m_window),
        m_pauseMenu(m_window),
        m_configurationMenu(m_window),
        m_status(Status::StatusMainMenu)
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

        initGui();
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

            if (m_status == StatusGame and not m_stats.isGameOver())
            {
                updatePhysics(time, timePerFramePhysics);
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

    void Game::updatePhysics(const sf::Time& deltaTime, const sf::Time& timePerFrame)
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

    void Game::initGui()
    {
        // m_mainMenu
        {
            book::gui::VLayout* layout = new book::gui::VLayout;
            layout->setSpace(25);

            book::gui::TextButton* newGame = new book::gui::TextButton("New Game");
            newGame->onClick = [this](const sf::Event&, book::gui::Button& button)
            {
                initGame();
                m_status = Status::StatusGame;
            };
            layout->add(newGame);

            book::gui::TextButton* configuration = new book::gui::TextButton("Configuration");
            configuration->onClick = [this](const sf::Event&, book::gui::Button& button)
            {
                m_status = Status::StatusConfiguration;
            };
            layout->add(configuration);

            book::gui::TextButton* exit = new book::gui::TextButton("Exit");
            exit->onClick = [this](const sf::Event&, book::gui::Button& button)
            {
                m_window.close();
            };
            layout->add(exit);

            m_mainMenu.setLayout(layout);

            m_mainMenu.bind(Configuration::GuiInputs::Escape, [this](const sf::Event& event)
                {
                    this->m_window.close();
                });
        }

        // m_pauseMenu
        {
            book::gui::VLayout* layout = new book::gui::VLayout;
            layout->setSpace(50);

            book::gui::Label* pause = new book::gui::Label("Pause");
            pause->setCharacterSize(70);
            layout->add(pause);

            book::gui::TextButton* exit = new book::gui::TextButton("Exit");
            exit->onClick = [this](const sf::Event&, book::gui::Button& button)
            {
                m_status = StatusMainMenu;
            };
            layout->add(exit);

            m_pauseMenu.setLayout(layout);

            m_pauseMenu.bind(Configuration::GuiInputs::Escape, [this](const sf::Event& event)
                {
                    m_status = StatusGame;
                });
        }

        // m_configurationMenu
        {
            auto title = sfg::Label::Create("Enter your starting level");
            auto level = sfg::Entry::Create();
            auto error = sfg::Label::Create();
            auto button = sfg::Button::Create("Ok");
            button->GetSignal(sfg::Button::OnLeftClick).Connect(
                [level, error, this]()
                {
                    int lvl = 0;
                    std::stringstream sstr(static_cast<std::string>(level->GetText()));
                    sstr >> lvl;
                    if (lvl < 1 or lvl > 100)
                        error->SetText("Enter a number from 1 to 100.");
                    else
                    {
                        error->SetText("");
                        initGame();
                        m_stats.setLevel(lvl);
                        m_status = Status::StatusGame;
                    }
                }
            );

            auto table = sfg::Table::Create();
            table->SetRowSpacings(10);
            table->Attach(title, sf::Rect<sf::Uint32>(0, 0, 1, 1));
            table->Attach(level, sf::Rect<sf::Uint32>(0, 1, 1, 1));
            table->Attach(button, sf::Rect<sf::Uint32>(0, 2, 1, 1));
            table->Attach(error, sf::Rect<sf::Uint32>(0, 3, 1, 1));
            table->SetAllocation(sf::FloatRect((m_window.getSize().x - 300) / 2.0f,
                (m_window.getSize().y - 200) / 2.0f, 300, 200));
            m_sfgDesktop.Add(table);

            m_configurationMenu.bind(Configuration::GuiInputs::Escape, [this](const sf::Event& event)
                {
                    m_status = StatusMainMenu;
                });
        }
    }

    void Game::initGame()
    {
        timeSinceLastFall = sf::Time::Zero;

        m_stats.reset();
        m_world.reset();

        m_currentPiece = m_world.newPiece();
    }

    void Game::processEvents()
    {
        //to store the events
        sf::Event event;
        //events loop
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//Close window
                m_window.close();
            else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape and m_status == Status::StatusGame)
            {
                m_status = StatusPaused;
            }
            else
            {
                switch (m_status)
                {
                case StatusMainMenu:
                {
                    m_mainMenu.processEvent(event);
                } break;
                case StatusGame:
                {
                    ActionTarget::processEvent(event);
                } break;
                case StatusPaused:
                {
                    m_pauseMenu.processEvent(event);
                } break;
                case StatusConfiguration:
                {
                    m_configurationMenu.processEvent(event);
                    m_sfgDesktop.HandleEvent(event);
                } break;
                default: break;
                }
            }
        }

        switch (m_status)
        {
        case StatusMainMenu:
        {
            m_mainMenu.processEvents();
        } break;
        case StatusGame:
        {
            ActionTarget::processEvents();
        } break;
        case StatusPaused:
        {
            m_pauseMenu.processEvents();
        } break;
        case StatusConfiguration:
        {
            m_configurationMenu.processEvents();
        } break;
        default: break;
        }
    }

    void Game::render()
    {
        m_window.clear();

        switch (m_status)
        {
        case StatusMainMenu:
        {
            m_window.draw(m_mainMenu);
        } break;
        case StatusGame:
        {
            if (not m_stats.isGameOver())
                m_window.draw(m_world);
            m_window.draw(m_stats);

        } break;
        case StatusPaused:
        {
            if (not m_stats.isGameOver())
                m_window.draw(m_world);
            m_window.draw(m_pauseMenu);
        } break;
        case StatusConfiguration:
        {
            m_sfgDesktop.Update(0.0);
            m_sfgui.Display(m_window);
            m_window.draw(m_configurationMenu);
        } break;
        default: break;
        }

        m_window.display();
    }
}