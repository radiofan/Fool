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