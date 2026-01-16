#ifndef CURSAR_H
#define CURSAR_H
#include<utility>
#include<vector>
extern int ROW_BEGIN;
extern int ROW_END;
extern int ROW_FACT;
class Cursor 
{
private:
	static int CursorID;
	int ID,X_fact,Y_fact,X_screen,Y_screen;
public:
	Cursor();
	~Cursor();
	void Up();//Cursor up
	void Down();//Cursor down
	void Left();//Cursor left 
	void Right();//Cursor right
	std::pair<int,int> Place_fact();//Get cursar place in fact 
	std::pair<int,int> Place_screen();//Get cursar place on screen
	void Move(int X,int Y);//Move to (X,Y) on screen,(0,0) is lefttop on screen
	void Move_fact(int X,int Y);//Move to (X,Y) in fact 
};
extern std::vector<Cursor> CURSORS;
#endif
