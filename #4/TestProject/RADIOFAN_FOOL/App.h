#pragma once

#include "SColor.h";
#include "set_coord.h"
#include "NeedRedraw.h"
#include "Card.h"
#include "CostConvertor.h"
#include "CardCouple.h"
#include "BrokenCards.h"
#include "PackCards.h"
#include "Player.h"
#include "PlayingField.h"
#include "GameLogic.h"
#include "Draw.h";

class App_defenition : public NeedRedraw{
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
			Draw::draw();

			_can_accept_move = false;
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;

			_current_player = -1;
			this->need_redraw = true;

			srand(time(nullptr));

			GameLogic::get_instance().reset();
			
			this->redraw();
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
				this->redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
				card = PackCards::get_instance().pop();
				game_logic.get_player(1)->add(card);
				this->redraw();
			}
			Sleep(CARD_DISTRIBUTION_DELAY_MS);
			PackCards::get_instance().set_trump();

			_current_player = game_logic.get_first_player();
			_current_player = 0;
			_can_accept_move = true;
			this->need_redraw = true;

			this->redraw();
			//todo
			//this->wait_events();
		}

		void redraw(){
			if(this->need_redraw){
				Draw::draw(*this, 0, 0);
			}

			if(_current_player == -1){
				Player tmp;
				Draw::draw(tmp, 0, 4, PlayerDrawType::HIDDEN);
			}else{
				Player* tmp = GameLogic::get_instance().get_player(_current_player^0x01);
				if(tmp->is_need_redraw()){
					Draw::draw(*tmp, 0, 4, PlayerDrawType::HIDDEN);
				}
			}
			if(BrokenCards::get_instance().is_need_redraw()){
				Draw::draw(BrokenCards::get_instance(), 4, 14);
			}
			if(PlayingField::get_instance().is_need_redraw()){
				Draw::draw(PlayingField::get_instance(), 20, 13);
			}
			if(PackCards::get_instance().is_need_redraw()){
				Draw::draw(PackCards::get_instance(), 66, 14);
			}
			if(_current_player == -1){
				Player tmp;
				Draw::draw(tmp, 0, 24, PlayerDrawType::CURRENT_HIDDEN);
			}else{
				Player* tmp = GameLogic::get_instance().get_player(_current_player);
				if(tmp->is_need_redraw()){
					Draw::draw(*tmp, 0, 24, tmp->get_type() == PlayerType::None ? PlayerDrawType::CURRENT_HIDDEN : PlayerDrawType::CURRENT_OPEN);
				}
			}
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