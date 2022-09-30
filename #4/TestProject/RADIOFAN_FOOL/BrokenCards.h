#pragma once

class BrokenCards_defenition{
	private:
		std::deque<Card*> broken_cards;


	protected:
		BrokenCards_defenition(){
			reset();
		}

	public:

		void reset(){
			broken_cards.clear();
		}

		uint8_t count(){
			return broken_cards.size();
		}

		void add(CardCouple& card_couple){
			if(card_couple.get_defense())
				broken_cards.push_front(card_couple.get_defense());
			if(card_couple.get_attack())
				broken_cards.push_front(card_couple.get_attack());
		}
};


class BrokenCards : public BrokenCards_defenition{
	private:
		BrokenCards(){}
		BrokenCards(const BrokenCards&){}  
		BrokenCards& operator=(BrokenCards&){}
	public:
		static BrokenCards& get_instance(){
			static BrokenCards instance;
			return instance;
		}
};