#include "game.hpp"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>
#include <string>

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
  } else if (((card1.getRank() > card2.getRank()) && card2.getRank() != 1) ||
             (card1.getRank() == 1 && card2.getRank() != 2)) {
    return 1; // player 1 wins
  } else if (((card2.getRank() > card1.getRank()) && card1.getRank() != 1) ||
             (card2.getRank() == 1 && card1.getRank() != 2)) {
    return 2; // player 2 wins
  } else {
    throw "not good";
  }
}

bool Game::GameOver() {
  return player1.stacksize() == 0 || player2.stacksize() == 0;
}

void Game::playTurn() {

  if (&player1 == &player2) {
    throw "must be two diffrent players!";
  }
  if (GameOver()) {
    throw "no cards left!";
  }

  Card p1c = player1.drawCard();
  Card p2c = player2.drawCard();
  int cardsInWar = 2;
  numTurns++;
  int roundWinner = getRoundWinner(p1c, p2c);
  if (lastTurnDraw) {

    this->turnLog = turnLog + player1.getName() + " played " + p1c.to_string() +
                    ". " + player2.getName() + " played " + p2c.to_string() +
                    ". ";
  } else {
    turnLog.clear();
    this->turnLog = player1.getName() + " played " + p1c.to_string() + ". " +
                    player2.getName() + " played " + p2c.to_string() + ". ";
  }

  if (lastTurnDraw && !GameOver()) {
    cardsInWar = cardsInWar + drawTemp;
    player1.drawCard();
    player2.drawCard();
  }

  if (roundWinner == 1) {

    turnLog = turnLog + player1.getName() + " wins.";
    log.push_back(turnLog);
    lastTurnDraw = false;
    player1.addWin();
    player1.updateScore(cardsInWar + drawTemp);
    drawTemp = 0;
  }
  if (roundWinner == 2) {

    turnLog = turnLog + player2.getName() + " wins.";
    log.push_back(turnLog);
    lastTurnDraw = false;
    player2.addWin();
    player2.updateScore(cardsInWar + drawTemp);
    drawTemp = 0;
  }
  if (roundWinner == 0) {

    turnLog = turnLog + "draw. ";
    numDraws++;
    if (numDraws == 13) {
      log.push_back(turnLog);
      player1.updateScore(26);
      player2.updateScore(26);
      cardsInWar = 0;
      drawTemp = 0;
    }

    if (GameOver() && numDraws < 13) {
      drawTemp = drawTemp + cardsInWar;
      player1.updateScore((drawTemp) / 2);
      player2.updateScore((drawTemp) / 2);
    } else if (!GameOver()) {

      drawTemp = drawTemp + 2;
      lastTurnDraw = true;
    }

    if (!GameOver() && numDraws < 13) {
      playTurn();
    }
  }
}

void Game::playAll() {
  while (!GameOver()) {
    playTurn();
  }
}

void Game::printLastTurn() const {
  if (log.size() == 0) {
    throw "the game did not start!";
  }
  std::cout << log.back() << std::endl;
}

void Game::printLog() const {
  if (log.size() == 0) {
    throw "the game did not start!";
  }
  for (std::string turns : log) {
    std::cout << turns << std::endl;
  }
}
void Game::printStats() const {
  if (log.size() == 0) {
    throw "the game did not start!";
  }
  std::cout << "Player 1 (" << player1.getName() << "):" << std::endl;
  std::cout << "Win rate: " << (player1.getWinRate() / numTurns) * 100 << "%"
            << std::endl;
  std::cout << "Cards won: " << player1.cardesTaken() << std::endl;
  std::cout << "Turns won: " << player1.getWinRate() << std::endl;
  std::cout << "Draw rate: " << (numDraws / numTurns) * 100 << "%" << std::endl;
  std::cout << std::endl;

  std::cout << "Player 2 (" << player2.getName() << "):" << std::endl;
  std::cout << "Win rate: " << (player2.getWinRate() / numTurns) * 100 << "%"
            << std::endl;
  std::cout << "Cards won: " << player2.cardesTaken() << std::endl;
  std::cout << "Turns won: " << player2.getWinRate() << std::endl;
  std::cout << "Draw rate: " << (numDraws / numTurns) * 100 << "%" << std::endl;
  std::cout << std::endl;

  std::cout << "Number of draws: " << this->numDraws << std::endl;
}

void Game::printWiner() const {
  if (log.size() == 0) {
    throw "the game did not start!";
  }
  if (player1.getScore() > player2.getScore()) {
    std::cout << player1.getName() << " is the Winner!!!" << std::endl;
  } else if (player1.getScore() < player2.getScore()) {
    std::cout << player2.getName() << " is the Winner!!!" << std::endl;
  } else {
    std::cout << "its a tie game!!!" << std::endl;
  }
}

} // namespace ariel