#pragma once
#include <SFML/Graphics.hpp>
#include "Layer.h"

class Display
{
protected:
	Layer* layer;
	sf::RenderWindow* window;
	sf::View view;
	std::vector<sf::Sprite> constant_sprite;
	std::vector<sf::Texture> texture;
	sf::Sprite setSprite(Object it);
	sf::Sprite setDynamicSprite(Object it);
	void loadDisplay();
public:
	Display(Layer* _layer);
	virtual void changeScale(double x, double y);
	virtual void handleViewerEvent(ViewEvents);
	virtual void update();
};