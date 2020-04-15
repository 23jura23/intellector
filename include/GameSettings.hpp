#ifndef _GAMESETTINGS_HPP
#define _GAMESETTINGS_HPP

class GameSettings 
{
   public:
    GameSettings(int diff, bool first, bool second)
            : difficulty_(diff)
            , first_player_(first)
            , second_player_(second) {};

    [[nodiscard]] int difficulty() const 
    {
        return difficulty_;
    }

    [[nodiscard]] bool first_player() const 
    {
        return first_player_;
    }

    [[nodiscard]] bool second_player() const 
    {
        return second_player_;
    }

   private:
    int difficulty_ = 0;      // bot's difficulty
    bool first_player_ = 0;   // 0 - player, 1 - bot
    bool second_player_ = 0;  // 0 - player, 1 - bot
};

#endif  //_GAMESETTINGS_HPP
