#include<string>
#include"../include/cursor.h"
#include"../include/buffer.h"
#include"../include/edit.h"
namespace Edit {
	void Insert(char Chr) {
		if(Chr==10) {
			for(auto &Cur:CURSORS) {
				auto [x,y]=Cur.Place_fact();
				BUFFER.InsLine(y+1);
				BUFFER.Insert(y+1,0,BUFFER.Read(y,x,BUFFER.LineSize(y)-1));
				BUFFER.Delete(y,x,BUFFER.LineSize(y)-1);
				Cur.Down();
			}
			ROW_FACT++;
			return;
		}
		for(auto &Cur:CURSORS) {
			auto [x,y]=Cur.Place_fact();
			std::string Tmp="";
			Tmp.push_back(Chr);
			BUFFER.Insert(y,x,Tmp);	
			Cur.Right();
		}
	}
	void Delete() {
		for(auto &Cur:CURSORS) {
			auto [x,y]=Cur.Place_fact();
			if(x==0) return;
			BUFFER.Delete(y,x-1,x-1);
			Cur.Left();
		}
	}
}
