#pragma once

class PackCards_defenition{
	private:
		Card all_cards[36];
		std::deque<Card*> pack_cards;

		Card* trump;

	protected:
		PackCards_defenition() : trump(nullptr){
			//создаем все карты
			for(uint8_t card_suit=1, card_ind=0; card_suit<=4; card_suit++){
				for(uint8_t card_cost=6; card_cost<=14; card_cost++, card_ind++){
					all_cards[card_ind] = Card(card_cost, (CardSuit)card_suit);
				}
			}
			reset();
		}

	public:

		void reset(){
			pack_cards.clear();
			uint8_t indexes[36];
			for(uint8_t i=0; i<36; i++){
				indexes[i] = i;
			}
			std::random_shuffle(indexes, indexes+36);
			for(uint8_t i=0; i<36; i++){
				pack_cards.push_front(&(all_cards[indexes[i]]));
			}

			trump = nullptr;
		}

		Card* pop(){
			if(pack_cards.empty())
				throw "PackCards is empty";

			Card* ret = pack_cards.front();
			pack_cards.pop_front();
			return ret;
		}

		uint8_t count(){
			return pack_cards.size();
		}

		Card* set_trump(){
			if(pack_cards.empty())
				throw "PackCards is empty";

			Card* ret = pack_cards.front();
			pack_cards.pop_front();
			pack_cards.push_back(ret);
			trump = ret;
			return ret;
		}

		Card* get_trump(){
			return trump;
		}

		CardSuit get_trump_suit(){
			if(trump)
				return trump->get_suit();
			return CardSuit::None;
		}
};


class PackCards : public PackCards_defenition{
	private:
		PackCards(){}
		PackCards(const PackCards&){}  
		PackCards& operator=(PackCards&){}
	public:
		static PackCards& get_instance(){
			static PackCards instance;
			return instance;
		}
};