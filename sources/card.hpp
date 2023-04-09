#ifndef CARD_HPP
#define CARD_HPP

namespace ariel {

enum class Suit { HEARTS, SPADES, CLUBS, DIAMONDS };



class Card {
private:
  Suit suit;
  int rank;

public:
  Card();
  Card(Suit suit, int rank);
  Suit getSuit() const;
  int getRank() const;
};

} // namespace ariel

#endif /* CARD_HPP */
