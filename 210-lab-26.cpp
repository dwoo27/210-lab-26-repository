#include <iostream>     
#include <fstream>     
#include <iomanip>    
#include <vector>      
#include <list>        
#include <set>       
#include <string>   
#include <chrono>       // for timing
#include <algorithm>    // for sort

using namespace std;
using namespace std::chrono;

const int SZ = 20000;
const string INSERT_VAL = "TESTCODE";
const int SIM = 15;

// functions for read timing functions/also called to reset containers
int readVector(vector<string>& v, string data[]);
int readList(list<string>& l, string data[]);
int readSet(set<string>& s, string data[]);

// functions for sort timing functions
int sortVector(vector<string> v);
int sortList(list<string> l);

// functons for insert timing functions
int insertVector(vector<string> v);
int insertList(list<string> l);
int insertSet(set<string> s);

// functions for delete timing functions
int deleteVector(vector<string> v);
int deleteList(list<string> l);
int deleteSet(set<string> s);

int main() {
    // open file and read codes into array
    ifstream fin;
    fin.open("codes.txt");
    string buf;
    string data[SZ];

    if (fin.good()) {
        for (int i = 0; i < SZ; i++) {
            getline(fin, data[i]);
        }
        fin.close();
    }
    else {
        cout << "File not found";
    }

    // double for avg values
    //results[current/accum][OPP][TYPE]
    double results[2][4][3] = {0}; 
    
    for (int i = 0; i < SIM; i++) {
        // create containers
        vector<string> vec;
        list<string> lst;
        set<string> st;

        // times duration of reading/populating containers
        results[0][0][0] = readVector(vec, data);
        results[0][0][1] = readList(lst, data);
        results[0][0][2] = readSet(st, data);

        // sort vector
        results[0][1][0] = sortVector(vec);

        // sort list
        results[0][1][1] = sortList(lst);

        // sets already sorted, no need for function 
        results[0][1][2] = 0;

        // reset and insert
        readVector(vec, data);
        results[0][2][0] = insertVector(vec);

        readList(lst, data);
        results[0][2][1] = insertList(lst);

        readSet(st, data);
        results[0][2][2] = insertSet(st);

        // reset and delete
        readVector(vec, data);
        results[0][3][0] = deleteVector(vec);

        readList(lst, data);
        results[0][3][1] = deleteList(lst);

        readSet(st, data);
        results[0][3][2] = deleteSet(st);

        //loops to add current data to accumulate
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                results[1][i][j] += results[0][i][j];
            }
        }
    }
   

    // display all times
    cout << "Number of simulations: " << SIM << endl;

    cout << left << setw(12) << "Operation"
        << setw(12) << "Vector"
        << setw(12) << "List"
        << setw(12) << "Set" << endl;

    cout << right << setw(12) << "Read"
        << setw(12) << results[1][0][0] / SIM
        << setw(12) << results[1][0][1] / SIM
        << setw(12) << results[1][0][2] / SIM << endl;

    cout << right << setw(12) << "Sort"
        << setw(12) << results[1][1][0] / SIM
        << setw(12) << results[1][1][1] / SIM
        << setw(12) << results[1][1][2] / SIM << endl;

    cout << right << setw(12) << "Insert"
        << setw(12) << results[1][2][0] / SIM
        << setw(12) << results[1][2][1] / SIM
        << setw(12) << results[1][2][2] / SIM << endl;

    cout << right << setw(12) << "Delete"
        << setw(12) << results[1][3][0] / SIM
        << setw(12) << results[1][3][1] / SIM
        << setw(12) << results[1][3][2] / SIM << endl;


}

// read data into vector and return time
int readVector(vector<string>& v, string data[]) {
    // start timer
    auto start = high_resolution_clock::now();

    // clear old contents
    v.clear();

    // load data into vector
    for (int i = 0; i < SZ; i++) {
        v.push_back(data[i]);
    }

    // stop timer
    auto end = high_resolution_clock::now();

    // return time in nanoseconds
    return duration_cast<nanoseconds>(end - start).count();
}

int readList(list<string>& l, string data[]) {
    auto start = high_resolution_clock::now();

    l.clear();

    for (int i = 0; i < SZ; i++) {
        l.push_back(data[i]);
    }

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int readSet(set<string>& s, string data[]) {
    auto start = high_resolution_clock::now();

    s.clear();

    for (int i = 0; i < SZ; i++) {
        s.insert(data[i]);
    }

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int sortVector(vector<string> v) {
    auto start = high_resolution_clock::now();

    sort(v.begin(), v.end());

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int sortList(list<string> l) {
    auto start = high_resolution_clock::now();

    l.sort();

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int insertVector(vector<string> v) {
    auto start = high_resolution_clock::now();

    auto it = v.begin() + v.size() / 2;

    v.insert(it, INSERT_VAL);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int insertList(list<string> l) {
    auto start = high_resolution_clock::now();

    auto it = l.begin();
    advance(it, l.size() / 2);

    l.insert(it, INSERT_VAL);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int insertSet(set<string> s) {
    auto start = high_resolution_clock::now();

    s.insert(INSERT_VAL);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int deleteVector(vector<string> v) {
    auto start = high_resolution_clock::now();

    auto it = v.begin() + v.size() / 2;

    v.erase(it);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int deleteList(list<string> l) {
    auto start = high_resolution_clock::now();

    auto it = l.begin();
    advance(it, l.size() / 2);

    l.erase(it);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}

int deleteSet(set<string> s) {
    auto start = high_resolution_clock::now();

    auto it = s.begin();
    advance(it, s.size() / 2);

    s.erase(it);

    auto end = high_resolution_clock::now();

    return duration_cast<nanoseconds>(end - start).count();
}