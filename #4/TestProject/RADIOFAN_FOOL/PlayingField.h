#pragma once
class PlayingField{
	private:
		PlayingField(){}
		PlayingField(const PlayingField&){}  
		PlayingField& operator=(PlayingField&){}
	public:
		static PlayingField& get_instance(){
			static PlayingField instance;
			return instance;
		}
};