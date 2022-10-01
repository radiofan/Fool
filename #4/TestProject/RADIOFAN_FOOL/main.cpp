#include "stdafx.h"
#include "App.h"

const wchar_t CostConvertor::cost_to_letter[] = {L'1', L'В', L'Д', L'К', L'Т'};


std::wostream& operator<<(std::wostream& os, const SColor& color){
	color.set_color();
	return os;
}
std::wostream& operator<<(std::wostream& os, const set_coord& tmp){
	tmp.set();
	return os;
}

int32_t wmain(int32_t argc, wchar_t* argv[]){
	App::get_instance();

	Card tmp = Card();

	Draw::draw(tmp, 4, 4);

	tmp = Card(10, CardSuit::Club);

	Draw::draw(tmp, 12, 4);

	tmp = Card(12, CardSuit::Heart);

	Draw::draw(tmp, 37, 13);

	_getch();
	return 0;
}