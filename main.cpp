#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#endif
#include"./include/buffer.h"
#include"./include/edit.h"
#include"./include/cursor.h"
#include"./include/tui.h"
using std::cout;
using std::cin;
using std::flush;
using std::endl;
using std::vector;
enum KeyCode {
    KEY_ESC = 27,
    KEY_ENTER = 10,
    KEY_BACKSPACE = 127,
    KEY_UP = 256,
    KEY_DOWN = 257,
    KEY_LEFT = 258,
    KEY_RIGHT = 259,
	KEY_END = 260
};

// 最简单的 getch 函数
char getch_simple() {
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

// 处理特殊键的函数
int getchex() {
    char first_char = getch_simple();
    
    // 如果是 ESC，检查是否是方向键
    if (first_char == 27) {
        // 非阻塞地检查下一个字符
        // 使用简单的延迟，不要用 select
        #ifdef _WIN32
            // Windows: 方向键是 224 + 某个值
            if (_kbhit()) {
                char second_char = _getch();
                if (second_char == 224 && _kbhit()) {
                    char third_char = _getch();
                    switch (third_char) {
                        case 72: return KEY_UP;
                        case 80: return KEY_DOWN;
                        case 75: return KEY_LEFT;
                        case 77: return KEY_RIGHT;
                    }
                }
            }
        #else
            // Linux/macOS: 使用 usleep 等待并检查
            usleep(1000); // 10ms 延迟
            
            // 检查是否有字符可用（简化版本）
            struct termios oldt2, newt2;
            tcgetattr(STDIN_FILENO, &oldt2);
            newt2 = oldt2;
            newt2.c_lflag &= ~(ICANON | ECHO);
            newt2.c_cc[VMIN] = 0;  // 非阻塞读取
            newt2.c_cc[VTIME] = 0;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt2);
            
            char second_char = getchar();
            if (second_char == '[') {
                char third_char = getchar();
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt2);
                
                switch (third_char) {
                    case 'A': return KEY_UP;
                    case 'B': return KEY_DOWN;
                    case 'C': return KEY_RIGHT;
                    case 'D': return KEY_LEFT;
					case 'F': return KEY_END;
                }
            } else if (second_char != -1) {
                // 有其他字符，但不是方向键
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt2);
            } else {
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt2);
                return KEY_ESC;  // 单独的 ESC
            }
        #endif
        return KEY_ESC;  // 其他 ESC 序列也当作 ESC
    }
    
    return first_char;  // 返回普通字符
}
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
Buffer BUFFER=Buffer();
vector<Cursor> CURSORS;
int ROW_BEGIN=0,ROW_END=0,ROW_FACT=0,TUI_COL=10,TUI_ROW=10;
namespace Help {
	void GetHelp() {
		cout<<"=======欢迎使用 Qaaxaap-vim========"<<endl;
		cout<<"目前还在测试阶段，仅支持 qvim [file name] 以 qvim 打开文件"<<endl;
	}
}
std::pair<int,int> getTerminalSizeWithIoctl() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

//    std::cout << "终端大小 (ioctl):" << std::endl;
//    std::cout << "行数: " << w.ws_row << std::endl;
//    std::cout << "列数: " << w.ws_col << std::endl;
//    std::cout << "水平像素: " << w.ws_xpixel << std::endl;
//    std::cout << "垂直像素: " << w.ws_ypixel << std::endl;
	return {w.ws_col,w.ws_row};
}
int main(int argc,char* argv[]) {
	if(argc<2) {
		Help::GetHelp();
		return 0;
	}
	//std::ofstream DeBugLogs("qvim.log",std::ios::trunc);
	cout<<"\x1b[?1049h"<<flush;
	tui::getTerminalSize();
	CURSORS.push_back(Cursor());
	for(auto &Cur:CURSORS)
		Cur.Move(0,0),Cur.Move_fact(0,0);
	std::string FileName=argv[1];
	std::ifstream inFile(FileName.c_str());
	if(!inFile) {
		std::cerr<<"文件错误或不存在，自动创建";
	}
	else {
		std::string Line;
		while(std::getline(inFile,Line)) {
			//DeBugLogs<<"Line:"<<ROW_FACT<<" Str:"<<Line<<endl;
			std::string Ins="";
			for(char c:Line) {
				if(c==9) 
					for(int i=1;i<=4;i++) 
						Ins+=' ';
				else 
					Ins+=c;
			}
			ROW_FACT++;
			BUFFER.NewLine();
			BUFFER.Insert(ROW_FACT-1,0,Ins);
		}
		inFile.close();
	}
	if(BUFFER.size()==0)
		BUFFER.NewLine(),ROW_FACT++;
//For Test
	cin>>std::noskipws;
	for(auto &Cur:CURSORS)
		Cur.Move(0,0),Cur.Move_fact(0,0);
	//DeBugLogs<<"TUI size:"<<TUI_COL<<' '<<TUI_ROW<<endl;
	//DeBugLogs<<"File rows:"<<ROW_FACT<<endl;
	//DeBugLogs<<"First Line:"<<BUFFER.ReadLine(0)<<endl;
	tui::draw();
	while(1) {
		//for(auto Cur:CURSORS) {
			//DeBugLogs<<"Cursor Place:("<<Cur.Place_fact().first<<","<<Cur.Place_fact().second<<")"<<endl;
			//DeBugLogs<<"Cursor Screen:("<<Cur.Place_screen().first<<","<<Cur.Place_screen().second<<")"<<endl;
			//DeBugLogs<<"ROW_BEGIN:"<<ROW_BEGIN<<endl;
			//DeBugLogs<<"ROW_END:"<<ROW_END<<endl;
		//}
		int Chr;
		Chr=getchex();
		if(Chr==KEY_ESC) break;
		else if(Chr==9) {
			for(int i=1;i<=4;i++) {
				Edit::Insert(' ');
			}
		}
		else if(Chr==127) Edit::Delete();
		else if(Chr==KEY_UP) {
			for(auto &Cur:CURSORS) {
				if(Cur.Place_screen().second>=0) 
					Cur.Up();
			}
		}
		else if(Chr==KEY_DOWN) {
			for(auto &Cur:CURSORS) {
				if(Cur.Place_screen().second<ROW_FACT-1)
					Cur.Down();
			}
		}
		else if(Chr==KEY_LEFT) {
			for(auto &Cur:CURSORS) {
				if(Cur.Place_screen().first>0)
					Cur.Left();
			}
		}
		else if(Chr==KEY_RIGHT) {
			for(auto &Cur:CURSORS) {
				if(Cur.Place_screen().first<BUFFER.LineSize(Cur.Place_fact().second))
					Cur.Right();
			}
		}
		else if(Chr==KEY_END) {
			for(auto &Cur:CURSORS) {
				Cur.Move(BUFFER.LineSize(Cur.Place_fact().second),Cur.Place_screen().second);
			}
		}
		else if(Chr==4) {
			std::ofstream outFile(FileName.c_str(),std::ios::trunc);
			for(int i=0;i<BUFFER.size();i++) {
				//std::cerr<<BUFFER.ReadLine(i)<<endl;
				std::string Str=BUFFER.ReadLine(i);
				for(int i=0;i<Str.size();i++) 
					if(Str[i]!=0)
						outFile<<Str[i];
				outFile<<endl;
			}
			outFile.close();
			cout<<"File Write!"<<flush;
			usleep(300000);
		}
		else Edit::Insert((char)Chr);
		for(auto &Cur:CURSORS) {
			auto [x,y]=Cur.Place_screen();
			if(x>BUFFER.LineSize(y)) Cur.Move(BUFFER.LineSize(y),y);
		} 
		tui::draw();
		//getTerminalSizeWithIoctl();
	}
	cout<<std::skipws;
	cout<<"\x1b[?1049l"<<flush;
	return 0;
}

