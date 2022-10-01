#pragma once

enum class PlayerType{
	None,
	ATTACKER,
	DEFENDER,
	MAIN_ATTACKER
};

class Player{
	private:
		PlayerType type;

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
			//todo расширить
			return 0;
		}
};