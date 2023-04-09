#include "game.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>

namespace ariel {
Game::Game(Player &player1, Player &player2)
    : player1(player1), player2(player2) {

  for (int i = 1; i <= 13; i++) {
    this->pile.push_back(Card(Suit::CLUBS, i));
    this->pile.push_back(Card(Suit::DIAMONDS, i));
    this->pile.push_back(Card(Suit::HEARTS, i));
    this->pile.push_back(Card(Suit::SPADES, i));
  }

  shuffle(this->pile);
  for (unsigned long int i = 0; i < 26; i++) {
    player1.addCard(pile[i]);
  }
  for (unsigned long int i = 26; i < 52; i++) {
    player2.addCard(pile[i]);
  }
}
void Game::shuffle(std::vector<Card> &pile1) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(pile1.begin(), pile1.end(), g); // used geekforgeeks
}

int Game::getRoundWinner(Card card1, Card card2) {
  if (card1.getRank() == card2.getRank()) {
    return 0; // tie
  } else if (card1.getRank() == 1 && card2.getRank() == 2) {
    return 2; // player 2 wins
  } else if (card2.getRank() == 1 && card1.getRank() == 2) {
    return 1; // player 1 wins
  } else if (card1.getRank() > card2.getRank() ||
             (card1.getRank() == 1 && card2.getRank() != 2)) {
    return 1; // player 1 wins
  } else if (card2.getRank() > card1.getRank() ||
             (card2.getRank() == 1 && card1.getRank() != 2)) {
    return 2; // player 2 wins
  } else {
    throw "not good";
  }
}

bool Game::isGameOver() {
  return player1.stacksize() > 0 || player2.stacksize() > 0;
}

void Game::playTurn() {

  if (&player1 == &player2) {
    throw "must be two diffrent players!";
  }
  if (!isGameOver()) {
    throw "no cards left!";
  }
  int cardsInWar = 2;
  Card p1c = player1.drawCard();
  Card p2c = player2.drawCard();

  if (lastTurnDraw) {
    cardsInWar = cardsInWar + this->drawTemp;
  }

  int roundWinner = getRoundWinner(p1c, p2c);

  if (roundWinner == 1) {
    this->lastTurnDraw = false;

    player1.updateScore(cardsInWar + drawTemp);
    this->drawTemp = 0;
  }
  if (roundWinner == 2) {
    this->lastTurnDraw = false;

    player2.updateScore(cardsInWar + drawTemp);
    drawTemp = 0;
  }
  if (roundWinner == 0) {

    if (!isGameOver()) {

      player1.updateScore((drawTemp + cardsInWar) / 2);
      player2.updateScore((drawTemp + cardsInWar) / 2);
    }
    if (player1.stacksize() > 0 && player2.stacksize() > 0) {
      player1.drawCard();
      player2.drawCard();
      drawTemp = drawTemp + 2;
      lastTurnDraw = true;
    }
  }
}

void Game::playAll() {
  while (isGameOver()) {
    playTurn();
  }
}

void Game::printLastTurn() const {}

void Game::printLog() const {}
void Game::printStats() const {}

void Game::printWiner() const {
  if (player1.getScore() > player2.getScore()) {
    std::cout << player1.getName() << " is the Winner!!!" << std::endl;
  } else if (player1.getScore() < player2.getScore()) {
    std::cout << player2.getName() << " is the Winner!!!" << std::endl;
  } else {
    std::cout << "its a tie game!!!" << std::endl;
  }
}

} // namespace ariel