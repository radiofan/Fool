#pragma once

class BrokenCards;
class Card;
class CardCouple;
class PackCards;
class Player;
class PlayingField;
class App;

enum class PlayerDrawType{
	HIDDEN,
	CURRENT
};

class Draw{
	private:
		static void draw_player_hidden(Player& player, uint16_t x, uint16_t y){

		}
		static void draw_player_current(Player& player, uint16_t x, uint16_t y){

		}
	public:
		static void draw(BrokenCards& broken_cards, uint16_t x, uint16_t y){

		}
		static void draw(Card& card, uint16_t x, uint16_t y){

		}
		static void draw(CardCouple& card_couple, uint16_t x, uint16_t y){

		}
		static void draw(PackCards& pack_cards, uint16_t x, uint16_t y){

		}
		static void draw(Player& player, uint16_t x, uint16_t y, PlayerDrawType type){
			switch(type){
				case PlayerDrawType::HIDDEN:
					Draw::draw_player_hidden(player, x, y);
					break;
				case PlayerDrawType::CURRENT:
					Draw::draw_player_current(player, x, y);
					break;
			}
		}
		static void draw(PlayingField& playing_field, uint16_t x, uint16_t y){

		}
		static void draw(App& app, uint16_t x, uint16_t y){

		}
};