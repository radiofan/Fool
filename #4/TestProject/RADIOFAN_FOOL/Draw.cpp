#include "stdafx.h"
#include "ClassesInclude.h"


void Draw::clear(uint16_t x, uint16_t y, uint16_t w, uint16_t h){
#ifndef TEST

	std::wcout << SColor();
	std::wstring out(w, L' ');
	for(uint8_t i=0; i<h; i++){
		std::wcout << set_coord(x, y+i) << out;
	}
#endif // TEST
}
void Draw::fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, BackColor bc, TextColor tc, wchar_t filler){
#ifndef TEST

	std::wcout << SColor(bc, tc);
	std::wstring out(w, filler);
	for(uint8_t i=0; i<h; i++){
		std::wcout << set_coord(x, y+i) << out;
	}
	std::wcout << SColor();
#endif // TEST
}
void Draw::draw_player_hidden(Player& player, uint16_t x, uint16_t y){
#ifndef TEST

	//очистка
	clear(x, y, 70, 5);

	uint8_t card_c = player.count();
	if(card_c > 9){
		card_c = 9;
	}
	Card tmp = Card();
	for(uint8_t i=0; i<card_c; i++){
		Draw::draw(tmp, x +i*8, y);
	}
	if(player.count() > 9){
		uint8_t shift = 9*7;
		if(player.count() - 8 > 9){
			shift += 2;
		}else{
			shift += 3;
		}
		std::wcout << SColor(BackColor::GREEN, TextColor::RED_DARK) << set_coord(x+shift, y+2)
					<< L"+" << (player.count() - 8);
	}
	std::wcout << set_coord() << SColor();
#endif // TEST
	player.redrawed();
}
void Draw::draw_player_current_open(Player& player, uint16_t x, uint16_t y){
#ifndef TEST

	//очистка
	clear(x, y, 70, 24);
	uint8_t len = player.count();
	uint16_t card_x=x, card_y=y;
	for(uint8_t i=0; i<len; i++){
		Draw::draw(*(player.get_card(i)), card_x, card_y);
		card_x += 8;
		if(card_x - x >= 72){
			card_x = x;
			card_y += 6;
		}
	}

	std::wcout << set_coord() << SColor();
#endif // TEST
	player.redrawed();
}
void Draw::draw_player_current_hidden(Player& player, uint16_t x, uint16_t y){

	//очистка
	clear(x, y, 70, 20);
	draw_player_hidden(player, x, y);
}
void Draw::draw_card_border(uint16_t x, uint16_t y, BackColor bc, TextColor tc){
#ifndef TEST

	std::wcout << SColor(bc, tc)
				<< set_coord(x, y)   << L"┌────┐";
				
	for(uint8_t i=1; i<=3; i++){
	std::wcout << set_coord(x, y+i) << L"│    │";
	}
	std::wcout << set_coord(x, y+4) << L"└────┘";
#endif // TEST
}

void Draw::draw(){
#ifndef TEST

			
	std::wcin.imbue(std::locale(".866"));
	std::wcout.imbue(std::locale(".866"));

	std::wcout << set_coord(0, 0);
	clear(0, 0, 80, 10);
	std::wcout << SColor(BackColor::YELLOW_DARK, TextColor::RED_DARK)
				<< L" ╔════════════════════════════════════════════════════════════════════════════╗ ";
	for(uint8_t i=0; i<11; i++){
	std::wcout << L" ║ " << set_coord(77, 11 + i) << L" ║ ";
	}
	std::wcout << L" ╚════════════════════════════════════════════════════════════════════════════╝ ";
			
	fill(3, 11, 74, 11, BackColor::GREEN_DARK, TextColor::GRAY);

	clear(0, 23, 80, 24);
	std::wcout << set_coord();
#endif // TEST
}

void Draw::draw(BrokenCards_defenition& broken_cards, uint16_t x, uint16_t y){
#ifndef TEST

	if(!broken_cards.count()){
		Draw::draw_card_border(x, y, BackColor::GREEN_DARK, TextColor::GRAY);
	}else{
		Card tmp = Card();
		Draw::draw(tmp, x, y);
		std::wcout << SColor(BackColor::GREEN, TextColor::RED_DARK);
	}
	std::wcout << set_coord(x+2, y+2) << broken_cards.count()
				<< set_coord() << SColor();
	
#endif // TEST
	broken_cards.redrawed();
}
void Draw::draw(Card& card, uint16_t x, uint16_t y, CardDrawType type){
#ifndef TEST


	if(card.get_suit() == CardSuit::None)
		type = CardDrawType::Default;

	fill(
		x, y, 6, 5,
		card.get_suit() == CardSuit::None ? BackColor::GREEN : (type == CardDrawType::SHADDOW ? BackColor::GRAY : BackColor::WHITE),
		TextColor::RED_DARK, card.get_suit() == CardSuit::None ? L'▒' : L' '
	);

	if(type == CardDrawType::SHADDOW){
		fill(x, y, 6, 1, BackColor::WHITE, TextColor::RED_DARK);
	}

	if(card.get_suit() != CardSuit::None){
		std::wcout << SColor(
			type == CardDrawType::SHADDOW ? BackColor::GRAY : BackColor::WHITE,
			CostConvertor::suit2color(card.get_suit())
		);
		std::wcout << set_coord(x+1, y+1) << CostConvertor::cost2letter(card.get_cost());
		if(card.get_cost() == 10){
			std::wcout << L"0";
		}
		std::wcout << set_coord(x+4, y+1) << CostConvertor::suit2letter(card.get_suit());
	}
	std::wcout << set_coord() << SColor();
#endif // TEST
}
void Draw::draw(CardCouple& card_couple, uint16_t x, uint16_t y){
#ifndef TEST

	fill(x, y, 7, 7, BackColor::GREEN_DARK, TextColor::GRAY);

	if(card_couple.get_attack()){
		Draw::draw(*(card_couple.get_attack()), x+1, y, card_couple.get_defense() ? CardDrawType::SHADDOW : CardDrawType::Default);
	}
	if(card_couple.get_defense()){
		Draw::draw(*(card_couple.get_defense()), x, y+2);
	}
#endif // TEST
	card_couple.redrawed();
}
void Draw::draw(PackCards_defenition& pack_cards, uint16_t x, uint16_t y){
#ifndef TEST

	//очистка
	fill(x, y, 10, 6, BackColor::GREEN_DARK, TextColor::GRAY);

	if(pack_cards.get_trump()){
		Card* trump = pack_cards.get_trump();
		if(pack_cards.count()){
			//козырь на месте
			Draw::draw(*trump, x+2, y, pack_cards.count() > 1 ? CardDrawType::SHADDOW : CardDrawType::Default);
		}else{
			//колода пуста но есть козырь
			Draw::draw_card_border(x+2, y, BackColor::GREEN_DARK, TextColor::GRAY);
			if(trump->get_suit() != CardSuit::None){
				std::wcout << set_coord(x+3, y+1) << CostConvertor::cost2letter(trump->get_cost());
				if(trump->get_cost() == 10){
					std::wcout << L"0";
				}
				std::wcout << set_coord(x+6, y+1) << CostConvertor::suit2letter(trump->get_suit());
			}
		}
	}

	if(pack_cards.get_trump() && pack_cards.count() > 1 || !pack_cards.get_trump() && pack_cards.count() > 0){
		fill(x, y+2, 10, 4, BackColor::GREEN, TextColor::RED_DARK, L'▒');
		std::wcout << SColor(BackColor::GREEN, TextColor::RED_DARK)
					<< set_coord(x+4, y+3)
					<< pack_cards.count();
	}

	std::wcout << set_coord() << SColor();
#endif // TEST
	pack_cards.redrawed();
}
void Draw::draw(Player& player, uint16_t x, uint16_t y, PlayerDrawType type){
	switch(type){
		case PlayerDrawType::HIDDEN:
			Draw::draw_player_hidden(player, x, y);
			break;
		case PlayerDrawType::CURRENT_OPEN:
			Draw::draw_player_current_open(player, x, y);
			break;
		case PlayerDrawType::CURRENT_HIDDEN:
			Draw::draw_player_current_hidden(player, x, y);
			break;
	}
}
void Draw::draw(PlayingField_defenition& playing_field, uint16_t x, uint16_t y){
#ifndef TEST


	for(uint8_t i=0; i<playing_field.count(); i++){
		CardCouple& tmp = playing_field.get_card_couple(i);
		if(tmp.is_need_redraw())
			Draw::draw(tmp, x + i*8, y);
	}

	if(playing_field.count() != playing_field.MAX_CARD_COUPLES){
		fill(
			x+playing_field.count()*8,
			y,
			(playing_field.MAX_CARD_COUPLES-playing_field.count())*8,
			7,
			BackColor::GREEN_DARK, TextColor::GRAY
		);
	}
	
#endif // TEST
	playing_field.redrawed();
}
void Draw::draw(App_defenition& app, uint16_t x, uint16_t y){
#ifndef TEST


	std::wcout << set_coord(0, 0)
			   << SColor(BackColor::CYAN_DARK, TextColor::GRAY)
			   << L"  ╔═╤═════════════╦═╤═══════════════╦═╤══════════════╦══════════════╤════════╗  "
			   << L"  ║ │             ║ │               ║ │              ║              │        ║  "
			   << L"  ╚═╧═════════════╩═╧═══════════════╩═╧══════════════╩══════════════╧════════╝  ";
	
	std::wcout << set_coord(3, 1) << SColor(app.can_accept_move() ? BackColor::CYAN : BackColor::GRAY_DARK, TextColor::GRAY)
			   << L"1" << set_coord(5, 1) << L" принять ход";
	if(app.can_accept_cards()){
	std::wcout << set_coord(19, 1) << SColor(app.can_accept_cards() ? BackColor::CYAN : BackColor::GRAY_DARK, TextColor::GRAY)
			   << L"2" << set_coord(21, 1) << L" принять карты";
	}else{
	std::wcout << set_coord(19, 1) << SColor(app.can_accept_cards() ? BackColor::CYAN : BackColor::GRAY_DARK, TextColor::GRAY)
			   << L"2" << set_coord(21, 1) << L" завершить кон";
	}
	std::wcout << set_coord(37, 1) << SColor(app.can_change_move() ? BackColor::CYAN : BackColor::GRAY_DARK, TextColor::GRAY)
			   << L"3" << set_coord(39, 1) << L" передать ход";

	std::wcout << set_coord(54, 1) << SColor(app.current_player() == -1 ? BackColor::CYAN_DARK : (app.current_player() == 0 ? BackColor::RED_DARK : BackColor::BLUE_DARK), TextColor::GRAY)
			   << L" ход икрока ";;
	if(app.current_player() == -1){
		std::wcout << L"  "
				   << set_coord(69, 1) << L"        ";
	}else{
		std::wcout << (app.current_player()+1) << L' '
				   << set_coord(69, 1) << SColor(BackColor::CYAN_DARK, TextColor::GRAY);
		PlayerType tmp = GameLogic::get_instance().get_player(app.current_player())->get_type();
		if(tmp == PlayerType::ATTACKER || tmp == PlayerType::MAIN_ATTACKER){
			std::wcout << L" атака  ";
		}else if(tmp == PlayerType::DEFENDER){
			std::wcout << L" защита ";
		}
	}

	std::wcout << set_coord() << SColor();
#endif // TEST


	//todo отображение выбранных карт
	app.redrawed();
}