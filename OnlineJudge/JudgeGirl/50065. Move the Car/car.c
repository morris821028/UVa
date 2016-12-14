#include "car.h"
#include <stdlib.h>

CarStatusList carSimulation(CarStatus car, Command cmds[]) {
	CarStatusList ret;
	ret.num = 0;
	const int dx[] = {1, -1, 0, 0};
	const int dy[] = {0, 0, 1, -1};
	for (int i = 0; ; i++) {
		Command cmd = cmds[i];
		if (cmd.t == 0)
			break;
		if (cmd.t == 1) {
			car.g += cmd.v;
			continue;
		}
		if (cmd.v > car.g)
			break;
		cmd.t -= 2;
		car.g -= cmd.v;
		car.x += cmd.v * dx[cmd.t];
		car.y += cmd.v * dy[cmd.t];
		ret.status[ret.num++] = car;
	}
	return ret;
}
