#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
const wchar_t CostConvertor::cost_to_letter[] = {L'0', L'В', L'Д', L'К', L'Т'};

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage(L"In Module Initialize");
}


TEST_CLASS(RADIOFAN_FOOL_Tester){
	public:
		
		TEST_METHOD_INITIALIZE(INIT_METHOD){
			Logger::WriteMessage(L"RADIOFAN_FOOL_Tester Initialize");
		}

		/*
		TEST_METHOD_CLEANUP(END_METHOD){

		}
		*/
		
		/// тест реализации синглтона класса приложения
		TEST_METHOD(Test_App__get_instance){
			App& game = App::get_instance();
			Assert::IsTrue(true);
		}
		

		/// тест реализации класса игрока
		TEST_METHOD(Test_Player){
			Player player();
			Assert::IsTrue(true);
		}
		

		/// тест реализации класса карты
		TEST_METHOD(Test_Card){
			Card card();
			Assert::IsTrue(true);
		}

		/// тест конструктора всех карт
		TEST_METHOD(Test_Card_Construct){
			for(uint8_t cost=2; cost<=14; cost++){
				for(int card_suit=1; card_suit <= Spade; card_suit++){
					try{
						Card card(cost, (CardSuit)card_suit);//конструктор с невыходящими за пределы свойствами не будет выкидывать исключение
						Assert::IsTrue(true);
					}catch(...){
						Assert::IsTrue(false);
					}
				}
			}
			for(uint8_t cost=15; cost != 2; cost++){
				for(int card_suit=1; card_suit <= Spade+1; card_suit++){
					try{
						Card card(cost, (CardSuit)card_suit);//конструктор с выходящими за пределы свойствами будет выкидывать исключение
						Assert::IsTrue(false);
					}catch(...){
						Assert::IsTrue(true);
					}
				}
			}
			for(uint8_t cost=2; cost<=14; cost++){
				try{
					Card card(cost, (CardSuit)(Spade+1));//конструктор с выходящими за пределы свойствами будет выкидывать исключение
					Assert::IsTrue(false);
				}catch(...){
					Assert::IsTrue(true);
				}
				try{
					Card card(cost, None);//конструктор с выходящими за пределы свойствами будет выкидывать исключение
					Assert::IsTrue(false);
				}catch(...){
					Assert::IsTrue(true);
				}
			}
		}
		
		/// тест геттеров карты
		TEST_METHOD(Test_Card__getters){
			Card card(5, Spade);
			Assert::AreEqual((uint8_t)5, card.get_cost());
			Assert::AreEqual((int)Spade, (int)card.get_suit());
		}
		

		/// тест реализации синглтона класса поля игры
		TEST_METHOD(Test_PlayingField){
			PlayingField& playing_field = PlayingField::get_instance();
			Assert::IsTrue(true);
		}

		/// тест реализации методов класса поля игры
		TEST_METHOD(Test_PlayingField_methods){
			PlayingField& playing_field = PlayingField::get_instance();
			playing_field.reset();
			
			CardCouple tmp = CardCouple();

			for(uint8_t couple_i = 0; couple_i <= 6; couple_i++){
				Assert::AreEqual(couple_i, playing_field.count());
			
				for(uint8_t i=0; i<=playing_field.count(); i++){ 
					try{
						playing_field.get_card_couple(i);
						Assert::IsTrue(i < playing_field.count());
					}catch(...){
						Assert::IsFalse(i < playing_field.count());
					}
				}
				try{
					playing_field.add_card_couple(tmp);
					Assert::IsTrue(couple_i < 6);
				}catch(...){
					Assert::IsFalse(couple_i < 6);
				}

			}
		}
		

		/// тест реализации класса пары карт
		TEST_METHOD(Test_CardCouple){
			CardCouple card_couple();
			Assert::IsTrue(true);
		}

		/// тест реализации методов пары карт
		TEST_METHOD(Test_CardCouple__test_1){
			CardCouple card_couple = CardCouple();
			Assert::IsNull(card_couple.get_attack());  //по умолчанию пара пустая
			Assert::IsNull(card_couple.get_defense()); 
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой
			
			Card card_1(5, Diamond);
			Assert::IsFalse(card_couple.set_defense(&card_1)); //нельзя установить защитную карту без атакующей
			Assert::IsTrue(card_couple.set_attack(&card_1));
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой

			Assert::IsTrue(&card_1 == card_couple.get_attack());
			
			Assert::IsFalse(card_couple.set_defense(&card_1)); //нельзя установить защитную карту равной атакующей



			Card card_2(4, Diamond);
			Assert::IsFalse(card_couple.set_defense(&card_2)); //нельзя установить защитную карту слабже атакующей
			Assert::IsFalse(card_couple.set_defense(&card_1, Diamond)); //нельзя установить защитную карту равной атакующей (даже если они козыри)

			//Card card_2(4, Diamond);
			Assert::IsFalse(card_couple.set_defense(&card_2, Diamond)); //нельзя установить защитную карту слабже атакующей (даже если они козыри)
			
			Card card_3(6, Heart);
			Assert::IsFalse(card_couple.set_defense(&card_3)); //нельзя установить защитную карту другой масти (если она не козырь)
			
			Card card_4(6, Diamond);
			Assert::IsTrue(card_couple.set_defense(&card_4)); //можно установить защитную карту выше по рангу
			Assert::IsTrue(card_couple.is_broken()); //является ли пара битой

			Assert::IsTrue(&card_4 == card_couple.get_defense());
			Assert::IsFalse(card_couple.set_attack(&card_2)); //нельзя сменять атакующую карту после установки защиты
			
		}

		/// тест реализации методов пары карт
		TEST_METHOD(Test_CardCouple__test_2){
			CardCouple card_couple = CardCouple();
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой

			Card card_1(5, Diamond);
			Assert::IsTrue(card_couple.set_attack(&card_1));
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой
			
			Card card_4(6, Diamond);
			Assert::IsTrue(card_couple.set_defense(&card_4, Diamond)); //можно установить защитную карту выше по рангу (даже если они козыри)
			Assert::IsTrue(card_couple.is_broken()); //является ли пара битой

			Assert::IsTrue(&card_4 == card_couple.get_defense());
		}

		/// тест реализации методов пары карт
		TEST_METHOD(Test_CardCouple__test_3){
			CardCouple card_couple = CardCouple();
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой

			Card card_1(5, Diamond);
			Assert::IsTrue(card_couple.set_attack(&card_1));
			Assert::IsFalse(card_couple.is_broken()); //является ли пара битой
			
			Card card_5(4, Heart);
			Assert::IsTrue(card_couple.set_defense(&card_5, Heart)); //можно установить защитную карту ниже по рангу но козырь
			Assert::IsTrue(card_couple.is_broken()); //является ли пара битой

			Assert::IsTrue(&card_5 == card_couple.get_defense());
		}
		

		/// тест реализации синглтона класса битых карт
		TEST_METHOD(Test_BrokenCards){
			BrokenCards& broken_cards = BrokenCards::get_instance();
			Assert::IsTrue(true);
		}

		/// тест реализации метода добавления пар карт в биту класса битых карт
		TEST_METHOD(Test_BrokenCards__add){
			BrokenCards& broken_cards = BrokenCards::get_instance();
			broken_cards.reset();
			Assert::AreEqual((uint8_t)0, broken_cards.count());

			std::vector<Card> all_cards(36);
			for(uint8_t card_suit=1, card_ind=0; card_suit<=4; card_suit++){
				for(uint8_t card_cost=6; card_cost<=14; card_cost++, card_ind++){
					all_cards[card_ind] = Card(card_cost, (CardSuit)card_suit);
				}
			}

			for(uint8_t i=0; i<3; i++){
				CardCouple tmp = CardCouple();
				tmp.set_attack(&(all_cards[i*2]));
				tmp.set_defense(&(all_cards[i*2+1]));
				broken_cards.add(tmp);
			}
			for(uint8_t i=6; i<36; i++){
				CardCouple tmp = CardCouple();
				tmp.set_attack(&(all_cards[i]));
				broken_cards.add(tmp);
			}
			Assert::AreEqual((uint8_t)36, broken_cards.count());
		}
		

		/// тест реализации синглтона класса колоды карт
		TEST_METHOD(Test_PackCards){
			PackCards& pack_cards = PackCards::get_instance();
			Assert::IsTrue(true);
		}

		/// тест реализации метода взятия карты из колоды
		TEST_METHOD(Test_PackCards__pop){
			PackCards& pack_cards = PackCards::get_instance();
			pack_cards.reset();
			Assert::AreEqual((uint8_t)36, pack_cards.count());

			std::vector<Card> all_cards(36);
			for(uint8_t card_suit=1, card_ind=0; card_suit<=4; card_suit++){
				for(uint8_t card_cost=6; card_cost<=14; card_cost++, card_ind++){
					all_cards[card_ind] = Card(card_cost, (CardSuit)card_suit);
				}
			}
			
			uint8_t len =pack_cards.count();
			for(uint32_t i=0; i<len; i++){
				Card* tmp = pack_cards.pop();
				for(uint8_t i=0; i<all_cards.size(); i++){
					if(tmp->get_cost() == all_cards[i].get_cost() && tmp->get_suit() == all_cards[i].get_suit()){
						all_cards.erase(all_cards.begin()+i);
					}
				}
			}

			Assert::AreEqual((size_t)0, all_cards.size());

			try{
				pack_cards.pop();//взятие карты из пустой колоды
				Assert::Fail();
			}catch(...){
				Assert::IsTrue(true);
			}
		}

		/// тест реализации метода взятия карты из колоды
		TEST_METHOD(Test_PackCards__trump){
			PackCards& pack_cards = PackCards::get_instance();
			pack_cards.reset();
			Assert::AreEqual((uint8_t)36, pack_cards.count());
			Assert::IsNull(pack_cards.get_trump());

			std::vector<Card> all_cards(36);
			for(uint8_t card_suit=1, card_ind=0; card_suit<=4; card_suit++){
				for(uint8_t card_cost=6; card_cost<=14; card_cost++, card_ind++){
					all_cards[card_ind] = Card(card_cost, (CardSuit)card_suit);
				}
			}
			
			uint8_t len =pack_cards.count();
			for(uint32_t i=0; i<len; i++){
				Card* tmp = pack_cards.set_trump();
				Assert::IsTrue(tmp == pack_cards.get_trump());
				for(uint8_t i=0; i<all_cards.size(); i++){
					if(tmp->get_cost() == all_cards[i].get_cost() && tmp->get_suit() == all_cards[i].get_suit()){
						all_cards.erase(all_cards.begin()+i);
					}
				}
			}

			Assert::AreEqual((size_t)0, all_cards.size());
		}
		

		/// тест реализации класса конвертора стоимости карты
		TEST_METHOD(Test_CostConvertor){
			CostConvertor cost_convertor();
			Assert::IsTrue(true);
		}

		/// тест реализации метода конвертации стоимости в букву
		TEST_METHOD(Test_CostConvertor__cost2letter){
			CostConvertor::cost2letter(0);
			Assert::IsTrue(true);
		}

		/// тест реализации метода конвертации буквы в стоимость
		TEST_METHOD(Test_CostConvertor__letter2cost){
			CostConvertor::letter2cost(L'\0');
			Assert::IsTrue(true);
		}

		/// тест правильной работы метода конвертации стоимости в букву
		TEST_METHOD(Test_CostConvertor__cost2letter__work){
			for(uint8_t i=15; i != 2; i++){
				try{
					CostConvertor::cost2letter(i);
					Assert::IsTrue(false);
				}catch(...){
					Assert::IsTrue(true);
				}
			}
			for(uint8_t i=2; i<10; i++){
				Assert::AreEqual((wchar_t)(L'0'+i), CostConvertor::cost2letter(i));
			}
			Assert::AreEqual(L'0', CostConvertor::cost2letter(10));
			Assert::AreEqual(L'В', CostConvertor::cost2letter(11));
			Assert::AreEqual(L'Д', CostConvertor::cost2letter(12));
			Assert::AreEqual(L'К', CostConvertor::cost2letter(13));
			Assert::AreEqual(L'Т', CostConvertor::cost2letter(14));
		}

		/// тест правильной работы метода конвертации буквы в стоимость
		TEST_METHOD(Test_CostConvertor__letter2cost__work){
			
			for(wchar_t i=L'2'; i<L'9'; i++){
				Assert::AreEqual((uint8_t)(i-L'0'), CostConvertor::letter2cost(i));
			}
			Assert::AreEqual((uint8_t)10, CostConvertor::letter2cost(L'0'));
			Assert::AreEqual((uint8_t)11, CostConvertor::letter2cost(L'В'));
			Assert::AreEqual((uint8_t)12, CostConvertor::letter2cost(L'Д'));
			Assert::AreEqual((uint8_t)13, CostConvertor::letter2cost(L'К'));
			Assert::AreEqual((uint8_t)14, CostConvertor::letter2cost(L'Т'));
		}





};
