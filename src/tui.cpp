#include<iostream>
#include<sys/ioctl.h>
#include<unistd.h>
#include<utility>
#include<algorithm>
#include"../include/cursor.h"
#include"../include/tui.h"
#include"../include/buffer.h"
namespace tui {
	std::pair<int,int> getTerminalSize() {
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		TUI_COL=w.ws_col;
		TUI_ROW=w.ws_row;
		return {w.ws_col,w.ws_row};
	}
	void draw() {
		std::cout<<"\x1b[2J";
		std::cout<<"\x1b[1;1H";
		getTerminalSize();
		ROW_END=std::min(ROW_BEGIN+TUI_ROW-2,ROW_FACT-1);
		for(int i=ROW_BEGIN;i<=ROW_END;i++) {
			std::cout<<BUFFER.ReadLine(i)<<std::endl;
		}
		auto [X,Y]=(*CURSORS.begin()).Place_screen();
		std::cout<<"\x1b["<<Y+1<<';'<<X+1<<'H'<<std::flush;
	}
	void drawcursor() {
		auto [X,Y]=(*CURSORS.begin()).Place_screen();
		std::cout<<"\x1b["<<Y+1<<';'<<X+1<<'H'<<std::flush;
	}
}
