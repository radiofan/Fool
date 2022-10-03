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
		static void clear(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
		static void fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, BackColor bc, TextColor tc, wchar_t filler = L' ');
		static void draw_player_hidden(Player& player, uint16_t x, uint16_t y);
		static void draw_player_current_open(Player& player, uint16_t x, uint16_t y);
		static void draw_player_current_hidden(Player& player, uint16_t x, uint16_t y);
		static void draw_card_border(uint16_t x, uint16_t y, BackColor bc, TextColor tc);

	public:
		static void draw();

		static void draw(BrokenCards_defenition& broken_cards, uint16_t x, uint16_t y);
		static void draw(Card& card, uint16_t x, uint16_t y, CardDrawType type=CardDrawType::Default);
		static void draw(CardCouple& card_couple, uint16_t x, uint16_t y);
		static void draw(PackCards_defenition& pack_cards, uint16_t x, uint16_t y);
		static void draw(Player& player, uint16_t x, uint16_t y, PlayerDrawType type);
		static void draw(PlayingField_defenition& playing_field, uint16_t x, uint16_t y);
		static void draw(App_defenition& app, uint16_t x, uint16_t y);
		static void draw_win(uint8_t player_ind, uint16_t x, uint16_t y);
};