#pragma once

class App_defenition;

enum class PlayerDrawType{
	HIDDEN,
	CURRENT_HIDDEN,
	CURRENT_OPEN
};

class Draw{
	private:
		static void draw_player_hidden(Player& player, uint16_t x, uint16_t y){

		}
		static void draw_player_current(Player& player, uint16_t x, uint16_t y){

		}
	public:
		static void draw(){
			
			std::wcin.imbue(std::locale(".866"));
			std::wcout.imbue(std::locale(".866"));

			std::wcout << set_coord(0, 0) << SColor() << SColor(BackColor::YELLOW_DARK, TextColor::GRAY)
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
					   << L" " << SColor(TextColor::RED_DARK) << L"╔════════════════════════════════════════════════════════════════════════════╗" << SColor() << std::endl;
			for(uint8_t i=0; i<11; i++){
			std::wcout << L" " << SColor(TextColor::RED_DARK) << L"║ " << SColor(BackColor::GREEN_DARK) << std::wstring(74, L' ')
					   << SColor() << SColor(TextColor::RED_DARK) << L" ║" << SColor() << std::endl;
			}
			std::wcout << L" " << SColor(TextColor::RED_DARK) << L"╚════════════════════════════════════════════════════════════════════════════╝" << SColor() << std::endl;
			for(uint8_t i=0; i<20; i++){
				std::wcout << std::endl;
			}
			std::wcout << set_coord();
		}

		static void draw(BrokenCards_defenition& broken_cards, uint16_t x, uint16_t y){

		}
		static void draw(Card& card, uint16_t x, uint16_t y){

			std::wstring out = (card.get_suit() == CardSuit::None ? L"▒▒▒▒▒▒" : L"      ");

			std::wcout << SColor(card.get_suit() == CardSuit::None ? BackColor::GREEN : BackColor::WHITE, TextColor::RED_DARK);
			for(uint8_t i=0; i<5; i++){
				std::wcout << set_coord(x, y+i) << out;
			}


			if(card.get_suit() != CardSuit::None){
				std::wcout << SColor(BackColor::WHITE, CostConvertor::suit2color(card.get_suit()));
				std::wcout << set_coord(x+1, y+1) << CostConvertor::cost2letter(card.get_cost());
				if(card.get_cost() == 10){
					std::wcout << L"0";
				}
				std::wcout << set_coord(x+4, y+1) << CostConvertor::suit2letter(card.get_suit());
			}
			std::wcout << set_coord() << SColor();
		}
		static void draw(CardCouple& card_couple, uint16_t x, uint16_t y){

		}
		static void draw(PackCards_defenition& pack_cards, uint16_t x, uint16_t y){

		}
		static void draw(Player& player, uint16_t x, uint16_t y, PlayerDrawType type){
			switch(type){
				case PlayerDrawType::HIDDEN:
					Draw::draw_player_hidden(player, x, y);
					break;
				case PlayerDrawType::CURRENT_OPEN:
					Draw::draw_player_current(player, x, y);
					break;
				case PlayerDrawType::CURRENT_HIDDEN:
					//todo
					break;
			}
		}
		static void draw(PlayingField_defenition& playing_field, uint16_t x, uint16_t y){

		}
		static void draw(App_defenition& app, uint16_t x, uint16_t y){

		}
};