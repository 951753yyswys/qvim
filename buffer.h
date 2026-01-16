#include <bits/stdc++.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

char getch() {
#ifdef _WIN32
    return _getch();
#else
    char ch;
    struct termios oldt, newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}
struct Buffer {
	static int BufferId;
	Buffer() : Id(BufferId++),Str() {}
	int Id;
	std::string Str;
	void Insert(int Pos,std::string InsStr) {//InsStr will begin at Pos
		Str.insert(Pos,InsStr);
	}
	void Delete(int Begin,int End)
	{
		std::string tmp="";

	}
};
/*int () {
	std::cout << "\x1B[?1049h"; // 进入替代缓冲区
    std::cout << "\x1B[2J\x1B[H"; // 清屏并光标归位
    std::cout << "Hello TUI" << std::endl;
    //std::string dummy;
    //std::getline(std::cin, dummy);
    //std::cout << "请输入字符，按q退出:" << std::endl;
    
	std::cin>>std::noskipws;
    char ch;
    do {
        ch = getch();  // 无需回车
		if(ch==27) break;
		if(ch==8||ch==127) std::cout<<"\b \b";
        std::cout << ch;
    } while (ch != 27);

	std::cin>>std::skipws;
	std::cout<<"\x1B[?1049l"<<std::flush;
    //std::cout << "\x1B[?1049l"; // 返回主缓冲区
   
    return 0;
} 
*/
