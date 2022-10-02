#pragma once

enum class PlayerType{
	None,
	ATTACKER,
	DEFENDER,
	MAIN_ATTACKER
};

class Player : public NeedRedraw{
	private:
		PlayerType type;
		std::vector<Card*> cards;

	public:
		Player()	:	type(PlayerType::None){}

		PlayerType get_type(){
			return type;
		}

		void set_type(PlayerType Type){
			if(Type < PlayerType::None || Type > PlayerType::MAIN_ATTACKER)
				throw L"Type out of range";
			type = Type;
		}

		uint8_t count(){
			return (uint8_t)cards.size();
		}

		void add(Card* card){
			uint8_t L = 0,
					R = (uint8_t)cards.size(),
					ind = L + (R - L) / 2;
			int32_t diff;
 
			while(L != R){
				ind = L + (R - L) / 2;
				/*
				diff = card->get_cost() + (int)card->get_suit() * ((int)CardSuit::Spade+1)
					 - cards[ind]->get_cost() + (int)cards[ind]->get_suit() * ((int)CardSuit::Spade+1);
					 */
				diff = (int64_t)card - (int64_t)cards[ind];//сортируем по указателям
				if(diff > 0){
					L = ind + 1;
				}else{
					R = ind;
				}
			}
			cards.insert(cards.begin()+L, card);
			this->need_redraw = true;
		}

		Card* get_card(uint8_t ind){
			if(ind >= cards.size())
				throw L"ind out of range";

			return cards[ind];
		}

		Card* take_card(uint8_t ind){
			if(ind >= cards.size())
				throw L"ind out of range";

			Card* ret = cards[ind];
			cards.erase(cards.begin() + ind);
			this->need_redraw = true;
			return ret;
		}
};