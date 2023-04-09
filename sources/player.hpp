#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <string>
#include <vector>

namespace ariel {

class Player {
public:
  Player(std::string name);
  const std::string getName() const;
  int getScore();
  int updateScore(int cards);
  int getNumCards() const;
  void addCard(Card card);
  Card drawCard();
  int stacksize();
  int cardesTaken();


private:
  std::string name;
  int score;
  std::vector<Card> stack;
};

} // namespace ariel

#endif // PLAYER_HPP