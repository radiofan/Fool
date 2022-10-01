#pragma once

class BrokenCards_defenition;
class Card;
class CardCouple;
class PackCards_defenition;
class Player;
class PlayingField_defenition;
class App_defenition;

enum class PlayerDrawType{
	HIDDEN,
	CURRENT_HIDDEN,
	CURRENT_OPEN
};

class NeedRedraw{
	protected:
		bool need_redraw = false;
	public:
		bool is_need_redraw(){
			return need_redraw;
		}
		void redrawed(){
			need_redraw = false;
		}
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
		}

		static void draw(BrokenCards_defenition& broken_cards, uint16_t x, uint16_t y){

		}
		static void draw(Card& card, uint16_t x, uint16_t y){

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