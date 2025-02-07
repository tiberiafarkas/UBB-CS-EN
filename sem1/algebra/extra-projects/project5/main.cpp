#include <iostream>
#include <fstream>
#include <vector>
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
int n, m; ///matrix dimensions
int REF[101][101]; ///row echelon form matrix
int number_of_ref_matrices = 0;
vector <string> solution;

int find_pivot(int A[101][101], int i){
    /// function to find the position of the pivot
    for(int k = 1; k <= m; ++k)
        if(A[i][k] == 1)
            return k;

    return 0;
}

bool verify_lines_under_pivot(int A[101][101], int i){
    //function to verify if the lines under the pivot are 0
    for(int j = i + 1; j <= n; ++j)
        for(int k = 1; k <= m; ++k)
            if(A[j][k] == 1)
                return 0;

    return 1;
}

int verify_row_echelon(int A[101][101]){
    //function to verify the row echelon form
    int last_pivot = 0;

    for(int i = 1; i <= n; ++i){
        int pivot = find_pivot(A, i);

        if(pivot == 0)
            return verify_lines_under_pivot(A, i);

        if(pivot <= last_pivot)
            return 0;

        for(int j = 1; j <= n; ++j)
            if(A[j][pivot] == 1 && j != i)
                return 0;

        last_pivot = pivot;
    }

    return 1;

}

void save_solution(int A[101][101]){
    //function to save the solution and write it nice
    string one_solution = "";

    for(int i = 1; i <= n; ++i){
        one_solution += "(";

        for(int j = 1; j <= m; ++j)
            if(j != m)
                one_solution += to_string(A[i][j]) + ", ";
            else if(j == m)
                one_solution += to_string(A[i][j]);

        one_solution += ")";
        one_solution += "\n";
    }
    solution.push_back(one_solution);
}

void generate_row_echelon_form_matrices(int i, int j){
    //function to generate all the matrices in row echelon form using backtracking
    for(int v = 1; v >= 0; --v){
        REF[i][j] = v;

        if(j < m)
            generate_row_echelon_form_matrices(i, j + 1);
        else if(j == m && i < n)
            generate_row_echelon_form_matrices(i + 1, 1);
        else if(i == n && j == m && verify_row_echelon(REF)){
            save_solution(REF);
            number_of_ref_matrices++;
        }
    }
}

int main(){
    ifstream fin = input_file_name();
    output_file_name();
    fin >> n >> m;

    generate_row_echelon_form_matrices(1, 1);

    fout << "The number of matrices in reduced echelon form is: " << solution.size() << "\n";
    fout << "The matrices in reduced echelon form are: \n";

    for(auto it : solution)
        fout << it << "\n";

    return 0;
}