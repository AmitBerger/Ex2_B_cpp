#ifndef GAME_H
#define GAME_H

#include "card.hpp"
#include "player.hpp"
#include <string>
#include <vector>

namespace ariel {
class Game {
private:
  Player &player1;
  Player &player2;
  std::vector<Card> pile;
  std::vector<std::string> log;

  double numDraws = 0;
  bool lastTurnDraw = false;
  int drawTemp = 0;
  double numTurns = 0;
  std::string turnLog ;
  int getRoundWinner(Card card1, Card card2);
  bool GameOver();
  void shuffle(std::vector<Card> &pile1);

public:
  Game(Player &player1, Player &player2);
  void playTurn();
  void playAll();
  void printLastTurn() const;
  void printLog() const;
  void printStats() const;
  void printWiner() const;
};
} // namespace ariel

#endif
