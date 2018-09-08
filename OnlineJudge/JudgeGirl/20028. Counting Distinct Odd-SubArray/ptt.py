import sys
import time
import random


def num_of_distinct_subarray(nums, k):
    # initialization
    n = len(nums)
    cnt_k = 0
    i, j = 0, 0

    # number of distinct arrays
    res = 0

    # find all sub arrays start from ith
    for i in range(n):

        # j goes to right as much as possible
        while j < n:
            if cnt_k < k:
                if nums[j] % 2 == 1:
                    cnt_k += 1
                j += 1
            elif cnt_k == k:
                if nums[j] % 2 == 1:
                    break
                else:
                    j += 1

        # accumulate
        res += j - i

        # decrease cnt_k if possible
        if nums[i] % 2 == 1:
            cnt_k -= 1

    # build suffix array
    suffix_array = []
    for i in range(n):
        suffix_array.append(nums[i:])
    suffix_array.sort()

    # find lcp and minus the duplicate items
    for i in range(n - 1):
        cnt_k = 0
        prefix_len = 0
        for j in range(min(len(suffix_array[i]), len(suffix_array[i+1]))):
            # the length of prefix_len = min(prefix_len, the length of longest string containing at most k)
            if suffix_array[i][j] == suffix_array[i+1][j]:
                if suffix_array[i][j] % 2 == 1:
                    if cnt_k < k:
                        cnt_k += 1
                    elif cnt_k == k:
                        break
                prefix_len += 1
            else:
                break
        res -= prefix_len

    # return res
    return res

if __name__ == "__main__":
    try:
        while True:
            line = input()
            line = line.split()
            n = int(line[0])
            k = int(line[1])
            line = input()
            nums = [int(i) for i in line.split()]
            print(num_of_distinct_subarray(nums, k))
    except EOFError:
        pass
