#pragma once

#include "Draw.h";
#include "CostConvertor.h"
#include "Card.h"
#include "CardCouple.h"
#include "BrokenCards.h"
#include "PackCards.h"
#include "Player.h"
#include "PlayingField.h"
#include "GameLogic.h"

class App_defenition{
	private:
		bool _can_accept_move;
		bool _can_accept_cards;
		bool _can_complete_action;
		bool _can_change_move;

		int8_t _current_player;

	protected:
		App_defenition(){
			reset();
		}

	public:
		const uint64_t CARD_DISTRIBUTION_DELAY_MS = 300;

		void reset(){
			_can_accept_move = false;
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;

			_current_player = -1;

			srand(time(nullptr));

			GameLogic::get_instance().reset();
			//this->redraw();
		}

		bool can_accept_move(){
			return _can_accept_move;
		}
		bool can_accept_cards(){
			return _can_accept_cards;
		}
		bool can_complete_action(){
			return _can_complete_action;
		}
		bool can_change_move(){
			return _can_change_move;
		}

		int8_t current_player(){
			return _current_player;
		}

		void start(){
			GameLogic& game_logic = GameLogic::get_instance();
			for(uint8_t i=0; i<6; i++){
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
				Card* card = PackCards::get_instance().pop();
				game_logic.get_player(0)->add(card);
				//this->redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
				card = PackCards::get_instance().pop();
				game_logic.get_player(1)->add(card);
				//this->redraw();
			}
			Sleep(CARD_DISTRIBUTION_DELAY_MS);
			PackCards::get_instance().set_trump();
			//todo
			_current_player = game_logic.get_first_player();
			_current_player = 0;
			_can_accept_move = true;
			//this->redraw();
			//this->wait_events();
		}
};

class App : public App_defenition{
	private:
		App(){}
		App(const App&){}  
		App& operator=(App&){}
	public:
		static App& get_instance(){
			static App instance;
			return instance;
		}
};