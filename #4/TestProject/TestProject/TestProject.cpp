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




};
