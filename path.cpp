#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>



using namespace std;

const int infinity = 1e8;

const int N = 195;

int length[N][N];     // Shortest length form v1 to v2
int previ[N][N];       // Previous on a shortest path from v1 to v2



// Prints the shortest path between a and b
void printPath(int a, int b) {
    while (a != b) {
        cout << previ[a][b]+1 << " ";
        b = previ[a][b];
    }
}


// Prints all paths of length 12
void printAllLongest() {
    int l = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (length[i][j] == 12) {
                cout << j+1;
                cout << " ";
                printPath(i, j);
                cout << "\n";
            }
        }
    }
}


// Print a matrix of distances
void printLenghts() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << length[i][j] << " ";
        }
        cout << "\n";
    }
}



vector<int> visited;
int aux[20];
int best[20];
int best_length = infinity;

void path_aux(int left) {
    if (left == 0) {
        // First and last vertex on path should be as we want. 
        // It's not the most optimal way to do it, but it can 
        // be easily modified. 
        if (aux[0] != visited[0] || aux[visited.size()-1] != visited[visited.size()-1]) {
            return;
        }

        // Check if different
        set<int> all;
        for (int i = 0; i < visited.size(); i++) {
            all.insert(aux[i]);
        }

        if (all.size() < visited.size()) {
            return;
        }

        // Calc length of path

        int count = 0;
        for (int i = 0; i < visited.size()-1; i++) {
            count += length[aux[i]][aux[i+1]];
        }
        if (best_length > count) {
            best_length = count;
            for (int i = 0; i < visited.size(); i++) {
                best[i] = aux[i];
            }
        }
    }
    else {
        for (int i = 0; i < visited.size(); i++) {
            aux[visited.size() - left] = visited[i];
            path_aux(left-1);
        }
    }
}


int cin_vertices() {
    cout << "Give me the number of vertices you want\n";
    int m, node;
    cin >> m;
    cout << "Now, list all those vertices (first one will be first on path)\n";
    for (int i = 0; i < m; i++) {
        cin >> node;
        visited.push_back(node-1);
    }

    return m;
}


// An input is a number m and then m numbers
// that are vertices labels. First one will be first on path
// and last one will be last on path. It outputs the shortest
// path containing all given vertices.
void path() {
    int m = cin_vertices();

    path_aux(visited.size());

    /*    !!!! DEBUG !!!!
    for (int i = 0; i < m; i++) {
        cout << visited[i];
    }
    cout << "\n";
    for (int i = 0; i < m; i++) {
        cout << best[i];
    }
    */

    cout << best[0]+1;
    cout << " ";
    for (int i = 0; i < visited.size()-1; i++) {
        printPath(best[i+1], best[i]);
    }
}



// Inputs a distance.
// Then inputs a number m and then m vertices. The first
// vertex will be first on a path. It outputs
// m-1 paths that contain all given vertices.
// Each path has different last vertex.
// For each path inputs all vertices that can be 
// at a specified distance from the first one on
// a given path.
void all_paths() {
    set<int> possibilities;

    int dist;
    cout << "Give me the distance: \n";
    cin >> dist;

    int m = cin_vertices();

    cout << "This are the shortest paths containing those vertices\n";

    for (int k = m-1; k >= 1; k--) {
        int swap = visited[k];
        visited[k] = visited[m-1];
        visited[m-1] = swap;
        best_length = infinity;

        path_aux(visited.size());

        cout << best[0]+1;
        cout << " ";
        int l = 0;
        for (int i = 0; i < visited.size()-1; i++) {
            l += length[best[i+1]][best[i]];
            printPath(best[i+1], best[i]);
        }

        cout << " Length: " << l << "\n";

        int dist_vert = 0;

        cout << "Vertices at distance at most " << dist - l << " from the last one: ";

        for (int j = 0; j < N; j++) {
            if (length[best[m-1]][j] <= dist - l) {
                cout << j+1 << " ";
                dist_vert++;
                possibilities.insert(j+1);
            }
        }
        if (dist_vert == 0) cout << "NONE";
        cout << "\n\n";
    }

    cout << "List of all possible hideouts:\n";
    for (int i : possibilities) {
        cout << i << " ";
    }
}

int main() {
    // READING CSV

    ifstream  data("matrix.csv");
    string line;
    vector<vector<string> > matrix;
    while(getline(data,line))
    {
        stringstream lineStream(line);
        string cell;
        vector<string> parsedRow;
        while(getline(lineStream,cell,';'))
        {
            parsedRow.push_back(cell);
        }

        matrix.push_back(parsedRow);
    }

    // CSV READ





    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == "1") {
                length[i][j] = 1;
                previ[i][j] = i;
            }
            else {
                length[i][j] = infinity;
                previ[i][j] = 0; // Undefined
            }   
        }
        length[i][i] = 0;
    }


    // Floyd - Warshall algorithm

    for (int u = 0; u < N; u++) {
        for (int v1 = 0; v1 < N; v1++) {
            for (int v2 = 0; v2 < N; v2++) {
                if (length[v1][v2] > length[v1][u] + length[u][v2]) {
                    length[v1][v2] = length[v1][u] + length[u][v2];
                    previ[v1][v2] = previ[u][v2];
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        length[i][194] = length[194][i];
    }

    //printLenghts();
    //path();
    all_paths();
}