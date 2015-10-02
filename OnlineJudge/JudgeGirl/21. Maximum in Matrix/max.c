int max(int A[][5]) {
	int ret = A[0][0];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			ret = ret > A[i][j] ? ret : A[i][j];
	}
	return ret;
}
