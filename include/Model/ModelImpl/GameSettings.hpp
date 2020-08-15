#ifndef _GAMESETTINGS_HPP
#define _GAMESETTINGS_HPP

class GameSettings {
   public:
    GameSettings(int difficulty_white, int difficulty_black, bool first, bool second)
            : difficulty_white_(difficulty_white)
            , difficulty_black_(difficulty_black)
            , first_player_(first)
            , second_player_(second){};

    [[nodiscard]] int difficulty_white() const {
        return difficulty_white_;
    }

    [[nodiscard]] int difficulty_black() const {
        return difficulty_black_;
    }

    [[nodiscard]] bool first_player() const {
        return first_player_;
    }

    [[nodiscard]] bool second_player() const {
        return second_player_;
    }

    void set_difficulty_white(int x) {
        difficulty_white_ = x;
    }

    void set_difficulty_black(int x) {
        difficulty_black_ = x;
    }

    void set_first_player(bool x) {
        first_player_ = x;
    }

    void set_second_player(bool x) {
        second_player_ = x;
    }

   private:
    int difficulty_white_ = 0;  // white bot's difficulty
    int difficulty_black_ = 0;  // black bot's difficulty
    bool first_player_ = 0;     // 0 - player, 1 - bot
    bool second_player_ = 0;    // 0 - player, 1 - bot
};

#endif  //_GAMESETTINGS_HPP
