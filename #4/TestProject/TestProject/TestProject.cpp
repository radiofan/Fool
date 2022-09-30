#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(RADIOFAN_FOOL_Tester){
	public:
		/*
		TEST_METHOD_INITIALIZE(INIT_METHOD){

		}

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
		TEST_METHOD(Test_CostConvertor__cost2letter){
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
		TEST_METHOD(Test_CostConvertor__cost2letter__work){
			
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
