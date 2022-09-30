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
			
		/// тест на проверку реализации синглтона класса приложения
		TEST_METHOD(Test_App__get_instance){
			App& game = App::get_instance();
			Assert::IsTrue(true);
		}
};
