#pragma once
#include "GameObject.h"
#include <string.h>

class Item :
	public GameObject
{
public:
	Item() = default;
	~Item();

	virtual void init(ASGE::Renderer * renderer, std::string data[]) override;
	virtual void render(ASGE::Renderer* renderer, Player &birdman, POINT cursorPos) override;

	std::string getLabel();

	void setPosition(int new_x, int new_y);
	void setTexture(std::string new_sprite, std::string new_outline);
	void setLabel(std::string new_label);
	void setCombi(std::string new_combi);
	void setCombo(std::string new_combo);

private:
	std::string label;
	std::string combi;
	std::string combo;
};
