#ifndef GAMEPOINTS_H
#define GAMEPOINTS_H

#include <string>

class GamePoints
{
    public:
        GamePoints();
        virtual ~GamePoints();

        int getScores();
        int getLives();
        std:: string getEndState();
        int getLevelNumber();
        bool is_changed_color;

        bool isChangedLives();
        bool isChangedColor();
        void updateScores( int add_value );
        void updateLives( int add_value );
        void updateLevel ( int add_value );
        void resetLevel();
        void endGame( std:: string state );

        void resetData();

        void changeTextColor();

    private:
        static int scores;
        static int lives;
        static int level;

        static bool changed_lives;
        static std:: string end_state;
};

#endif // GAMEPOINTS_H
