"""
Given the set of positive integers S, partition this set into two subsets S1 and S2 so that the difference between the sum of the elements in S1 and S2 is minimal.
For example, for set S = { 1, 2, 3, 4, 5 }, the two subsets could be S1 = { 1, 2, 4 } and S2 = { 3, 5 }. Display at least one of the solutions.
"""

def partition_subset(S):
    n = len(S)
    total_sum = sum(S)
    dp = [[False for _ in range(total_sum + 1)] for _ in range(2)]

    dp[0][0] = True
    dp[1][0] = True

    for i in range(1, n + 1):
        for j in range(1, total_sum + 1):
            if S[i - 1] <= j:
                dp[1][j] = dp[0][j] or dp[0][j - S[i - 1]]
            else:
                dp[1][j] = dp[0][j]

        dp[0] = dp[1][:]

    min_diff = float('inf')
    for j in range(total_sum // 2, -1, -1):
        if dp[1][j]:
            min_diff = total_sum - 2 * j
            break

    S1 = []
    S2 = []

    while n > 0:
        if dp[1][j] and dp[1][j - S[n - 1]] and j - S[n - 1] >= 0:
            S1.append(S[n - 1])
            j -= S[n - 1]
        else:
            S2.append(S[n - 1])
        n -= 1

    return min_diff, S1, S2

print(partition_subset([1, 2, 3, 4, 5]))

"""
Explanation:

How would the table looked like if we would have solved this problem using a 2D array with n rows and total_sum + 1 columns

	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15
1	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0
2	1	1	1	0	0	0	0	0	0	0	0	0	0	0	0
3	1	1	1	1	1	0	0	0	0	0	0	0	0	0	0
4	1	1	1	1	1	1	1	1	1	1	0	0	0	0	0
5	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1

But we can solve this problem using only two rows, which reduces the space complexity to O(total_sum).
sums    1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
row1    1	1	1	1	1	1	1	1	1	1	0	0	0	0	0
row2    1	1	1	1	1	1	1	1	1	1	1	1	1	1	1


The solution to this problem is similar to the solution to the problem of finding a subset that sums to a given number.
We create a 2D array dp with two rows and total_sum + 1 columns. We initialize the first element of the first row to True.
We iterate over the elements of the set S and update the values of the dp array.
After we have computed the values of the dp array, we find the minimum difference between the two subsets.
We start from the middle of the total_sum and move towards 0 until we find a value that can be obtained using the elements from the set S. 
This happens because the difference between the two subsets is minimized when the sum of the elements in one subset is close to half of the total sum.
Then the minimum difference is total_sum - 2 * j, where j is the sum of the elements in one subset, because we know that the sum of the elements in the other subset is total_sum - j.
Finally, we reconstruct the two subsets by starting from the last element of the set S and checking if the value of dp[i][j] is True and if the value of dp[i][j - S[i]] is True, where j is the sum of the elements in one subset.
If both conditions are met, we add the element to the first subset, otherwise, we add it to the second subset.

Time Complexity:
The time complexity of this solution is O(n * total_sum), where n is the number of elements in the set S and total_sum is the sum of all the elements in the set.
This is because we need to iterate over all the elements in the set S and all the possible sums up to total_sum.

Space Complexity:
The space complexity is O(total_sum) because we only use two rows of the 2D dp array to store the values of the subproblems.

The principle of optimality works in this case because the optimal solution for the problem of partitioning a set into two subsets with minimal difference depends on the optimal solutions for the subproblems of finding subsets that sum to certain values.
"""