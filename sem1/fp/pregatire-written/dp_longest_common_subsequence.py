"""
Determine the longest common subsequence of two given sequences.
Subsequence elements are not required to occupy consecutive positions.
For example, if X = "MNPNQMN" and Y = "NQPMNM", the longest common subsequence has length 4, and can be one of "NQMN", "NPMN" or "NPNM".
Determine and display both the length of the longest common subsequence as well as at least one such subsequence.
"""


def longest_common_subsequence(X, Y):
    m = len(X)
    n = len(Y)
    dp = [[0] * (n + 1) for i in range(m + 1)]
    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0 or j == 0:
                dp[i][j] = 0
            elif X[i - 1] == Y[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    index = dp[m][n]
    lcs = [""] * (index)
    i = m
    j = n
    while i > 0 and j > 0:
        if X[i - 1] == Y[j - 1]:
            lcs[index - 1] = X[i - 1]
            i -= 1
            j -= 1
            index -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    return dp[m][n], lcs

print(longest_common_subsequence("MNPNQMN", "NQPMNM"))

"""
How the table looks like:
    ^ 
<-- |       

It is a 2D table where the rows represent the elements of the first sequence and the columns represent the elements of the second sequence.
The value of each cell is the length of the longest common subsequence of the two sequences up to that point, calculated as follows:
- If the elements at the current position are the same, the value is the value of the cell to the top-left plus 1.
- If the elements are different, the value is the maximum of the value to the left and the value above.
The final value is the one in the bottom-right cell of the table.

	M	N	P	Q	M	N
N	0	1	1	1	1	1
Q	0	1	1	2	2	2
P	0	1	2	2	2	2
M	1	1	2	2	3	3
N	1	2	2	3	3	4
M	2	2	2	3	4	4

To determine the actual subsequence, we start from the bottom-right cell and move diagonally to the top-left, following these rules:
- If the elements at the current position are the same, add the element to the subsequence and move diagonally to the top-left.
- If the values to the left and above are equal, move to the left.
- Otherwise, move up.
- Repeat until reaching the top or left edge of the table.

Time Complexity:
The time complexity of this approach is O(m*n), where m and n are the lengths of the two sequences.
This is because we fill in an m x n table, with each cell taking constant time to calculate.

Space Complexity:
The space complexity is also O(m*n) as we use a 2D table to store the values of the subproblems.

The principal of optimality works in this case because the optimal solution for the subproblem of finding the longest common subsequence of two sequences depends 
on the optimal solutions for the subproblems of finding the longest common subsequences of the prefixes of the sequences.
You can build the solution for the entire sequence based on the solutions for the subsequences of the prefixes, which is the essence of dynamic programming.

"""


