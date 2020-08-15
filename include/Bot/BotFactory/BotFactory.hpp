#ifndef _BOTFACTORY_HPP
#define _BOTFACTORY_HPP

#include <memory>

#include "Bot/Bot.hpp"
#include "Model/ModelImpl/GameSettings.hpp"

std::shared_ptr<Bot> BotFactory(int difficulty);

#endif //_BOTFACTORY_HPP
