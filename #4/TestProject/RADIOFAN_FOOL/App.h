#pragma once

#include "Draw.h"

enum class GameStatus{
	WAIT,
	STARTED,
	FINISHED
};

class App_defenition : public NeedRedraw{
	private:
		bool _can_accept_move;
		bool _can_accept_cards;
		bool _can_complete_action;
		bool _can_change_move;

		int8_t _current_card;
		int8_t _current_couple;

		Card* _card_in_hand;

		GameStatus status;

		Player* _current_player;

	protected:
		App_defenition(){
			reset();
		}

	public:
#ifndef TEST
		const uint32_t CARD_DISTRIBUTION_DELAY_MS = 300;
#else
		const uint32_t CARD_DISTRIBUTION_DELAY_MS = 1;
#endif // !TEST


		void reset(){
			Draw::draw();

			_can_accept_move = false;
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;

			_current_card = -1;
			_current_couple = -1;

			_card_in_hand = nullptr;

			status = GameStatus::WAIT;

			_current_player = nullptr;
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

		GameStatus game_status(){
			return status;
		}

		Player* current_player(){
			return _current_player;
		}

		int8_t current_player_ind(){
			if(!_current_player)
				return -1;
			if(GameLogic::get_instance().get_player(0) == _current_player){
				return 0;
			}else{
				return 1;
			}
		}

		int8_t current_card(){
			return _current_card;
		}

		int8_t current_couple(){
			return _current_couple;
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

			_current_player = game_logic.get_player(game_logic.get_first_player());
			_can_accept_move = true;
			this->need_redraw = true;

			status = GameStatus::STARTED;

			this->redraw();
#ifndef TEST
			this->wait_events();
#endif // !TEST

		}

		void accept_move(){
			if(!_can_accept_move)
				return;

			_can_accept_move = false;
			need_redraw = true;

			
			if(_current_player->get_type() == PlayerType::DEFENDER){
				_can_accept_cards = true;
			}
			
			_current_couple = -1;
			_card_in_hand = nullptr;

			if(_current_player->count()){
				_current_player->add(_current_player->take_card(0));//заставим обновиться
				_current_card = 0;

			}

		}

		void complete_action(){}//todo

		void accept_cards(){}//todo

		void change_move(){}//todo

		bool card_shift(int32_t shift){

			//todo сдвиг по столу

			if(!shift)
				return false;

			if(_current_card == -1 || _current_player->count() == 1)
				return false;

			shift = shift / abs(shift);
			shift += _current_card;
			if(shift >= _current_player->count()){
				_current_card = 0;
			}else if(shift < 0){
				_current_card = _current_player->count() - 1;
			}else{
				_current_card = shift;
			}

			need_redraw = true;
			return true;
		}

		bool card_enter(){
			if(_current_card == -1 && _card_in_hand == nullptr)
				return false;

			PlayingField& palying_field = PlayingField::get_instance();

			//попытка взять карту когда стол заполнен
			if(palying_field.count() >= palying_field.MAX_CARD_COUPLES)
				return false;

			//защищающейся хочет взять карту когда все карты отбиты
			if(_current_player->get_type() == PlayerType::DEFENDER && palying_field.is_all_card_couples_broken())
				return false;

			if(_current_card > -1){
				//берем карту в руки
				_card_in_hand = _current_player->take_card(_current_card);
				_current_card = -1;
				
				//атакующий берет карту в свободное место
				if(_current_player->get_type() != PlayerType::DEFENDER){
					_current_couple = palying_field.count();
				}else{
					//защищающийся в свободное место
					//todo
				}

			}else{
				//устанавливаем карту на стол
				//todo
			}

			need_redraw = true;
			return true;
		}

		bool card_cancel(){
			if(!_card_in_hand)
				return false;

			_current_player->add(_card_in_hand);
			_card_in_hand = nullptr;
			_current_card = 0;
			_current_couple = -1;
		}

		void wait_events(){
			int8_t key;
			while(status != GameStatus::FINISHED){
				key = _getch();
				switch(key){
					case '1':
						accept_move();
						break;
					case '2':
						if(_can_complete_action){
							complete_action();
						}else{
							accept_cards();
						}
						break;
					case '3':
						change_move();
						break;
					case 8://backspase
						card_cancel();
						break;
					case 27://esc
						break;
					case 72://strelka vverh
						break;
					case 80://strelka vniz
						break;
					case 77://strelka vpravo
						card_shift(1);
						break;
					case 75://strelka vlevo
						card_shift(-1);
						break;
					case 13://enter
						card_enter();
						break;
					default:
						break;
				}
				redraw();
			}
		}

		void redraw(){
			Player* tmp = nullptr;
			if(_current_player == nullptr){
				tmp = GameLogic::get_instance().get_player(0);
			}else{
				tmp = GameLogic::get_instance().get_player(0);
				if(tmp == _current_player){
					tmp = GameLogic::get_instance().get_player(1);
				}
			}
			if(tmp->is_need_redraw()){
				Draw::draw(*tmp, 4, 4, PlayerDrawType::HIDDEN);
			}

			if(BrokenCards::get_instance().is_need_redraw()){
				Draw::draw(BrokenCards::get_instance(), 4, 14);
			}
			if(PlayingField::get_instance().is_need_redraw()){
				Draw::draw(PlayingField::get_instance(), 15, 13);
			}
			if(PackCards::get_instance().is_need_redraw()){
				Draw::draw(PackCards::get_instance(), 66, 14);
			}

			
			tmp = nullptr;
			PlayerDrawType pt = PlayerDrawType::CURRENT_HIDDEN;
			if(_current_player == nullptr){
				tmp = GameLogic::get_instance().get_player(1);
			}else{
				tmp = _current_player;
				if(tmp->get_type() != PlayerType::None && !_can_accept_move){
					pt = PlayerDrawType::CURRENT_OPEN;
				}
			}
			if(tmp->is_need_redraw()){
				Draw::draw(*tmp, 4, 24, pt);
			}

			if(this->need_redraw){
				Draw::draw(*this, 0, 0);
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