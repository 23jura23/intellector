#ifndef _TESTBOTFACTORY_HPP
#define _TESTBOTFACTORY_HPP

#include <memory>

#include "Bot/Bot.hpp"
#include "Model/ModelImpl/GameSettings.hpp"

std::shared_ptr<Bot> TestBotFactory(const int &type, const int &depth);

#endif //_TESTBOTFACTORY_HPP
