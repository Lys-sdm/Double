#include "web.h"
using namespace std;
string ip;
void JoinGame(){
	string msg,name;
	cout<<"Please enter server IP:";
	cin>>ip;
	UdpSend(ip,8888,"A|CLIENT");
	Sleep(10);
	UdpReceive(8888,msg);
	if (msg=="A|SERVER"){
		cout<<"Server connected.\nPlease enter your name:";
		cin>>name;
		UdpSend(ip,8888,"A|"+name);
		Sleep(10);
//		UdpReceive(8888,msg);
//		if (msg=="A|OK") cout<<"Waiting Game start...";
	}
}
string cds[] = {"0", "50", "75", "100", "x2", "x3", "x5", "/2", "/3", "+1", "+2", "+5", "+10", "+20", "+50", "+100", "-1", "-2", "-5", "-10", "-20", "-50", "-100", "x^2", "SQRT", "PASS", "TURN", "DOUBLE"};
string cdsg[200][200][200];
void initcard(){
	
}
void printscreen(){
	
	
}
void GameStart(){
	string msg="";
	cout<<"Waiting Game start...";
	while(msg!="B|GAMESTART") {
		UdpReceive(8888,msg);
		Sleep(10);
	}
}
int main(){
	JoinGame();
//	GameStart();
	
	return 0;
}
