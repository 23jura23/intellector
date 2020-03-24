#ifndef _GAMESETTINGS_HPP
#define _GAMESETTINGS_HPP

class GameSettings
{
public:
	int difficulty() const { return difficulty_; };
	bool first_player() const { return first_player_; };
	bool second_player() const { return second_player_; };
private:
	int difficulty_ = 0; // bot's difficulty
	bool first_player_ = 0; // 0 - player, 1 - bot
	bool second_player_ = 0; // 0 - player, 1 - bot
};

#endif //_GAMESETTINGS_HPP
