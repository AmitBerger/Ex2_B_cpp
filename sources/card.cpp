#include "card.hpp"

namespace ariel {

Card::Card() : suit(Suit::HEARTS), rank(2) {}

Card::Card(Suit suit, int rank) : suit(suit), rank(rank) {}

Suit Card::getSuit() const {
  return suit;
}

int Card::getRank() const {
  return rank;
}

} // namespace ariel
