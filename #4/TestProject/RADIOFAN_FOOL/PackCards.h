#pragma once
class PackCards{
	private:
		PackCards(){}
		PackCards(const PackCards&){}  
		PackCards& operator=(PackCards&){}
	public:
		static PackCards& get_instance(){
			static PackCards instance;
			return instance;
		}
};