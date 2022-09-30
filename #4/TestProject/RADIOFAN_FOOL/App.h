#pragma once

#include "CostConvertor.h"
#include "Card.h"
#include "Player.h"

class App{
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