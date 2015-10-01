int value(int type, int width, int height, int length) {
#define max(x, y) (x > y ? x : y)
	int val[128] = {};
	val[79] = 30, val[47] = 10, val[29] = 4;
	val[82] = 5, val[26] = 3, val[22] = 9;
	if (type < 0 || type > 100 || val[type] == 0)
		return -1;
	if (width <= 0 || height <= 0 || length <= 0)
		return -2;
	int ret = 0, i;
	for (i = 1; i <= width && i <= height && i <= length; i++)
		if (width%i == 0 && height%i == 0 && length%i == 0)
		ret = max(ret, (width/i)*(height/i)*(length/i)*i*i*i*i*i*i);
	return val[type] * ret;
}
