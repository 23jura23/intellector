#include <memory>
#include "BotFactory.hpp"

std::shared_ptr<Bot> BotFactory(const GameSettings &settings)
{
	void(settings.difficulty());
	std::shared_ptr<Bot> bot = std::reinterpret_pointer_cast<Bot>(std::make_shared<RandomBot>());
	return bot;
}
