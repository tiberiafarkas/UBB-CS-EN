"""
Given a set of integers A, determine if it can be partitioned into two subsets with equal sum.
For example, set A = { 1, 1, 1, 1, 2, 3, 5 } can be partitioned into sets A1 = { 1, 1, 2, 3 } and A2 = { 1, 1, 5 }, each of them having sum 7. Display one such possibility.
"""

def equal_sum_partition(A):
    total_sum = sum(A)
    if total_sum % 2 != 0:
        return False

    k = total_sum // 2
    n = len(A)
    dp = [[False for _ in range(k + 1)] for _ in range(2)]

    dp[0][0] = True
    dp[1][0] = True

    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if A[i - 1] <= j:
                dp[1][j] = dp[0][j] or dp[0][j - A[i - 1]]
            else:
                dp[1][j] = dp[0][j]

        dp[0] = dp[1][:]

    if not dp[1][k]:
        return False

    A1 = []
    A2 = []

    while n > 0:
        if dp[1][k] and dp[1][k - A[n - 1]] and k - A[n - 1] >= 0:
            A1.append(A[n - 1])
            k -= A[n - 1]
        else:
            A2.append(A[n - 1])
        n -= 1

    return A1, A2

A = [1, 1, 1, 1, 2, 3, 5]
print(equal_sum_partition(A))

"""
Explanation:

How would the table looked like if we would have solved this problem using a 2D array with n rows and k + 1 columns

    1	2	3	4	5	6	7
1	1	0	0	0	0	0	0
1	1	1	1	0	0	0	0
1	1	1	1	1	1	1	0
1	1	1	1	1	1	1	1
1	1	1	1	1	1	1	1
2	1	1	1	1	1	1	1
3	1	1	1	1	1	1	1
5	1	1	1	1	1	1	1

A 2 rows table is enough to solve this problem, as we only need the values of the previous row to compute the current row.
At the end, if the value of dp[1][k] is True, it means that the set A can be partitioned into two subsets with equal sum.

The solution to this problem is similar to the solution to the problem of finding a subset that sums to a given number.
We create a 2D array dp with two rows and k + 1 columns, where k is half of the total sum of the set A.
We initialize the first element of the first row to True.
We iterate over the elements of the set A and update the values of the dp array.
If the value of dp[1][k] is True, it means that the set A can be partitioned into two subsets with equal sum.
We then find the two subsets by starting from the last element of the set A and checking if the values of dp[i][k] and dp[i][k - A[i]] are True.
If both are True, we add the element to the first subset and subtract its value from k. Otherwise, we add the element to the second subset.
We continue this process until k becomes 0.

The time complexity of this solution is O(n * k), where n is the number of elements in the set A and k is the sum we are looking for.
The space complexity is O(k) as we only need two rows to store the values of the dp array.

The principal of optimality works in this case because the optimal solution for the subproblem of finding a subset that sums to a given number depends on the optimal solutions for smaller subproblems.

"""