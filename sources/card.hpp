#ifndef CARD_HPP
#define CARD_HPP

#include <string>
namespace ariel {

enum class Suit { HEARTS, SPADES, CLUBS, DIAMONDS };

class Card {
private:
  Suit suit;
  int rank;
  std::string rank_to_string(int rank);
  std::string suit_to_string(Suit suit);

public:
  Card();
  Card(Suit suit, int rank);
  Suit getSuit() const;
  int getRank() const;

  std::string to_string();
};

} // namespace ariel

#endif /* CARD_HPP */
