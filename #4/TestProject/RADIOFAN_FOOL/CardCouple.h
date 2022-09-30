#pragma once
class CardCouple{
	private:
		Card* attack;
		Card* defense;
	public:
		CardCouple()	: attack(nullptr), defense(nullptr){}

		Card* get_attack(){
			return attack;
		}
		Card* get_defense(){
			return defense;
		}

		bool set_attack(Card* Attack){
			if(attack)
				return false;
			attack = Attack;
			return true;
		}

		bool set_defense(Card* Defense, CardSuit Trump_card = None){
			if(!defense)
				return false;
			if(can_set_defense(Defense, Trump_card)){
				defense = Defense;
				return true;
			}
			return false;
		}

		bool is_broken(){
			return !defense;
		}

		bool can_set_defense(Card* Defense, CardSuit Trump_card = None){
			if(!attack)
				return false;								//отсутсвует атакующая карта, нечего защищать

			if(attack->get_suit() == Defense->get_suit()	//масти равны
			&& attack->get_cost() <  Defense->get_cost()){	//стоимость защиты больше атаки
				return true;								//бьем
			}

			if(Trump_card == Defense->get_suit()			//защитная карта - козырь
			&& attack->get_suit() != Defense->get_suit()){	//атакующая другой масти
				return true;								//бьем
			}

			return false;									//во всех других случаях не бьем
		}
};