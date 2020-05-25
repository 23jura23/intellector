#ifndef _BOTFACTORY_HPP
#define _BOTFACTORY_HPP

#include <memory>
#include "GameSettings.hpp"
#include "Bot.hpp"

std::shared_ptr<Bot> BotFactory(int difficulty);

#endif //_BOTFACTORY_HPP
