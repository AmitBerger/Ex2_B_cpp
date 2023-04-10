#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <string>
#include <vector>

namespace ariel {

class Player {
private:
  std::string name;
  double roundWins = 0;
  int score = 0;
  std::vector<Card> stack;

public:
  Player(std::string name);
  const std::string getName() const;
  int getScore();
  int updateScore(int cards);
  void addCard(Card card);
  Card drawCard();
  int stacksize();
  int cardesTaken();
  double getWinRate();
  void addWin();
};

} // namespace ariel

#endif // PLAYER_HPP