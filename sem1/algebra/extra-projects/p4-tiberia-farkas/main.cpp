#include <fstream>
#include <vector>
#include <deque>
#include <iostream>

using namespace std;

typedef vector<int> vi;

// Vectors to store the solutions
vector<vi> solutions;
vector<int> solution;

///function that reads data from a chosen input file
ifstream input_file_name() {
    ifstream fin;
    string name;
    cout << "What is the name of the file you want to input data from? = ";
    cin >> name;
    name.append(".txt");
    fin.open(name);
    if ( !fin ) {
        cout << "Error File" << endl;
        exit(1);
    }
    return fin;
}

ofstream fout;

void output_file_name() {
    string name;
    cout << "What is the name of the file you want to save your output data? = ";
    cin >> name;
    name.append(".txt");
    fout.open(name);
}


int n, k;

// Because we are working with vector spaces over Z_2, we can view each vector as a binary representation of a number, and we can use the XOR operator as the equivalent of the sum between 2 vectors. All the numbers range from 1 to (2 ^ n - 1). For a vector to be part of the basis, the condition is that the XOR result with any previous vectors from the basis has to be greater than the vector that is already in the possible basis. If this condition is not met, the vector ca not be part of the basis.
bool check(int y) {
    for (auto x : solution) {
        if ((x ^ y) < y)
          return false;
    }
    return true;
}

// Recursive function to generate all the possible solutions
void GenerateSolutions(int lvl)
{
// If the current solution has the desired dimension, add it to the solutions vector
    if (lvl == k) {
        solutions.push_back(solution);
        return;
    }
    // For each possible vector, check if it can be part of the basis and if it can, add it to the solution and call the function again
    // The next possible vector is the one that is greater than the last one in the solution
    for (int i = solution.back() + 1; i < (1 << n); ++i) {
        if (check(i)) {
          solution.push_back(i);
          GenerateSolutions(lvl + 1);
          solution.pop_back();
        }
    }
}

// Function to print the binary representation of a number
void BinaryRepresentation(int x) {
    deque<int> nr;
    while (x) {
        nr.push_front(x & 1);
        x >>= 1;
    }
    while (nr.size() < n)
        nr.push_front(0);

    fout << "(" << nr[0];
    for (int i = 1; i < n; ++i)
        fout << ", " << nr[i];
    fout << ")";
}

int main() {
    ifstream fin = input_file_name();
    output_file_name();
    fin >> n >> k;

    // The first vector in the basis is always has to be smaller than 2 ^ (n - 1)

    for (int i = 1; i < (1 << (n - 1)); ++i) {
        solution.push_back(i);
        GenerateSolutions(1);
        solution.pop_back();
    }

    // Print the number of solutions
    fout << "The number of " << k << "-dimensional subspaces of the vector space Z^" << n << "_2 over Z_2 is " << solutions.size() << "\nA basis for each subspace is:\n";

    // Print the solutions
    for (auto v : solutions) {
        fout << "(";
        BinaryRepresentation(v[0]);

        for (int i = 1; i < k; ++i){
            fout << ", ";
            BinaryRepresentation(v[i]);
        }

        fout << ")\n";
    }

    return 0;
}
