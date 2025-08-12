"""
Given an n * n square matrix with integer values, find the maximum length of a snake sequence.
A snake sequence begins on the matrix's top row (coordinate (0, i), 0 <= i < n).
Each element of the sequence, except the first one, must have a value ±1 from the previous one and be located directly below, or directly to the right of the previous element.
For example, element (i, j) can be succeeded by one of the (i, j + 1) or (i + 1, j) elements.
Display the length as well as the sequence of coordinates for one sequence of maximum length.
"""

def snake_sequence(matrix):
    n = len(matrix)
    dp = [[0] * n for _ in range(n)]

    max_distance = 0
    coords = (0, 0)

    for i in range(n):
        for j in range(n):
            if abs(matrix[i][j] - matrix[i][j-1]) == 1:
                if j > 0 and dp[i][j-1] + 1 > dp[i][j]:
                    dp[i][j] = dp[i][j-1] + 1

            if abs(matrix[i][j] - matrix[i-1][j]) == 1:
                if i > 0 and dp[i-1][j] + 1 > dp[i][j]:
                    dp[i][j] = dp[i-1][j] + 1

            if dp[i][j] > max_distance:
                max_distance = dp[i][j]
                coords = (i, j)

    path = []

    i = coords[0]
    j = coords[1]

    while dp[i][j] !=  0:
        path.append((i, j))
        if j > 0 and dp[i][j-1] == dp[i][j] - 1:
            j -= 1
        elif i > 0:
            i -= 1

    return len(path) + 1, path

matrix = [[1, 5, 3, 8, 9],
          [4, 2, 4, 10, 5],
          [0, 3, 3, 5, 9],
          [1, 1, 2, 2, 4],
          [6, 0, 3, 4, 0]]

print(snake_sequence(matrix))

"""
Explanation:

How the dp table looks like:
0	0	0	0	1
0	0	1	0	0
0	1	2	0	0
1	0	3	0	0
0	1	4	5	0

We are given an n * n square matrix with integer values, and we need to find the maximum length of a snake sequence.
A snake sequence is a sequence of elements in the matrix that starts on the top row and each element is adjacent to the previous one and differs by ±1.
We can solve this problem using dynamic programming by creating a 2D array dp with the same dimensions as the matrix.
The value of each cell dp[i][j] represents the length of the snake sequence ending at the element (i, j).
We iterate over the elements of the matrix and update the values of dp based on the adjacent elements.
If the difference between the current element and the element to the left is ±1 and dp[i][j-1] + 1 has a value which is bigger then dp[i][j],
we update dp[i][j] with the value of dp[i][j-1] + 1.
If the difference between the current element and the element above is ±1 and dp[i-1][j] + 1 has a value which is bigger then dp[i][j],
we update dp[i][j] with the value of dp[i-1][j] + 1.
We keep track of the maximum distance and the coordinates of the last element of the snake sequence.
To find the actual snake sequence, we start from the last element and move back based on the values in the dp array.
We add the coordinates to the path and move to the left or up based on the values in the dp array.
The final length of the snake sequence is the length of the path plus 1, and the path contains the coordinates of the elements in the sequence.

Time complexity:
The time complexity of this solution is O(n^2) where n is the size of the matrix.
This is because we iterate over all the elements of the matrix once to calculate the values of the dp array.

Space complexity:
The space complexity of this solution is also O(n^2) because we use a 2D array dp to store the values of the snake sequence lengths.

The principality of optimality works in this case because the optimal solution for the snake sequence ending at the element (i, j) depends on the optimal solutions for the snake sequences ending at the elements (i, j-1) and (i-1, j).
The value of dp[i][j] is calculated based on the values of dp[i][j-1] and dp[i-1][j], which represent the optimal solutions for the subproblems.

"""
