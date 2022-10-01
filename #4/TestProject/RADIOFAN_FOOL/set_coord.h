#pragma once


class set_coord{
	private:
		COORD for_set;
	public:
		set_coord(){
			CONSOLE_SCREEN_BUFFER_INFO info;
			HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hndl, &info);
			static COORD old = info.dwCursorPosition;
			for_set = old;
			SetConsoleCursorPosition(hndl, old);
		}
		set_coord(int16_t x, int16_t y){
			HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
			for_set.X = x;
			for_set.Y = y;
		}

		void set() const{
			HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(hndl, for_set);
		}
};
std::wostream& operator<<(std::wostream& os, const set_coord& tmp);