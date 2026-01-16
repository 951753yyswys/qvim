#ifndef TUI_H
#define TUI_H
#include<utility>
#include"./cursor.h"
extern int TUI_ROW,TUI_COL;
namespace tui {
	void draw();
	void drawcursor();
	std::pair<int,int> getTerminalSize();
}
#endif 
