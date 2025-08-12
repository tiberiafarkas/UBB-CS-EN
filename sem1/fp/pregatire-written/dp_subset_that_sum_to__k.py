"""
Given the set of positive integers S and the natural number k, display one of the subsets of S which sum to k.
For example, if S = { 2, 3, 5, 7, 8 } and k = 14, subset { 2, 5, 7 } sums to 14.
"""

def subset_sum(S, k):
    n = len(S)
    dp = [[False for _ in range(k + 1)] for _ in range(2)]

    dp[0][0] = True
    dp[1][0] = True

    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if S[i - 1] <= j:
                dp[1][j] = dp[0][j] or dp[0][j - S[i - 1]]
            else:
                dp[1][j] = dp[0][j]

        dp[0] = dp[1][:]

    if not dp[1][k]:
        return None

    subset = []
    while k > 0:
        if dp[1][k] and dp[1][k - S[n - 1]] and k - S[n - 1] >= 0:
            subset.append(S[n - 1])
            k -= S[n - 1]
        n -= 1

    return subset

print(subset_sum([2, 3, 5, 7, 8], 14))

"""
If we would have solved this dynamic programming problem using a 2D array with n rows, where n is the number of elements in the set S, and k columns, where k is the sum we are looking for, 
the space complexity would have been O(n * k). However, we can solve this problem using only two rows, which reduces the space complexity to O(k).
We can see that when we are computing the value of dp[i][j], we only need the values of dp[i - 1][j] and dp[i - 1][j - S[i - 1]], so two rows are enough for storing the values.


	1	2	3	4	5	6	7	8	9	10	11	12	13	14          -> sums that can be obtained
2	0	1	0	0	0	0	0	0	0	0	0	0	0	0
3	0	1	1	0	1	0	0	0	0	0	0	0	0	0
5	0	1	1	0	1	0	1	1	0	1	0	0	0	0
7	0	1	1	0	1	0	1	1	1	1	0	1	0	1
8	0	1	1	0	1	0	1	1	1	1	1	1	1	1

|
v

the values from the set

From the table above, we can use only the last 2 rows:
sums    1   2   3   4   5   6   7   8   9   10  11  12  13  14
row1    0	1	1	0	1	0	1	1	1	1	0	1	0	1
row2    0	1	1	0	1	0	1	1	1	1	1	1	1	1

In both of the tables, we mark the values that can be obtained using the elements from the set S.
At the end, when we need to find the subset that sums to k, we start from the last element of the set S and check if the value of dp[i][k] is True and if the value of dp[i][k - S[i]] is True.
If both are True, we add the element to the subset and subtract its value from k. We continue this process until k becomes 0. 

The time complexity of this solution is O(n * k), where n is the number of elements in the set S and k is the sum we are looking for 
because we still need to iterate through all the elements in the set S and all the possible sums up to k.

The space complexity of this solution is O(k) because we only need two rows to store the values of the dynamic programming table.

The principle of optimality works in this case because the optimal solution for the sum k depends on the optimal solutions for the sums k - S[i] for each element in the set S.
To be able to obtain a sum k, you must be able to obtain the sum k - value, where value is one of the elements in the set S. So each sum k is built based on the optimal solutions for the sums k - value.

"""

