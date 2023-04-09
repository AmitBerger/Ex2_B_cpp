#ifndef GAME_H
#define GAME_H

#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <string>

namespace ariel {
    class Game {
        private:
            Player& player1;
            Player& player2;
            std::vector<Card> pile;
            std::vector<std::string> log;
            int numTurns;
            bool lastTurnDraw = false;
            int drawTemp = 0;
            

            int getRoundWinner(Card card1, Card card2);
            bool isGameOver();
            void shuffle(std::vector<Card>& pile1);

        public:
            Game(Player& player1, Player& player2);

            void playTurn();
            void playAll();
            void printLastTurn() const;
            void printLog() const;
            void printStats() const;
            void printWiner() const;
    };
}

#endif
