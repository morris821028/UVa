#include <stdio.h> 
#include <algorithm>
#include <map>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class Info {
	public:
		static int M, N, R, K, T;
		static map<string, int> HP, ATK;
		static string Mkind[];
		static string Rkind[];
		static string Bkind[];
};
int Info::M = 0, Info::N = 0, Info::R = 0, Info::K = 0, Info::T = 0;
map<string, int> Info::HP, Info::ATK;
string Info::Mkind[] = {"dragon", "ninja", "iceman", "lion", "wolf"};
string Info::Rkind[] = {"dragon", "iceman", "lion", "wolf", "ninja"};
string Info::Bkind[] = {"wolf", "lion", "dragon", "ninja", "iceman"};

class Weapon {
	public:
		virtual void show() {};
		virtual int getMeleeAttack() {
			return 0;
		};
		virtual int actMeleeAttack() {
			return 0;
		}; 
		virtual int getRangeAttack() {
			return 0;
		}
		virtual int actRangeAttack() {
			return 0;
		}
		virtual int getBombAttack() {
			return 0;
		}
		virtual int actBombAttack() {
			return 0;
		}
};
class Sword: public Weapon {
	public:
		int attack;
		Sword(int _attack): attack(_attack) {
			
		}
		int getMeleeAttack() {
			return attack;
		}
		int actMeleeAttack() {
			attack = attack * 8 / 10;
			return attack > 0;
		}
		void show() {
			printf("sword(%d)", attack);
		}
};
class Arrow: public Weapon {
	public:
		int R, usedTime;
		Arrow(int _R): R(_R) {
			usedTime = 0;
		}
		int getRangeAttack() {
			return usedTime < 3 ? R : 0;
		}
		int actRangeAttack() {
			usedTime++;
			return usedTime >= 3;
		}
		void show() {
			printf("arrow(%d)", 3 - usedTime);
		}
};
class Bomb: public Weapon {
	public:
		Bomb() {
			
		}
		int getBombAttack() {
			return 1;
		}
		void show() {
			printf("bomb");
		}
};
class WeaponFactory {
	public:
		static Weapon* build(int n, int attack) {
			if(n == 0) {
				if(attack / 5 <= 0)
					return NULL;
				return new Sword(attack/5);
			}
			else if(n == 2)
				return new Arrow(Info::R);
			else
				return new Bomb();
		}
};

class Warrior {
	public:
  		int n;  
  		int life;  
  		Warrior(int _n, int _life): n(_n), life(_life) {
  			
  		}  
  		virtual void show() {};  
  		virtual void showName() {};  
  		virtual void showWeapon() {};  
  		virtual int getAttack() {return 0;}
  		virtual int getFled() {return 0;}
  		virtual int getMeleeAttack() {return 0;}
  		virtual void actMeleeAttack() {}
  		virtual int getBackAttack() {return 0;}
  		virtual void actBackAttack() {}
  		virtual void move() {};
  		virtual void actRangeAttack(Warrior* o) {};
};  
class Dragon: public Warrior {  
	public:  
  		Weapon *weapon;
  		float morale;  
  		Dragon(int _n, int _life, float _morale): Warrior(_n, _life), morale(_morale) {
    		weapon = WeaponFactory::build(n%3, Info::ATK["dragon"]);
  		}  
  		void show() {
  			printf("dragon %d born\n", n);
  			printf("Its morale is %.2f\n", morale);
  		}  
  		void showName() {
  			printf("dragon %d", n);
  		}  		
		void showWeapon() {
			if(weapon != NULL)
				weapon->show();
			else
				printf("no weapon");
  		}
  		int getAttack() {
  			return Info::ATK["dragon"];
  		}
  		int getMeleeAttack() {
  			int m = 0;
  			if(weapon != NULL)
  				m = weapon->getMeleeAttack();
  			return getAttack() + m;
  		}
  		int getBackAttack() {
  			int m = 0;
  			if(weapon != NULL)
  				m = weapon->getMeleeAttack();
  			return getAttack()/2 + m;
  		}
  		void actMeleeAttack() {
  			if(weapon != NULL) {
  				int f = weapon->actMeleeAttack();
  				if(f == 0) {
  					delete weapon;
  					weapon = NULL;
  				}
  			}
  		}
  		void actBackAttack() {
  			actMeleeAttack();
  		}
  		void actRangeAttack(Warrior* o) {
  			if(weapon != NULL) {
  				o->life -= weapon->getRangeAttack();
  				int f = weapon->actRangeAttack();
  				if(f == 1) {
  					delete weapon;
  					weapon = NULL;
  				}
  			}
		}
};  
class Ninja: public Warrior {  
	public:  
		Weapon *weapon[2];  
		Ninja(int _n, int _life): Warrior(_n, _life) {
    		weapon[0] = WeaponFactory::build(n%3, Info::ATK["ninja"]);
    		weapon[1] = WeaponFactory::build((n+1)%3, Info::ATK["ninja"]);
	  	}  
  		void show() {  
    		printf("ninja %d born\n", n);
  		}  
		void showName() {
  			printf("ninja %d", n);
  		}		
		void showWeapon() {
			int f1 = n%3, f2 = (n+1)%3, f = 0;
			if(f1 < f2) {
				if(weapon[0] != NULL)
					weapon[0]->show(), f++;
				if(f)	putchar(',');
				if(weapon[1] != NULL)
					weapon[1]->show(), f++;
			} else {
				if(weapon[1] != NULL)
					weapon[1]->show(), f++;
				if(f)	putchar(',');
				if(weapon[0] != NULL)
					weapon[0]->show(), f++;
			}
			if(f == 0)
				printf("no weapon");
  		}
  		int getAttack() {
  			return Info::ATK["ninja"];
  		}  		
		int getMeleeAttack() {
  			int m = 0;
  			if(weapon[0] != NULL)
  				m += weapon[0]->getMeleeAttack();
  			if(weapon[1] != NULL)
  				m += weapon[1]->getMeleeAttack();
  			return getAttack() + m;
  		}
  		int getBackAttack() {
  			int m = 0;
  			if(weapon[0] != NULL)
  				m += weapon[0]->getMeleeAttack();
  			if(weapon[1] != NULL)
  				m += weapon[1]->getMeleeAttack();
  			return getAttack()/2 + m;
  		}
  		void actMeleeAttack() {
			if(weapon[0] != NULL) {
  				int f = weapon[0]->actMeleeAttack();
  				if(f == 0) {
  					delete weapon[0];
  					weapon[0] = NULL;
  				}
  			}
  			if(weapon[1] != NULL) {
  				int f = weapon[1]->actMeleeAttack();
  				if(f == 0) {
  					delete weapon[1];
  					weapon[1] = NULL;
  				}
  			}
  		}
  		void actBackAttack() {
  			actMeleeAttack();
  		}
  		void actRangeAttack(Warrior* o) {
  			for(int i = 0; i < 2; i++) {
  				if(weapon[i] != NULL) {
  					o->life -= weapon[i]->getRangeAttack();
  					int f = weapon[i]->actRangeAttack();
  					if(f == 1)
  						weapon[i] = NULL;
  				}
  			}
		}
};  
  
class Iceman: public Warrior {  
	public:  
  		Weapon *weapon;
  		int move_count;
  		int attack;
  		Iceman(int _n, int _life): Warrior(_n, _life) {
    		weapon = WeaponFactory::build(n%3, Info::ATK["iceman"]);
    		move_count = 0;
    		attack = Info::ATK["iceman"];
  		}  
  		void show(){  
    		printf("iceman %d born\n", n);
  		}  		
		void showName() {
  			printf("iceman %d", n);
  		}
  		void showWeapon() {
			if(weapon != NULL)
				weapon->show();
			else
				printf("no weapon");
  		}
  		int getAttack() {
  			return attack;
  		}
  		int getMeleeAttack() {
  			int m = 0;
  			if(weapon != NULL)
  				m = weapon->getMeleeAttack();
  			return getAttack() + m;
  		}  		
		int getBackAttack() {
  			int m = 0;
  			if(weapon != NULL)
  				m = weapon->getMeleeAttack();
  			return getAttack()/2 + m;
  		}
  		void actMeleeAttack() {
  			if(weapon != NULL) {
  				int f = weapon->actMeleeAttack();
  				if(f == 0) {
  					delete weapon;
  					weapon = NULL;
  				}
  			}
  		}
  		void actBackAttack() {
  			actMeleeAttack();
  		}
  		void actRangeAttack(Warrior* o) {
  			if(weapon != NULL) {
  				o->life -= weapon->getRangeAttack();
  				int f = weapon->actRangeAttack();
  				if(f == 1) {
  					delete weapon;
  					weapon = NULL;
  				}
  			}
		}
  		void move() {
  			move_count++;
  			if(move_count == 2) {
  				attack += 20;
  				life -= 9;
  				if(life <= 0)
  					life = 1;
  				move_count = 0;
  			}
  		}
};  
class Lion: public Warrior {  
	public:  
  		int loyalty;  
  		Lion(int _n, int _life, int _loyalty): Warrior(_n, _life), loyalty(_loyalty) { 
  		}  
  		void show() {
  			printf("lion %d born\n", n);
  			printf("Its loyalty is %d\n", loyalty);
  		}
  		void showName() {
  			printf("lion %d", n);
  		}	
		void showWeapon() {
			printf("no weapon");
  		}
  		int getAttack() {
  			return Info::ATK["lion"];
  		}  		
		int getMeleeAttack() {
  			return getAttack();
  		}		
		int getBackAttack() {
  			return getAttack()/2;
  		}
  		int getFled() {
  			return loyalty <= 0;
  		}
};  
class Wolf: public Warrior {  
	public:
		Weapon *weapon[3];
  		Wolf(int _n, int _life): Warrior(_n, _life) {
  			weapon[0] = weapon[1] = weapon[2] = NULL;
		} 
  		void show() {
  			printf("wolf %d born\n", n);
		} 
		void showName() {
  			printf("wolf %d", n);
  		}
		void showWeapon() {
			int f = 0;
			for(int i = 0; i < 3; i++) {
				if(weapon[i] != NULL) {
					if(f)	putchar(',');
					weapon[i]->show(), f++;
				}
			}
			if(f == 0)
				printf("no weapon");
  		}  		
		int getAttack() {
  			return Info::ATK["wolf"];
  		}  		
		int getMeleeAttack() {
  			int m = 0;
  			if(weapon[2] != NULL)
  				m = weapon[2]->getMeleeAttack();
  			return getAttack() + m;
  		}
		int getBackAttack() {
  			int m = 0;
  			if(weapon[2] != NULL)
  				m = weapon[2]->getMeleeAttack();
  			return getAttack()/2 + m;
  		}
  		void actMeleeAttack() {
			if(weapon[2] != NULL) {
  				int f = weapon[2]->actMeleeAttack();
  				if(f == 0) {
  					delete weapon[2];
  					weapon[2] = NULL;
  				}
  			}
  		}
  		void actBackAttack() {
  			actMeleeAttack();
  		}
  		void actRangeAttack(Warrior* o) {
  			if(weapon[2] != NULL) {
  				o->life -= weapon[2]->getRangeAttack();
  				int f = weapon[2]->actRangeAttack();
  				if(f == 1)
  					weapon[2] = NULL;
  			}
		}
};
class WarriorFactory {
	public:
		static Warrior* build(string kind, int n, float _morale, int _loyalty) {
			if(!strcmp(kind.c_str(), "dragon"))
				return new Dragon(n, Info::HP[kind], _morale);
			else if(!strcmp(kind.c_str(), "ninja"))
				return new Ninja(n, Info::HP[kind]);
			else if(!strcmp(kind.c_str(), "iceman"))
				return new Iceman(n, Info::HP[kind]);
			else if(!strcmp(kind.c_str(), "lion"))
				return new Lion(n, Info::HP[kind], _loyalty);
			else
				return new Wolf(n, Info::HP[kind]);				
		}
};

class Headquarter {
	public:
		int HP;
		int dir;
		int n;
		Headquarter(int _HP, int _dir): HP(_HP), dir(_dir) {
			n = 1;
		}
		void produce(vector<Warrior*> R[], vector<Warrior*> B[], int hh, int mm) {
			string kind;
			int born_cost;
			if(dir == 1) { // RED
				kind = Info::Rkind[n % 5];
			} else { // BLUE
				kind = Info::Bkind[n % 5];
			}
			born_cost = Info::HP[kind];
			if(born_cost > HP)
				return;
			HP -= born_cost;
			printf("%03d:%02d %s ", hh, mm, dir == 1 ? "red" : "blue");
			Warrior *w = WarriorFactory::build(kind, n, (double) HP/ Info::HP[kind], HP);
			w->show();
			if(dir == 1) { // RED
				R[0].push_back(w);
			} else {
				B[Info::N + 1].push_back(w);
			}
			n++;
		}
};

void simulate() {
	Headquarter RED(Info::M, 1), BLUE(Info::M, -1);
	int timescale[] = {0, 5, 10, 20, 30, 35, 38, 40, 50, 55};
	vector<Warrior*> R[Info::N + 2], B[Info::N + 2];
	int cityHP[Info::N+2], cityFlag[Info::N+2], cityBattle[Info::N+2];
	// cityFlag[], cityBattle[], NONE: 0, RED: 1, BLUE: 2 
	for(int i = 0; i <= Info::N + 1; i++)
		cityHP[i] = cityFlag[i] = cityBattle[i] = 0;
	for(int hour = 0; ; hour++) {
		for(int i = 0; i < 10; i++) {
			if(hour * 60 + timescale[i] > Info::T)
				return;
			int t = timescale[i];
			if(t == 0) { // fixed
				RED.produce(R, B, hour, t);
				BLUE.produce(R, B, hour, t);
			} else if(t == 5) { // fixed
				for(int i = 0; i <= Info::N; i++) {
					if(R[i].size() > 0) {
						if(R[i][0]->getFled()) {
							printf("%03d:%02d red ", hour, t);
							R[i][0]->showName();
							printf(" ran away\n");
							R[i].clear();
						}
					}
				}
				for(int i = 1; i <= Info::N+1; i++) {
					if(B[i].size() > 0) {
						if(B[i][0]->getFled()) {
							printf("%03d:%02d blue ", hour, t);
							B[i][0]->showName();
							printf(" ran away\n");
							B[i].clear();
						}
					}
				}
			} else if(t == 10) { // fixed
				for(int i = 0; i <= Info::N + 1; i++) {
					if(R[i].size() > 0 && i <= Info::N) {
						printf("%03d:%02d red ", hour, t);
						R[i][0]->showName();
						R[i][0]->move();
						if(i + 1 < Info::N + 1)
							printf(" marched to city %d with %d elements and force %d\n", i + 1, R[i][0]->life, R[i][0]->getAttack());
						else
							printf(" reached blue headquarter with %d elements and force %d\n", R[i][0]->life, R[i][0]->getAttack());
					}
					if(B[i].size() > 0 && i > 0) {
						printf("%03d:%02d blue ", hour, t);
						B[i][0]->showName();
						B[i][0]->move();
						if(i - 1 > 0)
							printf(" marched to city %d with %d elements and force %d\n", i - 1, B[i][0]->life, B[i][0]->getAttack());
						else
							printf(" reached red headquarter with %d elements and force %d\n", B[i][0]->life, B[i][0]->getAttack());
				
					}
				}
				for(int i = Info::N; i >= 0; i--) {
					if(R[i].size() > 0) {
						R[i+1].push_back(R[i][0]);
						R[i].clear();
					}
				}
				for(int i = 1; i <= Info::N + 1; i++) {
					if(B[i].size() > 0)	 {
						B[i-1].push_back(B[i][0]);
						B[i].clear();
					}
				}
				if(B[0].size() >= 2) {
					printf("%03d:%02d red headquarter was taken\n", hour, t);
					return ;
				}
				if(R[Info::N+1].size() >= 2) {
					printf("%03d:%02d blue headquarter was taken\n", hour, t);
					return ;
				}
			} else if(t == 20) { // fixed
				for(int i = 1; i <= Info::N; i++)
					cityHP[i] += 10;
			} else if(t == 30) { // fixed
				for(int i = 1; i <= Info::N; i++) {
					if(R[i].size() == 1 && B[i].size() == 0) {
						printf("%03d:%02d red ", hour, t);
						R[i][0]->showName();
						printf(" earned %d elements for his headquarter\n", cityHP[i]);
						RED.HP += cityHP[i], cityHP[i] = 0;
					}
					if(R[i].size() == 0 && B[i].size() == 1) {
						printf("%03d:%02d blue ", hour, t);
						B[i][0]->showName();
						printf(" earned %d elements for his headquarter\n", cityHP[i]);
						BLUE.HP += cityHP[i], cityHP[i] = 0;
					}
				}
			} else if(t == 35) { // fixed
				for(int i = 0; i <= Info::N; i++) {
					if(R[i].size() > 0 && B[i+1].size() > 0) {
						R[i][0]->actRangeAttack(B[i+1][0]);
					}
				}
				for(int i = 1; i <= Info::N + 1; i++) {
					if(B[i].size() > 0 && R[i-1].size() > 0) {
						B[i][0]->actRangeAttack(R[i-1][0]);
					}
				}
			} else if(t == 38) { // fixed
				for(int i = 0; i <= Info::N + 1; i++) {
					if(R[i].size() > 0 && B[i].size() > 0) {
						int rATK = R[i][0]->getMeleeAttack();
						int bATK = B[i][0]->getMeleeAttack();
						if(bATK >= R[i][0]->life) {
							printf("%03d:%02d red ", hour, t);
							R[i][0]->showName();
							printf(" used a bomb and killed blue ");;
							B[i][0]->showName();
							puts("");
						}
						if(rATK >= B[i][0]->life) {
							printf("%03d:%02d blue ", hour, t);
							B[i][0]->showName();
							printf(" used a bomb and killed red ");;
							R[i][0]->showName();
							puts("");
						}
						if(bATK >= R[i][0]->life || rATK >= B[i][0]->life) {
							delete R[i][0];
							R[i].clear();
							delete B[i][0];
							B[i].clear();
						}
					}
				}
			} else if(t == 40) {
				int RB[Info::N+2];
				for(int i = 1; i <= Info::N; i++) {
					RB[i] = 0;
				}
				for(int i = 1; i <= Info::N; i++) {
					if(R[i].size() > 0 && B[i].size() > 0) {
						if(R[i][0]->life <= 0 || B[i][0]->life <= 0) {
							
						} else {
							if(cityFlag[i] == 1 || (cityFlag[i] == 0 && i%2 == 1)) {
								int AT = R[i][0]->getMeleeAttack();
								B[i][0]->life -= AT;
								if(B[i][0]->life > 0) {
									int BAT = B[i][0]->getBackAttack();
									R[i][0]->life -= AT;
								}
							} else {
								int AT = B[i][0]->getMeleeAttack();
								R[i][0]->life -= AT;
								if(R[i][0]->life > 0) {
									int BAT = R[i][0]->getBackAttack();
									B[i][0]->life -= AT;
								}
							}
						}
						if(R[i][0]->life > 0 && B[i][0]->life <= 0) { 
							RB[i] = 1;
							if(cityBattle[i] == 1) {
								cityFlag[i] = 1;
							} else if(cityBattle[i] == 0) {
								cityBattle[i] = 1;
							}
						} 
						if(B[i][0]->life > 0 && R[i][0]->life <= 0) {
							RB[i] = 2;							
							if(cityBattle[i] == 2) {
								cityFlag[i] = 2;
							} else if(cityBattle[i] == 0) {
								cityBattle[i] = 2;
							}
						}
					}
					if(R[i].size() > 0 && R[i][0]->life <= 0) {
						delete R[i][0];
						R[i].clear();
					}
					if(B[i].size() > 0 && B[i][0]->life <= 0) {
						delete B[i][0];
						B[i].clear();
					}
				}
				for(int i = Info::N + 1; i >= 0; i--) {
					if(RED.HP >= 8 && RB[i] == 1) {
						RED.HP -= 8;
						R[i][0]->life += 8;
					}
				}
				for(int i = 0; i <= Info::N + 1; i++) {
					if(BLUE.HP >= 8 && RB[i] == 2) {
						BLUE.HP -= 8;
						B[i][0]->life += 8;
					}
				}
				for(int i = 0; i <= Info::N + 1; i++) {
					if(RB[i] == 1) {
						RED.HP += cityHP[i];
						cityHP[i] = 0;
					}
					if(RB[i] == 2) {
						BLUE.HP += cityHP[i];
						cityHP[i] = 0;
					}
				}
			} else if(t == 50) { // fixed
				printf("%03d:%02d %d elements in red headquarter\n", hour, t, RED.HP);
				printf("%03d:%02d %d elements in blue headquarter\n", hour, t, BLUE.HP);
			} else if(t == 55) { // fixed
				for(int i = 0; i <= Info::N + 1; i++) {
					if(R[i].size() == 1) {
						printf("%03d:%02d red ", hour, t);
						R[i][0]->showName();
						printf(" has ");
						R[i][0]->showWeapon();
						puts("");
					}
					if(B[i].size() == 1) {
						printf("%03d:%02d blue ", hour, t);
						B[i][0]->showName();
						printf(" has ");
						B[i][0]->showWeapon();
						puts("");
					}
				}
			}
		}
	}
}
int main() {  	
	freopen("in.txt", "r+t", stdin);
	freopen("out-my.txt", "w+t", stdout); 
	int testcase, cases = 0;
	scanf("%d", &testcase); 
	while(testcase--) {
		scanf("%d %d %d %d %d", &Info::M, &Info::N, &Info::R, &Info::K, &Info::T);
		for(int i = 0; i < 5; i++)
			scanf("%d", &Info::HP[Info::Mkind[i]]);
		for(int i = 0; i < 5; i++)
			scanf("%d", &Info::ATK[Info::Mkind[i]]);
		printf("Case %d:\n", ++cases);
		simulate();
	}
	return 0;
}
