#pragma once

class GameLogic_defenition{
	private:
		Player players[2];


	protected:
		GameLogic_defenition(){
			reset();
		}

	public:

		void reset(){
			players[0] = Player();
			players[1] = Player();
			BrokenCards::get_instance().reset();
			PlayingField::get_instance().reset();
			PackCards::get_instance().reset();
		}

		Player* get_player(uint8_t ind){
			if(ind > 1)
				throw L"ind out of range";
			return &players[ind];
		}

		uint8_t get_first_player(){
			CardSuit trump_suit = PackCards::get_instance().get_trump_suit();

			int8_t min_1 = INT8_MAX, min_2 = INT8_MAX;
			for(uint8_t i=0; i<players[0].count(); i++){
				if(players[0].get_card(i)->get_suit() == trump_suit){
					if(players[0].get_card(i)->get_cost() < min_1){
						min_1 = players[0].get_card(i)->get_cost();
					}
				}
			}
			for(uint8_t i=0; i<players[1].count(); i++){
				if(players[1].get_card(i)->get_suit() == trump_suit){
					if(players[1].get_card(i)->get_cost() < min_2){
						min_2 = players[1].get_card(i)->get_cost();
					}
				}
			}

			uint8_t first;

			if(min_1 == min_2){
				first = (rand() & 0x01);
			}else{
				first = min_2 < min_1;
			}

			players[first].set_type(PlayerType::MAIN_ATTACKER);
			players[get_another_player_ind(first)].set_type(PlayerType::DEFENDER);

			return first;
		}

		uint8_t get_another_player_ind(uint8_t ind){
			return ind ? 0 : 1;
		}
};


class GameLogic : public GameLogic_defenition{
	private:
		GameLogic(){}
		GameLogic(const GameLogic&){}  
		GameLogic& operator=(GameLogic&){}
	public:
		static GameLogic& get_instance(){
			static GameLogic instance;
			return instance;
		}
};