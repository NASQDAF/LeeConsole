#include <iostream>
#include<cstdlib>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<iomanip>
#include<Windows.h>
#pragma region Global Variable

int const mapX = 20;
int const mapY = 10;
int freq = 30, tofreq = 1; // отношение freq к tofreq(частота выпадания)
char way = '+';
char Vmap[mapY][mapX];

bool lee(int ax, int ay, int bx, int by);
void smap(char map[mapY][mapX]);
void deploy(int grid[mapY][mapX], char map[mapY][mapX]);

//for lee
const int LmapX = mapX;
const int LmapY = mapY;
const int border = -1;
const int unseen = -2;

int px[LmapX * LmapY * 2 / 3], py[LmapX * LmapY * 2 / 3];
int len;
int grid[LmapY][LmapX];
//for lee

bool isnear = false; //for Pcheck
#pragma endregion


class s {
	
public:
	int hlth = 100,
		mana = 10,
		step = 3;

	int x, y, atk = 2;
	void ntfc() {
		std::cout << "hi" << std::endl;
	}
	void abil(int x){
		mana -= x;
	}
	void swdmg(int x) {
		std::cout << x << std::endl;
		hlth -= x;
	}
}s;

struct body {
	body(void);
	int hlth = 100;
};

body::body(void){
	hlth;
}


class enemy {
private:
	int hp = 10,
		mp = 2,
		st = 1,
		def = 1,
		dres = 2;
public:

	body * aren;
	int x, y;
	void step() {
		lee(x, y, s.x, s.y); 
		std::swap(Vmap[py[1]][px[1]], Vmap[y][x]);
	}
	void atk(int s) {
		hp -= (s-def);
		if (hp < 1)
			Vmap[x][y] = ' ';

	}
}*arren;



#pragma region Functions
void gen(char map[mapY][mapX]) {
	for (int i = 0; i < mapY; i++)
		for (int j = 0; j < mapX; j++)
			if (rand() % freq < tofreq) {
				map[i][j] = rand() % 26 + 65;
				int sz = sizeof(arren)+1;
				enemy *arren = new enemy[sz];
				arren[sz].y = i;
				arren[sz].x = j;
				
			}
			else map[i][j] = char(32);
			//map[i][j] = ggrid[i][j];
}
void smap(char map[mapY][mapX]) {
	std::system("cls");
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++)
			std::cout << std::setw(1) << map[i][j];
		std::cout << std::endl;
	}
}
void deploy(int grid[mapY][mapX]) {
	for (int i = 0; i < mapY; i++)
		for (int j = 0; j < mapX; j++)
			if (Vmap[i][j] == ' ' || Vmap[i][j] == '@' || Vmap[i][j] == way || Vmap[i][j] == 'o')
				grid[i][j] = unseen;
			else
				grid[i][j] = border;
			//grid[i][j] = ggrid[i][j];
}
bool lee(int ax, int ay, int bx, int by)
{
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	int d, x, y, k;
	bool stop;

	if (grid[ay][ax] == border || grid[by][bx] == border) return false;
	d = 0;
	grid[ay][ax] = 0;
	do {
		stop = true;
		for (y = 0; y < LmapY; ++y)
			for (x = 0; x < LmapX; ++x)
				if (grid[y][x] == d)
					for (k = 0; k < 4; ++k)
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < LmapY && ix >= 0 && ix < LmapX && grid[iy][ix] == unseen)
						{
							stop = false;
							grid[iy][ix] = d + 1;
						}
					}
		d++;
	} while (!stop && grid[by][bx] == unseen);

	if (grid[by][bx] == unseen) return false;

	len = grid[by][bx];
	x = bx;
	y = by;
	d = len;
	while (d > 0)
	{
		px[d] = x;
		py[d] = y;
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < LmapY && ix >= 0 && ix < LmapX && grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];
				std::cout << x << ":" << y << " ";
				break;
			}
		}
	}
	px[0] = ax;
	py[0] = ay;
	
	return true;
}
void path(char map[mapY][mapX], char smap[mapY][mapX]) {
	for (int i = 0; i < mapY; i++) 
		for (int j = 0; j < mapX; j++) 
			smap[i][j] = map[i][j];
}
bool Pcheck(char x, int da, int a) {
	int cx = int(x);
	if (cx >= da && cx <= a)
		isnear = true;
	else
		isnear = false;
	return isnear;
}
void clear(char smap[mapY][mapX]) {
	for (int i = 0; i < mapY; i++)
		for (int j = 0; j < mapX; j++)
			if (smap[i][j] == way)
				smap[i][j] = ' ';
}
void pathp(char smap[mapY][mapX]){
	lee(s.x, s.y, 8, 9);
	for (int i = 1; i <= len-1; i++)
		smap[py[i]][px[i]] = way;
	//map[py[0]][px[0]] = "o";
	//smap[py[len]][px[len]] = 'o';
	}
#pragma endregion


/*void enemy_event(int x, int y) {
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, -1, 0, 1 };
	for (int i = 0; i < 4;i++)
		if (Vmap[y + dy[i]][x + dx[i]] == char(64)) {
			enemy.atk(s.atk);
		}
}*/

void info() {
	using namespace std;
	cout << "________________________________\n";
	cout << "|" << setw(15) << "Coordinats X:" << setw(2) << s.y + 1 << setw(4) << "Y:" << setw(2) << s.x +1 << setw(9) <<"|\n";
	cout << "|" << setw(9) << "Health: " <<setw(2) << s.hlth << setw(3)<< sizeof(arren) << setw(10) << "|\n";
	cout << "________________________________\n";
}

int main() {
	setlocale(0, "");
	srand(time(NULL));
	s.x = 1, s.y = 1;
	char map[mapY][mapX];
	Vmap[mapY][mapX];
	gen(map);
	deploy(grid);
	map[s.x][s.y] = char(64);
	path(map, Vmap);
	smap(Vmap);
	char a = 'x'; //ловец
	int n = 0; // переключатель
	while (a != '\r') {	
		
		if (GetAsyncKeyState(VK_UP))
			if (Vmap[s.y - 1][s.x] == ' ' && s.y - 1 >= 0 || Vmap[s.y - 1][s.x] == way || Pcheck(Vmap[s.y - 1][s.x], 65, 91) && s.y - 1 >= 0) {
				keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
				//if (isnear)
					std::swap(Vmap[s.y][s.x], Vmap[s.y--][s.x]); n++;
			}

		if (GetAsyncKeyState(VK_RIGHT))
			if (Vmap[s.y][s.x + 1] == ' ' &&  s.x + 1 < mapX || Vmap[s.y][s.x + 1] == way || Pcheck(Vmap[s.y][s.x + 1], 65, 91) && s.x + 1 < mapX) {
				keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
				std::swap(Vmap[s.y][s.x], Vmap[s.y][s.x++]);	n++;
			}
		
		if (GetAsyncKeyState(VK_LEFT))
			if (Vmap[s.y][s.x - 1] == ' ' && s.x - 1 >= 0 || Vmap[s.y][s.x - 1] == way || Pcheck(Vmap[s.y][s.x - 1], 65, 91) && s.x - 1 >= 0) {
				keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
				std::swap(Vmap[s.y][s.x], Vmap[s.y][s.x--]); n++;
			}
		
		if (GetAsyncKeyState(VK_DOWN))
			if (Vmap[s.y + 1][s.x] == ' '&& s.y + 1 < mapY || Vmap[s.y + 1][s.x] == way || Pcheck(Vmap[s.y + 1][s.x], 65, 91) && s.y + 1 < mapY) {
				keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
				std::swap(Vmap[s.y][s.x], Vmap[s.y++][s.x]); n++;
			}
		if (GetAsyncKeyState(VK_SPACE))
			if (Vmap[s.y + 1][s.x] == ' ' || Vmap[s.y + 1][s.x] == way) {
				keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
				std::swap(Vmap[s.y][s.x], Vmap[s.y++][s.x]); n++;
			}
		
		if (GetAsyncKeyState(VK_RETURN)){keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);break;}
		
		if (n == 1) {
			clear(Vmap);
			//events();
			deploy(grid);
			pathp(Vmap);
			smap(Vmap);
			info();
			n--;
		}
		Sleep(40);
	}
	std::system("pause");
	delete[]arren;
	return 0;
}