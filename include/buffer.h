#ifndef BUFFER_H
#define BUFFER_H
#include<string>
#include<memory>
#include<vector>
class Buffer {
private:
	static int BufferID;
	int ID,Size;
	class LineBuffer {
	private:
		std::string Str;//save text
	public:
		LineBuffer();
		~LineBuffer();
		void Insert(int Pos,std::string InsertStr);//InsertStr will begin at Pos
		void Delete(int Begin,int End);//Delete [Begin,End]
		int size();//Get size 
		std::string Read(int Begin,int End);//Read [Begin,End]
	};
	std::vector<std::unique_ptr<LineBuffer>> Lines;
public:
	Buffer();
	~Buffer();
	void NewLine();//Create a new line 
	void InsLine(int Line);
	std::string ReadLine(int Line);//Get a hole line 
	std::string Read(int Line,int Begin,int End);//Read the [Begin,End] chars in Line 
	void DeleteLine(int Line);//Delete a hole line 
	void Delete(int Line,int Begin,int End);//Delete the [Begin,End] chars in Line 
	void Insert(int Line,int Pos,std::string InsertStr);//Insert the Str to Line and it will begin at Pos 
	int size();//Get size 
	int LineSize(int Line);//Get Line size
};
extern Buffer BUFFER;
#endif 
