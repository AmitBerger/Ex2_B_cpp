#include "player.hpp"
#include "card.hpp"
#include <algorithm>
#include <random>

namespace ariel {

Player::Player(std::string name) {
  this->name = name;
  this->stack.clear();
  this->score = 0;
}

int Player::stacksize() { return stack.size(); }

int Player::updateScore(int cards) { 
  return this->score = score + cards; }

int Player::cardesTaken() { return score; }

const std::string Player::getName() const { return name; }

int Player::getScore() { return score; }

void Player::addCard(Card card) { this->stack.push_back(card); }

Card Player::drawCard() {
  Card tempCard = this->stack.back();
  this->stack.pop_back();
  return tempCard;
}

} // namespace ariel
