#include <bits/stdc++.h>

using namespace std;

///function that reads data from a chosen input file
ifstream input_file_name() {
    ifstream fin;
    string name;
    cout << "What is the name of the file you want to input data from? = ";
    cin >> name;
    name.append(".in");
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
    name.append(".out");
    fout.open(name);
}

// A = {a1, a2, a3, ... , an}

// a[][] = a matrix in which we store our operation table
// In our matrices, we store only the index of the element for the set (a[x][y] = 1, then in a[x][y] we have a1)
int a[10][10];

// An operation is associative <=> for any x, y, z from s, (x * y) * z = x * ( y * z ) = x * y * z
// For our matrix, we get that a[a[x][y]][z] = a[x][a[y][z]]


// Function to check if each (x, y, z) belongs to A x A x A
bool check(int n) {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k)
                if ( a[a[i][j]][k] != a[i][a[j][k]] )
                    return false;
    return true;
}

// Function to print our matrix

void print_solution(int n) {
    for (int i = 1; i <= n; ++i) {
        fout << "(a" << a[i][1];
        for (int j = 2; j <= n; ++j)
            fout << ", a" << a[i][j];
        fout << ")" << '\n';
    }
    fout << "\n";
}

// We generate all the possible matrices using the elements from the set
// If a matrix passes the check test, we increment our cnt and we print the solution
void compute_matrices(int x, int y, int val, int &cnt, int n) {
    int i;
    a[x][y] = val;
    if ( x == n && y == n ) {
        if ( check(n) ) {
            cnt++;
            if ( n <= 4 )
                print_solution(n);
        }
        return;
    }
    if ( y == n ){
        ++x;
        y = 1;
    }
    else
        ++y;
    for ( i = 1; i <= n; ++i )
        compute_matrices(x, y, i, cnt, n);
}

int main() {
    ifstream fin = input_file_name();
    output_file_name();
    int cnt, n, i;
    //cnt = nr of associative operations
    fin >> n;
    cnt = 0;

    // We assign all the values from the set A
    for ( i = 1; i <= n; ++i )
        compute_matrices(1, 1, i, cnt, n);

    fout << "The number of associative operations on a set with " << n << " elements is " << cnt << '\n';
    return 0;
}