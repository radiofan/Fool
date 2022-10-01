#pragma once
class PlayingField_defenition{
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
		}

		uint8_t count(){
			return card_couples.size();
		}

		void add_card_couple(CardCouple& card_couple){
			if(card_couples.size() == MAX_CARD_COUPLES)
				throw L"Count of card couples reached the limit";
			card_couples.push_back(card_couple);
		}

		CardCouple& get_card_couple(uint8_t ind){
			if(ind >= card_couples.size())
				throw L"ind out of range";

			return card_couples[ind];
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