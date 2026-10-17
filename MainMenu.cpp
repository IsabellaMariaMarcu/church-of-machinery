#include "MainMenu.h"

MainMenu::MainMenu() : backgroundTexture("assets/background.png"), backgroundSprite(backgroundTexture) {
	backgroundTexture.setSmooth(false);
}

void MainMenu::draw(sf::RenderWindow& window) const {
	window.draw(backgroundSprite);
}

Dialogue::Dialogue() : DialogueTexture("assets/DialogueBox.png"), DialogueSprite(DialogueTexture) {
	DialogueTexture.setSmooth(false);
}

void Dialogue::draw(sf::RenderWindow& window) const {
	window.draw(DialogueSprite);
}


RobotMenu::RobotMenu() : robotMenuBipedTexture("assets/RobotMenuBiped3.png"), robotMenuBipedSprite(robotMenuBipedTexture),
                         robotMenuQuadrupleTexture("assets/RobotMenuQuadruple1.png"), robotMenuQuadrupleSprite(robotMenuQuadrupleTexture),
                         robotMenuWheelsTexture("assets/RobotMenuWheels2.png"), robotMenuWheelsSprite(robotMenuWheelsTexture) {
	robotMenuBipedTexture.setSmooth(false);
	robotMenuQuadrupleTexture.setSmooth(false);
	robotMenuWheelsTexture.setSmooth(false);

}
void RobotMenu::drawQuadruple(sf::RenderWindow& window) const {
	window.draw(robotMenuQuadrupleSprite);
}
void RobotMenu::drawBiped(sf::RenderWindow& window) const {
	window.draw(robotMenuBipedSprite);
}
void RobotMenu::drawWheels(sf::RenderWindow& window) const {
	window.draw(robotMenuWheelsSprite);
}

ShopMenu::ShopMenu() : shopMenuTexture("assets/Shop.png"), shopMenuSprite(shopMenuTexture) {
	shopMenuTexture.setSmooth(false);
}

void ShopMenu::draw(sf::RenderWindow& window) const {
	window.draw(shopMenuSprite);
}
