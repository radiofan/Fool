#pragma once
class NeedRedraw{
	protected:
		bool need_redraw = false;
	public:
		bool is_need_redraw(){
			return need_redraw;
		}
		void redrawed(){
			need_redraw = false;
		}
};