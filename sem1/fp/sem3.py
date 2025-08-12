"""
    time complexity notation:
        n - size of the algorithm's input
        T(n) - function that represents the number of operations carried out by the algorithm for the input size n
        after we calculate/approximate T(n) we can talk about the time complexity
        going from T(n) to time complexity:
            1. only consider the dominating term
            2. throw out any constants
        algorithm complexity:
            BigO => O(n) -> high bound on the algorithm complexity (worst case)
            BigOmega => Omega(n) -> low bound on the algorithm complexity (best case)
            Theta => Theta(n) -> the exact complexity (average case) - not sure if this exists?!

    extra space complexity:
        - how much additional memory space the algorithm requires to do its job
        - we dont consider the input

    notes:
        -> every operation that doesnt depend on 'n' takes 1 unit of time
        -> function allocates a quantity of memory that doesnt depend on 'n' -> 1 unit of space
"""