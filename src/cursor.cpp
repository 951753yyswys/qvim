#include<utility>
#include<iostream>
#include"../include/cursor.h"
#include"../include/tui.h"
int Cursor::CursorID=0;
//int ID,X_fact,Y_fact,X_screen,Y_screen;
Cursor::Cursor():ID(CursorID++),X_fact(0),Y_fact(0),X_screen(0),Y_screen(0){};
Cursor::~Cursor()=default;
void Cursor::Up() {//Cursor up
	std::cout<<"\x1b[1A"<<std::flush;
	if(Y_fact) {
		Y_fact--;
		if(Y_screen) Y_screen--;
		else ROW_BEGIN--;
	}	
}
void Cursor::Down() {//Cursor down
	std::cout<<"\x1b[1B"<<std::flush;
	if(Y_fact<ROW_FACT-1) {
		Y_fact++;
		if(Y_fact<ROW_END+1) Y_screen++;
		else ROW_BEGIN++;
	}		
}
void Cursor::Left() {//Cursor left 
	std::cout<<"\x1b[1D"<<std::flush;
	if(X_fact) X_fact--;
	if(X_screen) X_screen--;
}
void Cursor::Right() {//Cursor right
	std::cout<<"\x1b[1C"<<std::flush;
	X_fact++;
	X_screen++;
}
std::pair<int,int> Cursor::Place_fact() {//Get cursar place in fact 
	return {X_fact,Y_fact};	
}
std::pair<int,int> Cursor::Place_screen() {//Get cursar place on screen
	return {X_screen,Y_screen};
}
void Cursor::Move(int X,int Y) {//Move to (X,Y) on screen,(0,0) is lefttop on screen
	std::cout<<"\x1b["<<Y<<';'<<X<<"H"<<std::flush;
	X_fact+=X-X_screen;
	Y_fact+=Y-Y_screen;
	X_screen=X;
	Y_screen=Y;
}
void Cursor::Move_fact(int X,int Y) {//Move to (X,Y) in fact 
	X_fact=X;
	Y_fact=Y;
}
