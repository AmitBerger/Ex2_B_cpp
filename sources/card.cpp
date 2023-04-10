#include "card.hpp"
#include <string>

namespace ariel {

Card::Card() : suit(Suit::HEARTS), rank(2) {}

Card::Card(Suit suit, int rank) : suit(suit), rank(rank) {}

Suit Card::getSuit() const { return suit; }

int Card::getRank() const { return rank; }

std::string Card::rank_to_string(int rank) {
  if (rank == 1) {
    return "ACE";
  }
  if (rank == 11) {
    return "JACK";
  }
  if (rank == 12) {
    return "QUEEN";
  }
  if (rank == 13) {
    return "KING";
  } else
    return std::to_string(rank);
}
std::string Card::suit_to_string(Suit suit) {
  if (suit == Suit::CLUBS) {
    return "CLUBS";
  }
  if (suit == Suit::SPADES) {
    return "SPADES";
  }
  if (suit == Suit::DIAMONDS) {
    return "DIAMONDS";
  }
  if (suit == Suit::HEARTS) {
    return "HEARTS";
  }
  return "";
}

std::string Card::to_string() {

  return rank_to_string(this->rank) + " of " + suit_to_string(this->suit);
}

} // namespace ariel
