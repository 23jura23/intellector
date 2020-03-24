#ifndef _BOTFACTORY_HPP
#define _BOTFACTORY_HPP
#include <memory>
#include "RandomBot.hpp"
#include "GameSettings.hpp"

std::shared_ptr<Bot> BotFactory(const GameSettings &settings);

#endif //_BOTFACTORY_HPP
