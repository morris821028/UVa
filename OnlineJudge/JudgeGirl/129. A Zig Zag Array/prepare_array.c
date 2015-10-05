void prepare_array(int buffer[], int *array[], int row, int column[]) {
	int offset = 0;
	for (int i = 0; i < row; i++)
		array[i] = buffer+offset, offset += column[i];
}
