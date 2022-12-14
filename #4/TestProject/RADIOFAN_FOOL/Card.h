#pragma once

enum class CardSuit{
	None,
	Diamond,
	Heart,
	Club,
	Spade
};

class Card{
	private:
		CardSuit suit;
		uint8_t cost;
	public:
		Card()  : suit(CardSuit::None), cost(0){}
		Card(uint8_t Cost, CardSuit Suit){
			if(Cost < 2 || Cost > 14)
				throw "Cost out of range 2-14";
			cost = Cost;

			if(Suit < CardSuit::Diamond || Suit > CardSuit::Spade)
				throw "Suit out of range";
			suit = Suit;
		}

		uint8_t get_cost(){
			return cost;
		}

		CardSuit get_suit(){
			return suit;
		}
};