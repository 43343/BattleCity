#include "menu.h"

Menu::Menu(SceneStack& scene, Context context)
    : Scene(scene, context)
{
    if (!font.loadFromFile("fonts\\PublicPixel-z84yD.ttf")) {
        std::cout << "Failed to load font!" << std::endl;
        return;
    }
    //GamePanel
    typingText(score, sf::Color::White, font, 31, 450.f, 1995.f, "I -   00  HI -   20000");
    tank_n_texture.loadFromFile("textures\\tank-h.png");
    tank_n_sprite.setTexture(tank_n_texture);
    tank_n_sprite.setPosition(500.f, 2095.f);
    tank_n_sprite.setScale(1.f, 1.f);
    float x = getContext().window->getView().getSize().x;
    float y = getContext().window->getView().getSize().y;
    typingText(resume, sf::Color::White, font, x / 38.4, x / 2.5, y, "RESUME");
    typingText(newGame, sf::Color::White, font, x / 38.4, x / 2.5, y + (y/10), "NEW GAME");
    typingText(settings, sf::Color::White, font, x / 38.4, x / 2.5, y + (y / 10 * 2), "SETTINGS");
    typingText(exit, sf::Color::White, font, x / 38.4, x / 2.5, y + (y / 10 * 3), "EXIT");
    typingText(year, sf::Color::White, font, x / 38.4, x / 2.5, y + (y / 10 * 4), "©️   YS  1990");

    //SettingsPanel
    typingText(settingsText, sf::Color::White, font, 50, 750.f, 1000.f, "SETTINGS");
    typingText(fullScreenMode, sf::Color::White, font, 50, 750.f, 1000.f, "FULLSCREEN MODE");
    typingText(screenResolution, sf::Color::White, font, 50, 750.f, 1000.f, "SCREEN RESOLUTION");
    typingText(soundVolume, sf::Color::White, font, 50, 750.f, 1000.f, "SOUND");
    typingText(back, sf::Color::White, font, 50, 750.f, 1000.f, "BACK");
    std::cout << "MenuCreate";
    tank_texture.loadFromFile("textures\\texture.png");
    tank_sprite.setTexture(tank_texture);
    tank_sprite.setTextureRect(sf::IntRect(112, 15, 16, 15));
    tank_sprite.setScale(4.f, 4.f);
    tank_sprite.setPosition(600.f, 2415.f);

    scoreAnim.animSet(score);
    scoreAnim.addFlag(sf::Vector2f(450.f, 75.f),10.f);
    tank_n_spriteAnim.animSet(tank_n_sprite);
    tank_n_spriteAnim.addFlag(sf::Vector2f(500.f, 175.f),10.f);
    resumeAnim.animSet(resume);
    resumeAnim.addFlag(sf::Vector2f(x / 2.5, y / 2.17),10.f);
    newGameAnim.animSet(newGame);
    newGameAnim.addFlag(sf::Vector2f(x / 2.5, y / 2.17 + (y / 10)),10.f);
    settingsAnim.animSet(settings);
    settingsAnim.addFlag(sf::Vector2f(x / 2.5, y / 2.17 + (y / 10 * 2)),10.f);
    exitAnim.animSet(exit);
    exitAnim.addFlag(sf::Vector2f(x / 2.5, y / 2.17 + (y / 10 * 3)),10.f);
    yearAnim.animSet(year);
    yearAnim.addFlag(sf::Vector2f(x / 2.5, y / 2.17 + (y / 10 * 4)),10.f);
    tank_spriteAnim.animSet(tank_sprite);
    tank_spriteAnim.addFlag(sf::Vector2f(600.f, 495.f),10.f);
    std::cout << "Anim1CreatedAll" << std::endl;
    scoreAnim.startAnimation();
    tank_n_spriteAnim.startAnimation();
    resumeAnim.startAnimation();
    newGameAnim.startAnimation();
    settingsAnim.startAnimation();
    exitAnim.startAnimation();
    yearAnim.startAnimation();
    tank_spriteAnim.startAnimation();

}

void Menu::typingText(sf::Text &textObject, const sf::Color &color, const sf::Font &font,unsigned int size, float positionX, float positionY, const sf::String &string) {
    textObject.setFillColor(color);
    textObject.setPosition(positionX, positionY);
    textObject.setFont(font);
    textObject.setCharacterSize(size);
    textObject.setString(string);
    std:: cout << "ObjectCreate" << std::endl;
}
bool Menu::handleEvent(const sf::Event& event) {
    sf::RenderWindow& m_window = *getContext().window;
        if (!scoreAnim.isAnimating()) {
            switch (activePanel) {
            case PanelActive::GamePanel: GamePanelHandleEvents(event, m_window); break;
            case PanelActive::SettingsPanel: SettingsPanelHandleEvents(event); break;
            }
            tank_sprite.setPosition(600.f, 495.f + 100 * textSelect);
        }
        return true;
    
}

void Menu::GamePanelHandleEvents(sf::Event event, sf::RenderWindow& m_window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (int)event.type == sf::Event::MouseWheelScrolled > 0) {
        textSelect = (textSelect + maxTextSelect - 1) % maxTextSelect;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || event.type == sf::Event::MouseWheelScrolled < 0) {
        textSelect = (textSelect + 1) % maxTextSelect;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        switch (textSelect) {
        case 2: activePanel = PanelActive::SettingsPanel; break;
        case 3: m_window.close(); break;
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        // Обработка нажатия кнопок меню
        if (resume.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            textSelect = 0;
        }
        else if (newGame.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            textSelect = 1;
        }
        else if (settings.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            textSelect = 2;
        }
        else if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            textSelect = 3;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        // Обработка нажатия кнопок меню
        if (resume.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            // Запуск игры
           SceneLoad(Scenes::Level1);
        }
        else if (newGame.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            SceneLoad(Scenes::Level1);
        }
        else if (settings.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            activePanel = PanelActive::SettingsPanel;
        }
        else if (exit.getGlobalBounds().contains(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y)) {
            m_window.close();
        }
    }
}
void Menu::SettingsPanelHandleEvents(sf::Event event) {

}
bool Menu::update(const float deltaTime) {
    scoreAnim.update(deltaTime);
    tank_n_spriteAnim.update(deltaTime);
    resumeAnim.update(deltaTime);
    newGameAnim.update(deltaTime);
    settingsAnim.update(deltaTime);
    exitAnim.update(deltaTime);
    yearAnim.update(deltaTime);
    tank_spriteAnim.update(deltaTime);
    return true;
}
void Menu::draw() {
    sf::RenderWindow& m_window = *getContext().window;
    m_window.setView(m_window.getDefaultView());

    // Отрисовка элементов меню
    switch (activePanel) {
    case PanelActive::GamePanel:
        m_window.draw(score);
        m_window.draw(tank_n_sprite);
        m_window.draw(resume);
        m_window.draw(newGame);
        m_window.draw(settings);
        m_window.draw(exit);
        m_window.draw(year); 
        break;
    case PanelActive::SettingsPanel:
        m_window.draw(settingsText);
        m_window.draw(fullScreenMode);
        m_window.draw(screenResolution);
        m_window.draw(soundVolume);
        m_window.draw(back);
        break;
    }
    m_window.draw(tank_sprite);
}