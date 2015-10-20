int eval(int exp[]) {
	int n = exp[0];
	int ret = 0;
	for (int i = 2; i <= n; i += 2) {
		if (exp[i] < 1 || exp[i] > 4)		return -2147483646;
	}
	for (int i = 2; i <= n; i += 2) {
		if (exp[i] == 4 && exp[i+1] == 0)	return -2147483647;
	}
	int s = exp[1];
	for (int i = 3; i <= n; i += 2) {
		if (exp[i-1] == 1)	
			ret += s, s = exp[i];
		else if (exp[i-1] == 2)
			ret += s, s = -exp[i];
		else if (exp[i-1] == 3)
			s *= exp[i];
		else
			s /= exp[i];
	}
	ret += s;
	return ret;
}


