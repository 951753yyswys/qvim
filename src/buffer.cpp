#include<memory>
#include<vector>
#include<string>
#include"../include/buffer.h"
int Buffer::BufferID=0;
Buffer::Buffer():ID(BufferID),Lines(),Size(0){};
Buffer::~Buffer()=default;
void Buffer::DeleteLine(int Line) {//Delete a hole line 
	Size--;
	for(int i=Size-1;i>=Line;i--) {
		Lines[i]=std::move(Lines[i+1]);
	}
	Lines.pop_back();
}
void Buffer::Delete(int Line,int Begin,int End) {//Delete the [Begin,End] chars in Line 
	if(Begin<=End) {
		Lines[Line]->Delete(Begin,End);
	}		
}
void Buffer::Insert(int Line,int Pos,std::string InsertStr) {//Insert the Str to Line and it will begin at Pos
	if(InsertStr!="") {
		Lines[Line]->Insert(Pos,InsertStr);
	}
}
std::string Buffer::ReadLine(int Line) {//Get a hole line 
	return Lines[Line]->Read(0,Lines[Line]->size());
}
std::string Buffer::Read(int Line,int Begin,int End) {//Read the [Begin,End] chars in Line 
	if(Begin<=End) {
		return Lines[Line]->Read(Begin,End);
	}
	return "";
}
int Buffer::size() {
	return Size;
}
int Buffer::LineSize(int Line) {
	return Lines[Line]->size();
}
std::string Buffer::LineBuffer::Read(int Begin,int End) {//Read [Begin,End]
	std::string Ret="";
	for(int i=Begin;i<=End;i++) Ret.push_back(Str[i]);
	return Ret;
}
void Buffer::NewLine() {//Create a new line 
	Lines.emplace_back(std::make_unique<LineBuffer>(LineBuffer()));
	Size++;
}
void Buffer::InsLine(int Line) {
	Lines.emplace_back(nullptr);
	Size++;
	for(int i=Size-2;i>=Line;i--) Lines[i+1]=std::move(Lines[i]);
	Lines[Line]=std::make_unique<LineBuffer>();
}
Buffer::LineBuffer::LineBuffer():Str(){};
Buffer::LineBuffer::~LineBuffer()=default;
void Buffer::LineBuffer::Insert(int Pos,std::string InsertStr) {//InsertStr will begin at Pos
	Str.insert(Pos,InsertStr);	
}
void Buffer::LineBuffer::Delete(int Begin,int End) {//Delete [Begin,End]
	Str.erase(Begin,End-Begin+1);	
}
int Buffer::LineBuffer::size() {
	return Str.size();
}
