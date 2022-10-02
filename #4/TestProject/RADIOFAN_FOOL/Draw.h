#pragma once

class App_defenition;

enum class PlayerDrawType{
	HIDDEN,
	CURRENT_HIDDEN,
	CURRENT_OPEN
};

enum class CardDrawType{
	Default,
	SHADDOW
};

class Draw{
	private:
		static void clear(uint16_t x, uint16_t y, uint16_t w, uint16_t h){
			std::wcout << SColor();
			std::wstring out(w, L' ');
			for(uint8_t i=0; i<h; i++){
				std::wcout << set_coord(x, y+i) << out;
			}
		}
		static void fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, BackColor bc, TextColor tc, wchar_t filler = L' '){
			std::wcout << SColor(bc, tc);
			std::wstring out(w, filler);
			for(uint8_t i=0; i<h; i++){
				std::wcout << set_coord(x, y+i) << out;
			}
			std::wcout << SColor();
		}
		static void draw_player_hidden(Player& player, uint16_t x, uint16_t y){
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
			player.redrawed();
		}
		static void draw_player_current_open(Player& player, uint16_t x, uint16_t y){
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
			player.redrawed();
		}
		static void draw_player_current_hidden(Player& player, uint16_t x, uint16_t y){
			//очистка
			clear(x, y, 70, 20);
			draw_player_hidden(player, x, y);
		}
		static void draw_card_border(uint16_t x, uint16_t y, BackColor bc, TextColor tc){
			std::wcout << SColor(bc, tc)
					   << set_coord(x, y)   << L"┌────┐";
				
			for(uint8_t i=1; i<=3; i++){
			std::wcout << set_coord(x, y+i) << L"│    │";
			}
			std::wcout << set_coord(x, y+4) << L"└────┘";
		}

	public:
		static void draw(){
			
			std::wcin.imbue(std::locale(".866"));
			std::wcout.imbue(std::locale(".866"));

			std::wcout << set_coord(0, 0);
			clear(0, 0, 80, 10);
			/*
			<< SColor(BackColor::YELLOW_DARK, TextColor::GRAY)
					   << L" ╔═╤═════════════╦═╤═══════════════╦═╤══════════════╦══════════════╤════════╗ " << std::endl
					   << L" ║" << SColor(BackColor::GRAY_DARK, TextColor::GRAY) << L"1"
					   << SColor(BackColor::YELLOW_DARK, TextColor::GRAY) << L"│" << SColor(BackColor::GRAY_DARK, TextColor::GRAY)
					   << L" принять ход" << SColor(BackColor::YELLOW_DARK, TextColor::GRAY)
					   << L" ║" << SColor(BackColor::GRAY_DARK, TextColor::GRAY) << L"2"
					   << SColor(BackColor::YELLOW_DARK, TextColor::GRAY) << L"│" << SColor(BackColor::GRAY_DARK, TextColor::GRAY)
					   << L" принять карты" << SColor(BackColor::YELLOW_DARK, TextColor::GRAY)
					   << L" ║" << SColor(BackColor::GRAY_DARK, TextColor::GRAY) << L"3"
					   << SColor(BackColor::YELLOW_DARK, TextColor::GRAY) << L"│" << SColor(BackColor::GRAY_DARK, TextColor::GRAY)
					   << L" передать ход" << SColor(BackColor::YELLOW_DARK, TextColor::GRAY)
					   << L" ║ ход икрока   │        ║ " << std::endl
					   << L" ╚═╧═════════════╩═╧═══════════════╩═╧══════════════╩══════════════╧════════╝ " << std::endl
					   << SColor() << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
			*/
			std::wcout << SColor(BackColor::YELLOW_DARK, TextColor::RED_DARK)
					   << L" ╔════════════════════════════════════════════════════════════════════════════╗ ";
			for(uint8_t i=0; i<11; i++){
			std::wcout << L" ║ " << set_coord(77, 11 + i) << L" ║ ";
			}
			std::wcout << L" ╚════════════════════════════════════════════════════════════════════════════╝ ";
			
			fill(3, 11, 74, 11, BackColor::GREEN_DARK, TextColor::GRAY);

			clear(0, 23, 80, 24);
			std::wcout << set_coord();
		}

		static void draw(BrokenCards_defenition& broken_cards, uint16_t x, uint16_t y){
			if(!broken_cards.count()){
				Draw::draw_card_border(x, y, BackColor::GREEN_DARK, TextColor::GRAY);
			}else{
				Card tmp = Card();
				Draw::draw(tmp, x, y);
				std::wcout << SColor(BackColor::GREEN, TextColor::RED_DARK);
			}
			std::wcout << set_coord(x+2, y+2) << broken_cards.count()
					   << set_coord() << SColor();

			broken_cards.redrawed();
		}
		static void draw(Card& card, uint16_t x, uint16_t y, CardDrawType type=CardDrawType::Default){

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
		}
		static void draw(CardCouple& card_couple, uint16_t x, uint16_t y){
			if(card_couple.get_attack()){
				Draw::draw(*(card_couple.get_attack()), x+1, y, card_couple.get_defense() ? CardDrawType::SHADDOW : CardDrawType::Default);
			}
			if(card_couple.get_defense()){
				Draw::draw(*(card_couple.get_defense()), x, y+2);
			}
		}
		static void draw(PackCards_defenition& pack_cards, uint16_t x, uint16_t y){
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
			pack_cards.redrawed();
		}
		static void draw(Player& player, uint16_t x, uint16_t y, PlayerDrawType type){
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
		static void draw(PlayingField_defenition& playing_field, uint16_t x, uint16_t y){

		}
		static void draw(App_defenition& app, uint16_t x, uint16_t y){

		}
};