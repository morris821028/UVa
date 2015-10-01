void intersection(int g[100][100], int result[4]) {
const int dx[] = {0, 0, 1, -1}; 
const int dy[] = {1, -1, 0, 0}; 
const int kd[] = {4, 3, 3, 4, 3, 2, 2, 1, 3, 2, 2, 1, 4, 1, 1, 0}; 
    int ret[5] = {}; 
    int n = 100;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            if (g[i][j] == 0) 
                continue; 
            int tx, ty, mm = 0; 
            for (int k = 0; k < 4; k++) { 
                tx = i+dx[k], ty = j+dy[k]; 
                if (tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == 0) 
                    continue; 
                mm |= 1<<k; 
            } 
            ret[kd[mm]]++; 
        } 
    } 
    for (int i = 0; i < 4; i++) 
    	result[i] = ret[i];
} 
