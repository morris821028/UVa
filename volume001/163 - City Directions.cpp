// Wrong Answer WTFFFFFFFFFFF 
#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
const string dName[8] = {"E", "NE", "N", "NW", "W", "SW", "S", "SE"};
const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
void getInit(char s1[], char s2[], char d1[], int &x, int &y, int &d) {
	if(sscanf(s1, "A%d", &x) == 1) {
		if(x) {
			char t = s1[strlen(s1)-1];
			if(t == 'W')	x = -x;
		}
	}
	if(sscanf(s2, "A%d", &x) == 1) {
		if(x) {
			char t = s2[strlen(s2)-1];
			if(t == 'W')	x = -x;
		}
	}
	if(sscanf(s1, "S%d", &y) == 1) {
		if(y) {
			char t = s1[strlen(s1)-1];
			if(t == 'S')	y = -y;
		}
	}
	if(sscanf(s2, "S%d", &y) == 1) {
		if(y) {
			char t = s2[strlen(s2)-1];
			if(t == 'S')	y = -y;
		}
	}
	d = find(dName, dName + 8, d1) - dName;
}
int checkFaceDir(int x, int y, int shiftDir) {
	int vx = dx[shiftDir], vy = dy[shiftDir];
	return ((vy&&!(x%25)) || (vx&&!(y%25)) || (vx&&vy&&!((x+y)%50)) || (vx&&vy&&!((y-x)%50))) ? 0 : 1;
}
int checkAndMove(int &x, int &y, int shiftDir) {
	int tx = x + dx[shiftDir], ty = y + dy[shiftDir];
	x += dx[shiftDir], y += dy[shiftDir];
	return 1;
}

int main() {
//	freopen("h.in", "r", stdin);
//	freopen("out.txt", "w+t", stdout); 
	char strx[128], stry[128], strd[128], cmd[128], token1[128], token2[128];
	int sx, sy, dir, n;
	while(scanf("%s %s %s", &strx, &stry, &strd) == 3) {
		getInit(strx, stry, strd, sx, sy, dir);
		while(getchar() != '\n');
		int safe = 1;
		while(gets(cmd) && strcmp(cmd, "STOP")) {
			if(sscanf(cmd, " TURN %s %s", token1, token2) == 2) {
				int vx = sx, vy = sy, vdir = dir;
				checkAndMove(vx, vy, vdir);
				int w, d;
				w = !strcmp(token1, "HALF") ? 1 : 3;
				d = !strcmp(token2, "LEFT") ? 1 : -1;				
				vdir = (dir + w * d % 8 + 8)%8;	
//				printf("%d %d %d\n", vx, vy, vdir);
				int ok = checkFaceDir(vx, vy, vdir) && checkFaceDir(sx, sy, dir);
				if(!strcmp(token1, "LEFT"))
					ok = 1;
				if(dx[dir] && dy[dir])	
					ok = 0;
				if(dx[vdir] && dy[vdir]) 
					ok = 0;
				if(!strcmp(token1, "SHARP") && !strcmp(token2, "LEFT")) {
					ok = 1;
				}
//				printf("%d %d %d %d\n", dx[vdir], dy[vdir], vx, vy);
				if(dx[vdir] == dy[vdir] && !((vx+vy)%50))
					ok = 0;
				if(dx[vdir] == -dy[vdir] && !((vx-vy)%50))
					ok = 0;
				if(dx[vdir] && dy[vdir] && (vx+vy)%50 && (vx-vy)%50)
					ok = 0;
				if(ok)
					sx = vx, sy = vy, dir = vdir;
//				puts("WTF");
			} else if(sscanf(cmd, " TURN %s", token1) == 1) {
				int vx = sx, vy = sy, vdir = dir;
				checkAndMove(vx, vy, vdir);
				int w = 2, d;
				d = !strcmp(token1, "LEFT") ? 1 : -1;
				vdir = (dir + w * d % 8 + 8)%8;	
				int ok = checkFaceDir(vx, vy, vdir) && checkFaceDir(sx, sy, dir);
				if(!strcmp(token1, "LEFT"))
					ok = 1;
				if(dx[dir] && dy[dir])	
					ok = 0;
				if(dx[vdir] && dy[vdir]) 
					ok = 0;
				if(dx[vdir] == dy[vdir] && !((vx+vy)%50))
					ok = 0;
				if(dx[vdir] == -dy[vdir] && !((vx-vy)%50))
					ok = 0;
				if(dx[vdir] && dy[vdir] && (vx+vy)%50 && (vx-vy)%50)
					ok = 0;
				if(ok)
					sx = vx, sy = vy, dir = vdir;
			} else if(sscanf(cmd, " GO STRAIGHT %d", &n) == 1) {
				if(n > 0) {
					sx += dx[dir] * n;
					sy += dy[dir] * n;
				}
			} else if(sscanf(cmd, " GO %d", &n) == 1) {
				if(n > 0) {
					sx += dx[dir] * n;
					sy += dy[dir] * n;
				}
			}
//			printf(">> A%d%s S%d%s %s\n", abs(sx), sx < 0 ? "W" : (sx > 0) ? "E" : "", 
//				abs(sy), sy < 0 ? "S" : (sy > 0) ? "N" : "", dName[dir].c_str());
		}
		safe = checkFaceDir(sx, sy, dir);
		if(!safe)
			puts("Illegal stopping place");
		else {
			printf("A%d%s S%d%s %s\n", abs(sx), sx < 0 ? "W" : (sx >= 0) ? "E" : "", 
				abs(sy), sy < 0 ? "S" : (sy >= 0) ? "N" : "", dName[dir].c_str());
		}
	}
	return 0;
}
/*
A3W S2N SW
TURN       LEFT
TURN   HALF RIGHT
  TURN   RIGHT   
D        J OW DQIX Z OCOMKU WMS   I  T N P    W 
VB O
  GO   STRAIGHT    27
  GO   STRAIGHT    11
GO STRAIGHT -21
YTXDVTLBEOJKGYY
  GO          ON 64
  TURN SHARP       RIGHT
GO STRAIGHT -17
  GO   STRAIGHT    16
GO ON 6
TURN SHARP RIGHT
TURN SHARP LEFT
TURN HALF RIGHT
GO ON 43
TURN SHARP RIGHT
 EV HL ME R KD  K   V  K  UVO U  YDJ   R 
  TURN   RIGHT   
  TURN   RIGHT   
  TURN HALF    LEFT
GO ON 39
IWYTOHFHKEBGHZVDQOLWLYKRKFHRBMK
  TURN SHARP       RIGHT
  TURN HALF    LEFT
  JIL UX    Z CL TEE LD  DYFCFYO GKNV   Q 
  TURN   RIGHT   
TURN HALF LEFT
GO 17
TURN HALF LEFT
  GO          ON 64
  GO   -18
GO -12
TURN LEFT
TURN       LEFT
  GO          ON 62
GO STRAIGHT 16
  TURN   RIGHT   
TURN   HALF RIGHT
TURN RIGHT
  TURN SHARP       RIGHT
GO ON 57
TURN HALF RIGHT
  TURN HALF    LEFT
TURN HALF LEFT
  TURN         SHARP           LEFT
GO ON 20
*/
