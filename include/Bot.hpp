#include "Game.hpp"
#include <memory>

class Bot
{
	virtual std::shared_ptr<SimpleMove> makeMove(Game &b) = 0;
};

class RandomBot : Bot
{
	std::shared_ptr<SimpleMove> makeMove(Game &b) override;
};