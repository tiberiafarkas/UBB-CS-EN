"""
Given an array of integers A, maximize the value of the expression A[m] - A[n] + A[p] - A[q], where m, n, p, q are array indices with m > n > p > q.
For A = [30, 5, 15, 18, 30, 40], the maximum value is 32, obtained as 40 - 18 + 15 - 5. Display both the maximum value as well as the expression used to calculate it
"""
def print_the_computation_matrix_and_its_significance_based_on_the_alternating_expression(computation_matrix: list[list], original_array: list):
    EMPTY_SEPARATOR: str = "  "
    header_string = 4 * EMPTY_SEPARATOR + EMPTY_SEPARATOR.join([str(num) for num in original_array])

    print(header_string)
    print("-" * len(header_string))

    for index, line in enumerate(computation_matrix):
        print("- |\t" if index % 2 == 0 else "+ |\t", "\t".join(str(num) for num in line[:-1]))
    print()
    print()

def create_computed_expression_string_from_computation_matrix(computation_matrix: list[list], original_array: list[int], number_of_alternating_operations: int) -> str:
    """
    This method will compute the string of the expression calculated at the previous exercise
    :param computation_matrix:
    :param number_of_alternating_operations:
    :return:
    """
    array_length: int = len(original_array)
    terms_in_expression: list[int] = [0] * (number_of_alternating_operations + 1)

    # We'll traverse the matrix from the beginning
    current_matrix_coordinates: list[int] = [number_of_alternating_operations, 1]

    while current_matrix_coordinates[0] > 0 and current_matrix_coordinates[1] <= array_length:
        current_number_of_operands, current_array_index = current_matrix_coordinates

        while computation_matrix[current_number_of_operands][current_array_index] == computation_matrix[current_number_of_operands][current_array_index + 1]:
            current_array_index += 1

        terms_in_expression[current_number_of_operands] = original_array[current_array_index - 1]

        # Go to the previous sum
        current_matrix_coordinates = [current_number_of_operands - 1, current_array_index + 1]

    # ignore the first sign, always positive
    EXPRESSION_OFFSET: int = 2
    return " ".join(
        f"{'+' if (-1) ** (index - 1) == 1 else '-'} {num}"
        for index, num in enumerate(terms_in_expression[1:], start=1)
    )[EXPRESSION_OFFSET:]

def generate_the_maximum_value_of_alternating_expression__optimized(input_array: list):
    """
    Given an array A, we want to calculate the maximum value of the expression A[m] - A[n] + A[p] - A[q], where
    m > n > p > q are indexes.
    :param input_array:
    :return:
    """
    NUMBER_OF_ALTERNATING_OPERATIONS = 4
    array_length: int = len(input_array)

    max_value_of_the_alternating_expression_at_each_index_and_number_of_terms: list[list] = [[0] * (array_length + 2)
                                                                                             for _ in range(
            NUMBER_OF_ALTERNATING_OPERATIONS + 1)]

    # We'll first have to compute the max value of the expression at each number of terms, the indexes decreasing
    max_value_of_the_alternating_expression_at_each_index_and_number_of_terms[1][array_length] = input_array[array_length - 1]

    for number_of_terms in range(1, NUMBER_OF_ALTERNATING_OPERATIONS + 1):
        sign_of_expression: int = (-1) ** (number_of_terms - 1)

        for array_index in range(array_length - number_of_terms + 1, 0, -1):
            max_value_of_the_alternating_expression_at_each_index_and_number_of_terms[number_of_terms][
                array_index] = max(
                max_value_of_the_alternating_expression_at_each_index_and_number_of_terms[number_of_terms][
                    array_index + 1],  # the previous maximum remains
                max_value_of_the_alternating_expression_at_each_index_and_number_of_terms[number_of_terms - 1][
                    array_index + 1] + \
                sign_of_expression * input_array[array_index - 1]
            )

            print("THE CURRENT NUMBER OF TERMS IN OPERATION:", number_of_terms)
            print("CURRENT INDEX:", array_index)
            print_the_computation_matrix_and_its_significance_based_on_the_alternating_expression(
                max_value_of_the_alternating_expression_at_each_index_and_number_of_terms, input_array)

    # The solution will be at indexes [number_of_expressions, 1]
    return max_value_of_the_alternating_expression_at_each_index_and_number_of_terms[NUMBER_OF_ALTERNATING_OPERATIONS][
        1], create_computed_expression_string_from_computation_matrix(
        max_value_of_the_alternating_expression_at_each_index_and_number_of_terms,
        input_array,
        NUMBER_OF_ALTERNATING_OPERATIONS
    )

print(generate_the_maximum_value_of_alternating_expression__optimized([30, 5, 15, 18, 30, 40]))

"""
Explanation:

We can solve this problem using dynamic programming by creating a 2D array dp with 5 rows and n + 2 columns, where n is the length of the input array.
The value of dp[i][j] represents the maximum value of the expression A[m] - A[n] + A[p] - A[q], where m, n, p, q are array indices with m > n > p > q and i is the number of terms in the expression.
We initialize the first element of the first row to the last element of the input array.
We iterate over the elements of the input array and update the values of dp based on the previous values.
At the end, the maximum value of the expression will be at the indexes [number_of_expressions, 1] in the dp array.
We can also compute the expression used to calculate the maximum value by traversing the dp array from the end and keeping track of the elements used in the expression.
The time complexity of this solution is O(n), where n is the length of the input array, because we iterate over the elements of the array only once.
The space complexity is also O(n) because we use a 2D array with 5 rows and n + 2 columns.

"""