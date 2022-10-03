#pragma once
class PlayingField_defenition : public NeedRedraw{
	private:
		std::vector<CardCouple> card_couples;


	protected:
		PlayingField_defenition(){
			reset();
		}

	public:
		const uint8_t MAX_CARD_COUPLES = 6;

		void reset(){
			card_couples.clear();
			this->need_redraw = true;
		}

		uint8_t count(){
			return (uint8_t)card_couples.size();
		}

		uint8_t broken_couples_count(){
			uint8_t ret = 0;
			for(uint8_t i=0; i<card_couples.size(); i++){
				if(card_couples[i].is_broken())
					ret++;
			}
			return ret;
		}

		uint8_t not_broken_couples_count(){
			return card_couples.size() - broken_couples_count();
		}

		void add_card_couple(CardCouple& card_couple){
			if(card_couples.size() == MAX_CARD_COUPLES)
				throw L"Count of card couples reached the limit";
			card_couples.push_back(card_couple);
			this->need_redraw = true;
		}

		void add_card_couple(){
			if(card_couples.size() == MAX_CARD_COUPLES)
				throw L"Count of card couples reached the limit";
			card_couples.push_back(CardCouple());
			this->need_redraw = true;
		}

		CardCouple& get_card_couple(uint8_t ind){
			if(ind >= card_couples.size())
				throw L"ind out of range";
			
			return card_couples[ind];
		}

		bool is_all_card_couples_broken(){
			for(uint8_t i=0; i<card_couples.size(); i++){
				if(!card_couples[i].is_broken())
					return false;
			}
			
			return true;
		}

		bool can_add_card_couple(){
			return card_couples.size() < MAX_CARD_COUPLES;
		}

		void move_cards_to_broken(){
			BrokenCards& broken_cards = BrokenCards::get_instance();
			for(uint8_t i=0; i<card_couples.size(); i++){
				broken_cards.add(card_couples[i]);
			}
			this->reset();
		}

		void move_couple_to_player(uint8_t couple_ind, Player& player){
			if(couple_ind >= card_couples.size())
				throw L"couple_ind out of range";

			CardCouple tmp = card_couples[couple_ind];
			if(tmp.get_defense()){
				player.add(tmp.get_defense());
			}
			if(tmp.get_attack()){
				player.add(tmp.get_attack());
			}
			card_couples.erase(card_couples.begin()+couple_ind);
			for(couple_ind; couple_ind<card_couples.size(); couple_ind++){
				card_couples[couple_ind].set_need_redraw();
			}
			need_redraw = true;
		}

		bool can_add_attack_card(Card& attack){
			if(!card_couples.size())
				return true;
			for(uint8_t i=0; i<card_couples.size(); i++){
				if(card_couples[i].get_defense() && card_couples[i].get_defense()->get_cost() == attack.get_cost()
				|| card_couples[i].get_attack() && card_couples[i].get_attack()->get_cost() == attack.get_cost()
				){
					return true;
				}
			}
			return false;
		}

		int8_t get_right_not_broken_couple(int8_t ind){
			if(ind >= card_couples.size()-1 || ind < 0)
				ind = -1;
			int8_t ret = -1;
			for(int8_t start = ind+1; start<card_couples.size(); start++){
				if(!card_couples[start].is_broken()){
					ret = start;
					break;
				}
			}
			if(ret != -1)
				return ret;
			for(int8_t start = 0; start<=ind; start++){
				if(!card_couples[start].is_broken()){
					ret = start;
					break;
				}
			}
			return ret;
		}

		int8_t get_left_not_broken_couple(int8_t ind){
			if(ind >= card_couples.size() || ind <= 0)
				ind = card_couples.size();
			int8_t ret = -1;
			for(int8_t end = ind-1; end>=0; end--){
				if(!card_couples[end].is_broken()){
					ret = end;
					break;
				}
			}
			if(ret != -1)
				return ret;
			for(int8_t end = card_couples.size()-1; end>=ind; end--){
				if(!card_couples[end].is_broken()){
					ret = end;
					break;
				}
			}
			return ret;
		}

		void set_need_redraw_couple(int8_t ind){
			need_redraw = true;
			if(ind >= card_couples.size())
				return;
			get_card_couple(ind).set_need_redraw();
		}
};

class PlayingField : public PlayingField_defenition{
	private:
		PlayingField(){}
		PlayingField(const PlayingField&){}  
		PlayingField& operator=(PlayingField&){}
	public:
		static PlayingField& get_instance(){
			static PlayingField instance;
			return instance;
		}
};