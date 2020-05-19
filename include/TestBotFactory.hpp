#ifndef _TESTBOTFACTORY_HPP
#define _TESTBOTFACTORY_HPP

#include <memory>
#include "GameSettings.hpp"
#include "Bot.hpp"

std::shared_ptr<Bot> TestBotFactory(const int &type, const int &depth);

#endif //_TESTBOTFACTORY_HPP
