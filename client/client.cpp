#include "web.h"
#include <conio.h>
using namespace std;
string ip, name;
int a, b, c, d, e, now, db;
void JoinGame() {
	string msg;
	cout << "Please enter server IP:";
	cin >> ip;
	UdpSend(ip, 8889, "A|CLIENT");
	Sleep(10);
	while(msg!="A|SERVER"){
		Sleep(20);
		UdpReceive(8888, msg);
	}
	cout << "Server connected.\nPlease enter your name:";
	cin >> name;
	UdpSend(ip, 8889, "A|" + name);
	Sleep(10);
}
string cds[] = {"    0   ", "   50   ", "   75   ", "  100   ", "   x2   ", "   x3   ", "   x5   ", "   /2   ", "   /3   ", "   +1   ", "   +2   ", "   +5   ", "  +10   ", "  +20   ", "  +50   ", "  +100  ", "   -1   ", "   -2   ", "   -5   ", "  -10   ", "  -20   ", "  -50   ", "  -100  ", "  x^2   ", "  SQRT  ", "  PASS  ", "  TURN  ", " DOUBLE "};
int stc(char s) {
	if ('A' <= s) return s - 'A';
	else return s - '0';
}
void printscreen(int a, int b, int c, int d, int e, int pos) {
	system("cls");
	int num = 5;
	num -= (a == -1) + (b == -1) + (c == -1) + (d == -1) + (e == -1);
	cout << "The current number:" << now << "\nYou need to show " << db << " card(s).\n";
	for (int i = 1; i <= num; i++) cout << "---------- ";
	cout << "\n";
	for (int i = 1; i <= num; i++) cout << "|        | ";
	cout << "\n";
	for (int i = 1; i <= num; i++) cout << "|        | ";
	cout << "\n";
	if (a != -1) cout << "|" << cds[a] << "| ";
	if (b != -1) cout << "|" << cds[b] << "| ";
	if (c != -1) cout << "|" << cds[c] << "| ";
	if (d != -1) cout << "|" << cds[d] << "| ";
	if (e != -1) cout << "|" << cds[e] << "|\n";
	for (int i = 1; i <= num; i++) cout << "|        | ";
	cout << "\n";
	for (int i = 1; i <= num; i++) cout << "|        | ";
	cout << "\n";
	for (int i = 1; i <= num; i++) cout << "---------- ";
	cout << "\n";
	for (int i = 1; i <= 11 * pos - 11; i++) cout << " ";
	cout << "    /\\\n";
	for (int i = 1; i <= 11 * pos - 11; i++) cout << " ";
	cout << "   /[]\\\n";
	for (int i = 1; i <= 11 * pos - 11; i++) cout << " ";
	cout << "    []" << endl;
//	Sleep(20);
}
void GameStart() {
	string msg = "";
	cout << "Waiting Game start...";
	while (msg != "B|GAMESTART") {
		UdpReceive(8888, msg);
		Sleep(100);
	}
	UdpSend(ip, 8889, "B|OK");
	Sleep(100);
	while (msg[0] != 'C') {
		UdpReceive(8888, msg);
		Sleep(10);
	}
	a = stc(msg[2]), b = stc(msg[4]), c = stc(msg[6]), d = stc(msg[8]), e = stc(msg[10]), db = msg[12] - '0';
	printscreen(a, b, c, d, e, 1);
}
void Gaming() {
	int pos = 1;
	bool myturn = 0;
	string msg = "";
	printscreen(a, b, c, d, e, pos);
	while (1) {
		while (!myturn) {
			msg = ";";
			while (msg[0] != 'C') {
				UdpReceive(8888, msg);
				Sleep(10);
			}
			now = 0;
			int i;
			if (msg.substr(2) == "YOU DEAD") {
				cout << "YOU DEAD\n";
				return;
			}
			for (i = 2; msg[i] != '|'; i++) now = now * 10 + msg[i] - '0';
			if (msg.substr(i) == name) myturn = 1;
			printscreen(a, b, c, d, e, pos);
		}
		UdpSend(ip, 8889, "C|OK");
		while (msg[0] != 'C') {
			UdpReceive(8888, msg);
			Sleep(10);
		}
		a = stc(msg[2]), b = stc(msg[4]), c = stc(msg[6]), d = stc(msg[8]), e = stc(msg[10]), db = msg[12] - '0';
		printscreen(a, b, c, d, e, pos);
		while (!_kbhit());
		char ch = getch();
		if (ch == 'd') pos++, pos = min(pos, 5);
		if (ch == 'a') pos--, pos = max(pos, 1);
		if (ch == ' ') {
			string res = "?";
			res[0] = '0' + pos;
			UdpSend(ip, 8889, "C|" + res);
		}
		Sleep(20);
	}
}
int main() {
	JoinGame();
	GameStart();
	Gaming();
//	printscreen(-1,-1,-1,-1,1,1);
	return 0;
}
