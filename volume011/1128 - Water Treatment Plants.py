#!/bin/python3

import sys

def main():
	dp = [[0, 0, 0], [1, 1, 0]]
	for i in range(2, 101):
		dp.append([0, 0, 0])
		# V
		dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2]
		# >
		dp[i][1] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2]
		# <
		dp[i][2] = dp[i-1][0] + dp[i-1][2]

	for line in sys.stdin:
		n = int(line.split()[0].strip())
		print(dp[n][0] + dp[n][2])
		sys.stdout.flush()

main()