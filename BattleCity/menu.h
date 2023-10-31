#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SceneStack.h"
#include "Scene.h"
#include "SceneIdentifier.h"
class Menu : public Scene {
public:
    Menu(SceneStack& stack, Context context);
    enum PanelActive {
        GamePanel,
        SettingsPanel
    };
    sf::Font font;
    //GamePanel
    sf::Text score;
    Animation scoreAnim;
    sf::Texture tank_n_texture;
    sf::Sprite tank_n_sprite;
    Animation tank_n_spriteAnim;
    sf::Text resume;
    Animation resumeAnim;
    sf::Text newGame;
    Animation newGameAnim;
    sf::Text settings;
    Animation settingsAnim;
    sf::Text exit;
    Animation exitAnim;
    sf::Text year;
    Animation yearAnim;
    //SettingsPanel
    sf::Text settingsText;
    sf::Text fullScreenMode;
    sf::Text screenResolution;
    sf::Text soundVolume;
    sf::Text back;
    PanelActive activePanel = PanelActive::GamePanel;
    sf::Texture tank_texture;
    sf::Sprite tank_sprite;
    Animation tank_spriteAnim;
    int textSelect = 0;
    int maxTextSelect = 4;
private:
    Animation anim;
    void typingText(sf::Text& textObject, const sf::Color& color, const sf::Font& font, unsigned int size, float positionX, float positionY, const sf::String& string);
    void GamePanelHandleEvents(sf::Event event, sf::RenderWindow& m_window);
    void SettingsPanelHandleEvents(sf::Event event);
    virtual bool			handleEvent(const sf::Event& event);

    virtual bool update(const float deltaTime);

    virtual void draw();
};