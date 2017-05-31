#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"

class Viewer
{
	Model* model;
	sf::RenderWindow* window;
	sf::View view;
	sf::View viewUI;
	sf::Font font;
	sf::Text text;
	sf::Vector2f max_size, min_size;
	std::vector<sf::Sprite> constant_sprite;
	std::vector<sf::Sprite> flexible_sprite;
	std::vector<sf::Sprite> UI_sprite;
	std::vector<sf::Texture> texture;
	void prepareNewLevel();
	void update();
	void updateUI();
	sf::Sprite setSprite(Object it);
	void centerViewOnHero();
	void changeZoom(bool make_closer);
public:
	Viewer();
	void setModelPtr(Model*);
	void handleViewerEvent(ViewEvents);
};
