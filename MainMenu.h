#pragma once
#include <SFML/Graphics.hpp>

class MainMenu {
public:
	MainMenu();
	void draw(sf::RenderWindow& window) const;
	

private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
};

class Dialogue {
public:
	Dialogue();
	void draw(sf::RenderWindow& window) const;
private:
	sf::Texture DialogueTexture;
	sf::Sprite DialogueSprite;

};

class RobotMenu {
public:
	RobotMenu();
	void drawBiped(sf::RenderWindow& window) const;
	void drawQuadruple(sf::RenderWindow& window) const;
	void drawWheels(sf::RenderWindow& window) const;
private:
	sf::Texture robotMenuBipedTexture;
	sf::Sprite robotMenuBipedSprite;
	sf::Texture robotMenuQuadrupleTexture;
	sf::Sprite robotMenuQuadrupleSprite;
	sf::Texture robotMenuWheelsTexture;
	sf::Sprite robotMenuWheelsSprite;
};

class ShopMenu {
public:
	ShopMenu();
	void draw(sf::RenderWindow& window) const;
private:
	sf::Texture shopMenuTexture;
	sf::Sprite shopMenuSprite;
};
