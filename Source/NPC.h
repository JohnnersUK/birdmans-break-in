#include "GameObject.h"
#include "Item.h"

class NPC :
	public GameObject
{
public:
	NPC() = default;
	~NPC();

	virtual void init(ASGE::Renderer * renderer, std::string data[]) override;
	virtual void render(ASGE::Renderer* renderer, Player &birdman, POINT cursorPos) override;

	void trade(ASGE::Renderer* renderer, std::vector<Item*> inventory);
	bool checkCollision(POINT cursorPos, ASGE::Renderer* renderer, std::vector<Item*> inventory);
	bool checkComplete();

	void setTexture(std::string dir);

private:
	bool complete = false;

	std::string text;
	std::string clue;
	std::string take;
	std::string give;
};