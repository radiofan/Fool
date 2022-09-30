#pragma once

class BrokenCards{
	private:
		BrokenCards(){}
		BrokenCards(const BrokenCards&){}  
		BrokenCards& operator=(BrokenCards&){}
	public:
		static BrokenCards& get_instance(){
			static BrokenCards instance;
			return instance;
		}
};