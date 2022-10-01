#pragma once

class BrokenCards_defenition : public NeedRedraw{
	private:
		std::deque<Card*> broken_cards;


	protected:
		BrokenCards_defenition(){
			reset();
		}

	public:

		void reset(){
			broken_cards.clear();
			this->need_redraw = true;
		}

		uint8_t count(){
			return broken_cards.size();
		}

		void add(CardCouple& card_couple){
			if(card_couple.get_defense()){
				broken_cards.push_front(card_couple.get_defense());
				this->need_redraw = true;
			}
			if(card_couple.get_attack()){
				broken_cards.push_front(card_couple.get_attack());
				this->need_redraw = true;
			}
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