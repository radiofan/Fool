#include "stdafx.h"
#include "ClassesInclude.h"

const wchar_t CostConvertor::cost_to_letter[] = {L'1', L'В', L'Д', L'К', L'Т'};


std::wostream& operator<<(std::wostream& os, const SColor& color){
	color.set_color();
	return os;
}
std::wostream& operator<<(std::wostream& os, const set_coord& tmp){
	tmp.set();
	return os;
}

int32_t wmain(int32_t argc, wchar_t* argv[]){
	Draw::draw(App::get_instance(), 0, 0);
			
	std::vector<Card> all_cards(36);
	for(uint8_t card_suit=1, card_ind=0; card_suit<=4; card_suit++){
		for(uint8_t card_cost=6; card_cost<=14; card_cost++, card_ind++){
			all_cards[card_ind] = Card(card_cost, (CardSuit)card_suit);
		}
	}

	Draw::draw(PackCards::get_instance(), 66, 14);
	Draw::draw(BrokenCards::get_instance(), 4, 14);

	for(uint8_t i=0; i<6; i++){
		PlayingField::get_instance().add_card_couple();
		PlayingField::get_instance().get_card_couple(i).set_attack(&all_cards[i]);
		Draw::draw(PlayingField::get_instance(), 15, 13);
		Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
		PlayingField::get_instance().get_card_couple(i).set_defense(&all_cards[i+9], all_cards[i+9].get_suit());
		Draw::draw(PlayingField::get_instance(), 15, 13);
		Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
	}

	/*
	Player hidden = Player();
	Player current = Player();

	Draw::draw(hidden,  4, 4, PlayerDrawType::HIDDEN);
	Draw::draw(current, 4, 24, PlayerDrawType::CURRENT_HIDDEN);
	Draw::draw(PackCards::get_instance(), 66, 14);

	Draw::draw(BrokenCards::get_instance(), 4, 14);
	Draw::draw(PackCards::get_instance(), 66, 14);
	Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
	PackCards::get_instance().set_trump();
	Draw::draw(PackCards::get_instance(), 66, 14);
	*/
	/*
	for(uint8_t i=0; i<18; i++){
		Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
		hidden.add(PackCards::get_instance().pop());
		Draw::draw(PackCards::get_instance(), 66, 14);
		Draw::draw(hidden,  4, 4, PlayerDrawType::HIDDEN);

		Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
		current.add(PackCards::get_instance().pop());
		Draw::draw(PackCards::get_instance(), 66, 14);
		Draw::draw(current, 4, 24, PlayerDrawType::CURRENT_HIDDEN);
	}

	Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
	Draw::draw(current, 4, 24, PlayerDrawType::CURRENT_OPEN);
	*/

	/*
	for(uint8_t i=0; i<36; i++){
		Sleep(App::get_instance().CARD_DISTRIBUTION_DELAY_MS);
		current.add(PackCards::get_instance().pop());
		Draw::draw(PackCards::get_instance(), 66, 14);
		Draw::draw(current, 4, 24, PlayerDrawType::CURRENT_OPEN);
	}
	*/

	_getch();
	return 0;
}