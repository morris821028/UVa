#define MAXF 1000
#define MAXL 1500

struct Elevator;
typedef struct Elevator Elevator;

Elevator* newElevator(int u, int d, int F);
int up(Elevator* elevator);
int down(Elevator* elevator);
int visited(Elevator* elevator, int floor);
int getPosition(Elevator* elevator);
