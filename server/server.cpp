#include "web.h"
using namespace std;
#define ll long long
//0~27
int sorted[156] = {0, 1, 2, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27};
string cds[] = {"0", "50", "75", "100", "x2", "x3", "x5", "/2", "/3", "+1", "+2", "+5", "+10", "+20", "+50", "+100", "-1", "-2", "-5", "-10", "-20", "-50", "-100", "x^2", "SQRT", "PASS", "TURN", "DOUBLE"};
//             0   1    2    3     4    5    6     7   8    9    10   11    12    13    14    15    16   17   18    19    20    21    22     23    24     25    26      27
int n = 156, pnum;
vector<int> tc;
struct Players {
	string name, ip;
	int db;
	vector<int> cards;
};
vector<Players> player;
void Connect(int playernum) {
	pnum = playernum;
	vector<int> tmp;
	int nowplayer = 0;
	while (nowplayer < playernum) {
		system("cls");
		cout << "player num:" << nowplayer << endl;
		string msg;
		string fromip;
		while (msg != "A|CLIENT") fromip = UdpReceive(8888, msg);
		Sleep(10);
		cout << fromip << "connecting...\n";
		UdpSend(fromip, 8888, "A|SERVER");
		Sleep(10);
		while (msg[0] != 'A') UdpReceive(8888, msg);
		Sleep(10);
		UdpSend(fromip, 8888, "A|OK");
		cout << fromip << "connected\n";
		player.push_back({msg.substr(3), fromip, 1, tmp});
		nowplayer++;
	}
//	while(1) Sleep(10);
}
void GameStart() {
	for (int i = 0; i <= 156; i++) tc.push_back(sorted[i]);
	random_device rd;
	mt19937 g(rd());
	shuffle(tc.begin(), tc.end(), g);
	for (auto r : player) {
		UdpSend(r.ip, 8888, "B|GAMESTART");
		Sleep(10);
		string msg;
		while (msg != "B|OK") UdpReceive(8888, msg);
		Sleep(10);
		string cards = "", db = "";
		UdpSend(r.ip, 8888, "B|" + cards + "|" + db);
		Sleep(10);
	}
}
int main() {
	Connect(1);
//	GameStart();
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);

	return 0;
}
