#ifndef _BOT_HPP
#define _BOT_HPP

#include <functional>
#include <map>
#include <memory>

class Bot
{
public:
	Bot() = default;
	virtual std::shared_ptr<SimpleMove> makeMove(Game &g) = 0;
};

#endif // _BOT_HPP
