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

		Card* card_in_hand(){
			return _card_in_hand;
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

		int8_t another_player_ind(){
			if(!_current_player)
				return -1;
			if(GameLogic::get_instance().get_player(0) == _current_player){
				return 1;
			}else{
				return 0;
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
			
			Sleep(CARD_DISTRIBUTION_DELAY_MS);
			hand_out_cards();

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

		void hand_out_cards(){
			uint8_t player_ind = 0;
			GameLogic& game_logic = GameLogic::get_instance();

			Player* player = game_logic.get_player(0);
			if(player->get_type() == PlayerType::DEFENDER){
				player = game_logic.get_player(1);
				player_ind = 1;
			}

			uint8_t full = 0;
			PackCards& pack_cards = PackCards::get_instance();
			while(full < 2){
				if(player->count() >= 6){
					full++;
					player_ind = game_logic.get_another_player_ind(player_ind);
					player = game_logic.get_player(player_ind);
					continue;
				}
				if(!pack_cards.count())
					break;
				player->add(pack_cards.pop());
				if(player->get_type() == PlayerType::None){
					player_ind = game_logic.get_another_player_ind(player_ind);
					player = game_logic.get_player(player_ind);
				}
				this->redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
			}
		}

		void accept_move(){
			if(!_can_accept_move)
				return;
			
			_can_accept_move = false;
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;

			//главный атакющий может завершить кон если на столе есть карты и они побиты
			PlayingField& playing_field = PlayingField::get_instance();
			if(_current_player->get_type() == PlayerType::MAIN_ATTACKER && playing_field.count() && playing_field.is_all_card_couples_broken()){
				_can_complete_action = true;

			//атакующий может передать ход если на столе есть карты, и они не побиты
			}else if(_current_player->get_type() != PlayerType::DEFENDER && playing_field.count() && !playing_field.is_all_card_couples_broken()){
				_can_change_move = true;
			}

			//защищающийся может принять карты
			if(_current_player->get_type() == PlayerType::DEFENDER){
				_can_accept_cards = true;
			}

			need_redraw = true;
			
			_current_couple = -1;
			_card_in_hand = nullptr;

			if(_current_player->count()){
				_current_player->set_type(_current_player->get_type());//заставим обновиться
				_current_card = 0;

			}

		}

		void complete_action(){
			if(!_can_complete_action)
				return;
			
			_current_card = -1;
			_current_player->set_type(_current_player->get_type());
			need_redraw = true;
			redraw();
			
			PlayingField& playing_field = PlayingField::get_instance();

			if(_card_in_hand){
				_current_player->add(_card_in_hand);
				_card_in_hand = nullptr;
				playing_field.set_need_redraw_couple(0);
				_current_couple = -1;
				need_redraw = true;
				redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
			}

			playing_field.move_cards_to_broken();
			redraw();
			Sleep(CARD_DISTRIBUTION_DELAY_MS);

			hand_out_cards();
			
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;
			
			GameLogic& game_logic = GameLogic::get_instance();

			//роли игроков меняются
			if(!game_logic.get_player(0)->count() || !game_logic.get_player(1)->count()){
				_can_accept_move = false;
				if(_current_player->count() != 0){
					_current_player->set_type(PlayerType::DEFENDER);
					_current_player = game_logic.get_player(another_player_ind());
					_current_player->set_type(PlayerType::MAIN_ATTACKER);
				}
				status = GameStatus::FINISHED;
			}else{
				_can_accept_move = true;
				_current_player->set_type(PlayerType::DEFENDER);
				_current_player = game_logic.get_player(another_player_ind());
				_current_player->set_type(PlayerType::MAIN_ATTACKER);
			}
			need_redraw = true;
			redraw();

			if(status == GameStatus::FINISHED){
				Draw::draw_win(game_logic.get_player(0)->count() == game_logic.get_player(1)->count() ? -1 : current_player_ind(), 15, 12);
			}
		}

		void accept_cards(){
			if(!_can_accept_cards)
				return;

			PlayingField& playing_field = PlayingField::get_instance();

			_current_card = -1;
			_current_player->set_type(_current_player->get_type());
			need_redraw = true;
			redraw();

			if(_card_in_hand){
				_current_player->add(_card_in_hand);
				_card_in_hand = nullptr;
				playing_field.set_need_redraw_couple(_current_couple);
				_current_couple = -1;
				need_redraw = true;
				redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
			}
			for(;playing_field.count();){
				playing_field.move_couple_to_player(0, *_current_player);
				redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
			}

			hand_out_cards();

			//роли игроков не меняются
			GameLogic& game_logic = GameLogic::get_instance();

			_current_player->set_type(_current_player->get_type());
			_current_player = game_logic.get_player(another_player_ind());
			_current_player->set_type(_current_player->get_type());
			
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;

			if(_current_player->count()){
				_can_accept_move = true;
			}else{
				_can_accept_move = false;
				status = GameStatus::FINISHED;
			}
			need_redraw = true;
			redraw();

			if(status == GameStatus::FINISHED){
				Draw::draw_win(current_player_ind(), 15, 12);
			}
		}

		void change_move(){
			if(!_can_change_move)
				return;

			PlayingField& playing_field = PlayingField::get_instance();

			if(_card_in_hand){
				_current_player->add(_card_in_hand);
				_card_in_hand = nullptr;
				if(_current_player->get_type() == PlayerType::DEFENDER){
					playing_field.set_need_redraw_couple(_current_couple);
				}else{
					playing_field.set_need_redraw_couple(0);
				}
				_current_couple = -1;
				need_redraw = true;
				redraw();
				Sleep(CARD_DISTRIBUTION_DELAY_MS);
			}
			
			_can_accept_move = true;
			_can_accept_cards = false;
			_can_complete_action = false;
			_can_change_move = false;
			
			_card_in_hand = nullptr;
			_current_card = -1;
			_current_couple = -1;

			GameLogic& game_logic = GameLogic::get_instance();

			_current_player->set_type(_current_player->get_type());
			_current_player = game_logic.get_player(another_player_ind());
			_current_player->set_type(_current_player->get_type());

			need_redraw = true;
		}

		bool card_shift(int32_t shift){

			if(!shift)
				return false;

			if(_card_in_hand && _current_player->get_type() == PlayerType::DEFENDER){
				PlayingField& playing_field = PlayingField::get_instance();

				if(shift > 0){
					shift = playing_field.get_right_not_broken_couple(_current_couple);
				}else{
					shift = playing_field.get_left_not_broken_couple(_current_couple);
				}
				if(shift == _current_couple){
					return false;
				}else{
					playing_field.set_need_redraw_couple(_current_couple);
					_current_couple = shift;
					need_redraw = true;
					return true;
				}
			}

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

			_current_player->set_type(_current_player->get_type());
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
					_current_couple = palying_field.get_right_not_broken_couple(-1);
				}

			}else{
				//устанавливаем карту на стол
				if(_current_player->get_type() != PlayerType::DEFENDER){
					GameLogic& game_logic = GameLogic::get_instance();
					//атакующий
					//проверка на возможность установить атакующую карту и наличие карт у защищающегося
					if(palying_field.can_add_attack_card(*_card_in_hand)
					&& game_logic.get_player(another_player_ind())->count() >= palying_field.not_broken_couples_count()+1){
						palying_field.add_card_couple();
						palying_field.get_card_couple(_current_couple).set_attack(_card_in_hand);
						_can_change_move = true;
						_can_complete_action = false;
					}else{
						return false;
					}
				}else{
					//защищающийся
					CardCouple& tmp = palying_field.get_card_couple(_current_couple);;
					if(tmp.set_defense(_card_in_hand, PackCards::get_instance().get_trump_suit())){
						PlayingField::get_instance().set_need_redraw_couple(_current_couple);
						//если карта была установлена
						//то можно только передать ход атакующему
						_can_change_move = true;
						_can_accept_cards = false;
					}else{
						return false;
					}
				}
				_current_couple = -1;
				_card_in_hand = nullptr;
						
				_current_card = -1;
				if(_current_player->count()){
					_current_card++;
				}
			}

			need_redraw = true;
			return true;
		}

		bool card_cancel(){
			if(!_card_in_hand)
				return false;

			

			if(_current_player->get_type() == PlayerType::DEFENDER){
				PlayingField::get_instance().set_need_redraw_couple(_current_couple);
			}else{
				PlayingField::get_instance().set_need_redraw_couple(0);
			}

			_current_player->add(_card_in_hand);
			_card_in_hand = nullptr;
			_current_card = 0;
			_current_couple = -1;

			need_redraw = true;
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

			key = 0;
			while(key != 27){
				key = _getch();
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