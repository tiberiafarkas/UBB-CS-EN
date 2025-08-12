"""
Maximize the profit when selling a rod of length n.
The rod can be cut into pieces of integer lengths and pieces can be sold individually.
The prices are known for each possible length.
For example, if rod length n = 7, and the price array is price = [1, 5, 8, 9, 10, 17, 17] (the price of a piece of length 3 is 8), the maximum profit is 18,
and is obtained by cutting the rod into 3 pieces, two of length two and one of length 3.
Display the profit and the length of rod sections sold to obtain it.
"""

def maximize_profit_cut_rod(n, prices):
    dp = [0] * (n + 1)
    cuts = [0] * (n + 1)

    for i in range(1, n + 1):
        max_val = float('-inf')
        for j in range(1, i + 1):
            if prices[j - 1] + dp[i - j] > max_val:
                max_val = prices[j - 1] + dp[i - j]
                cuts[i] = j
        dp[i] = max_val

    profit = dp[n]
    rod_sections = []

    while n > 0:
        rod_sections.append(cuts[n])
        n -= cuts[n]

    return profit, rod_sections

n = 7
prices = [1, 5, 8, 9, 10, 17, 17]
print(maximize_profit_cut_rod(n, prices))

"""
Explanation:
The dp array for the example above, with n = 7 and prices = [1, 5, 8, 9, 10, 17, 17], would look like this:
dp = [0, 1, 5, 8, 10, 13, 17, 18]
cuts = [0, 1, 2, 3, 2, 2, 6, 1]

These were calculated as follows:
dp[1] = max(0, 1 + dp[0]) = 1
dp[2] = max(0, 1 + dp[1], 5 + dp[0]) = 5
dp[3] = max(0, 1 + dp[2], 5 + dp[1], 8 + dp[0]) = 8
dp[4] = max(0, 1 + dp[3], 5 + dp[2], 8 + dp[1], 9 + dp[0]) = 10
dp[5] = max(0, 1 + dp[4], 5 + dp[3], 8 + dp[2], 9 + dp[1], 10 + dp[0]) = 13
dp[6] = max(0, 1 + dp[5], 5 + dp[4], 8 + dp[3], 9 + dp[2], 10 + dp[1], 17 + dp[0]) = 17
dp[7] = max(0, 1 + dp[6], 5 + dp[5], 8 + dp[4], 9 + dp[3], 10 + dp[2], 17 + dp[1], 17 + dp[0]) = 18


We are given a rod of length n and an array of prices for each piece of the rod of length i.
We need to determine the maximum profit that can be obtained by cutting the rod into pieces and selling them individually.
We can solve this problem using dynamic programming by creating a 1D array dp with n + 1 elements.
The dp array stores the maximum profit that can be obtained for each rod length.
The cuts array stores the length of the rod section that was sold to obtain the maximum profit.
We calculate the maximum profit for each rod length by considering all possible cuts and comparing the profit obtained by selling the piece with the maximum profit obtained so far.
The maximum profit for a rod length i is the maximum between the price of the cut and the maximum profit for the remaining rod length.
At the end, we reconstruct the rod sections that were sold to obtain the maximum profit by following the cuts array.

Time complexity: O(n^2) - We have two nested loops that iterate over the rod length and the possible cuts.
Space complexity: O(n) - We use two arrays of size n + 1 to store the maximum profit and the cuts.

The principal of optimality is used in this problem, as the optimal solution to the problem contains within it optimal solutions to subproblems.
The maximum profit for a rod length i depends on the maximum profit for the remaining rod length, which is a subproblem of the original problem.

"""

