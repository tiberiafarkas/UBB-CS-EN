#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

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


int n;

set<vector<vector<int>>> solutions_set;
vector<vector<int>> partitions;
set<pair<int, int>> equiv_relations;


///function that adds partitions in the set containg all the partitions
void add_partition() {
    solutions_set.insert(partitions);
}

///function that creates the equivalance relations for a partition
void create_relations(vector<int> partitions) {
    for ( auto x : partitions )
        for ( auto y : partitions )
            equiv_relations.insert({x, y});
}

///function that prints the partitions and their equivalance relations
void print_partitions() {

    for ( auto partitions : solutions_set ) {
        for ( auto i : partitions ) {
            fout << "{";

            for ( int j = 0; j < i.size(); j++ ) {
                fout << i[j];

                if ( j < i.size() - 1 )
                    fout << ",";
            }
            fout << "} ";

            create_relations(i);
        }

        fout << " -> ";

        for ( auto relation : equiv_relations ) {
            fout << "{" << relation.first << " , " << relation.second << "} ";
        }

        fout << '\n';

        equiv_relations.clear();
    }
}

///function that generates the partitions using backtracking
void generate_partitions(vector<int> partition_stack, int index) {

    ///if we've processed all elements, add the current partition configuration
    if ( partition_stack.size() == index ) {
        add_partition();
        return;
    }

    for ( int i = 0; i < partitions.size(); ++i ) {

        partitions[i].push_back(partition_stack[index]); //add the current element to the i-th partition
        generate_partitions(partition_stack, index + 1); //generate partitions for the next element
        partitions[i].pop_back();
    }

    partitions.push_back({partition_stack[index]}); //create a new partition for the current element
    generate_partitions(partition_stack, index + 1);
    partitions.pop_back();
}



int main()
{
    ifstream fin = input_file_name();
    output_file_name();

    int i, j, nr_partitions = 0;
    fin >> n;
    fin.close();

    vector<int> partition_stack(n);

    for ( i = 0; i < n; ++i ) {
        partition_stack[i] = i + 1;
    }

    generate_partitions(partition_stack, 0);

    fout << "The number of partitions of a set with " << n << " elements is " << solutions_set.size() << '\n';
    fout << "The partitions of the set and their corresponding equivalence relations are: " << '\n';

    print_partitions();

    return 0;
}
