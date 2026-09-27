#include "web.h"
using namespace std;
#define ll long long
//0~27
string cts(int id){
	string res="?";
	if (id<=25) res[0]='A'+id;
	else res[0]='0'+id;
	return res;
}

int sorted[156] = {0, 1, 2, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27};
string cds[] = {"    0   ", "   50   ", "   75   ", "  100   ", "   x2   ", "   x3   ", "   x5   ", "   /2   ", "   /3   ", "   +1   ", "   +2   ", "   +5   ", "  +10   ", "  +20   ", "  +50   ", "  +100  ", "   -1   ", "   -2   ", "   -5   ", "  -10   ", "  -20   ", "  -50   ", "  -100  ", "  x^2   ", "  SQRT  ", "  PASS  ", "  TURN  ", "DOUBLE"};
//             0   1    2    3     4    5    6     7   8    9    10   11    12    13    14    15    16   17   18    19    20    21    22     23    24     25    26      27
int n = 156, pnum;
vector<int> tc;
queue<int> q;
struct Players {
	string name, ip;
	int db;
	int a,b,c,d,e;
};
vector<Players> player;
void Connect(int playernum) {
	pnum = playernum;
	int nowplayer = 0;
	while (nowplayer < playernum) {
		system("cls");
		cout << "player num:" << nowplayer << endl;
		string msg;
		string fromip;
		while (msg != "A|CLIENT") fromip = UdpReceive(8889, msg);
		Sleep(100);
		cout << fromip << "connecting...\n";
		UdpSend(fromip, 8888, "A|SERVER");
		Sleep(10);
		msg="";
		while (msg[0] != 'A') UdpReceive(8889, msg);
		Sleep(100);
		cout << fromip << "connected\n";
		player.push_back({msg.substr(2), fromip, 1, -1,-1,-1,-1,-1});
		nowplayer++;
	}
	Sleep(1000);
}
void GameStart() {
	for (int i = 0; i <= 156; i++) tc.push_back(sorted[i]);
	random_device rd;
	mt19937 g(rd());
	shuffle(tc.begin(), tc.end(), g);
	for (auto r : tc) q.push(r);
	for (int i=0;i<(int)(player.size());i++) {
		Sleep(10);
		UdpSend(player[i].ip, 8888, "B|GAMESTART");
		system("cls");
		cout<<"have send message to "<<player[i].ip<<"\n";
		Sleep(10);
		string msg;
		while (msg != "B|OK") UdpReceive(8889, msg);
		cout<<"User"<<player[i].name<<"is ready\n";
		Sleep(200);
		string db = "?";
		int a,b,c,d,e;
		a=q.front();
		q.pop();
		b=q.front();
		q.pop();
		c=q.front();
		q.pop();
		d=q.front();
		q.pop();
		e=q.front();
		q.pop();
		db[0]='0'+player[i].db;
		UdpSend(player[i].ip, 8888, "C|" +cts(a)+"|"+cts(b)+"|"+cts(c)+"|"+cts(d)+"|"+cts(e)+ "|" + db);
		player[i].a=a;
		player[i].b=b;
		player[i].c=c;
		player[i].d=d;
		player[i].e=e;
		Sleep(10);
	}
}
void Gaming(){
	int rplayer=player.size();
	while(rplayer>1){
		
	}
}
int main() {
	cout<<"please enter the number of players:";
	int kkk;
	cin>>kkk;
	Connect(kkk);
	GameStart();
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);

	return 0;
}
