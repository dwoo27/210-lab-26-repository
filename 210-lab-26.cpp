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

    // create containers
    vector<string> vec;
    list<string> lst;
    set<string> st;

    // times duration of reading/populating containers
    int read_v = readVector(vec, data);
    int read_l = readList(lst, data);
    int read_s = readSet(st, data);

    // sort vector
    int sort_v = sortVector(vec);

    // sort list
    int sort_l = sortList(lst);

    // sets already sorted, no need for function 
    int sort_s = -1;

    // reset and insert
    readVector(vec, data);
    int insert_v = insertVector(vec);

    readList(lst, data);
    int insert_l = insertList(lst);

    readSet(st, data);
    int insert_s = insertSet(st);

    // reset and delete
    readVector(vec, data);
    int delete_v = deleteVector(vec);

    readList(lst, data);
    int delete_l = deleteList(lst);

    readSet(st, data);
    int delete_s = deleteSet(st);

    // display all times
    cout << left << setw(12) << "Operation"
        << setw(12) << "Vector"
        << setw(12) << "List"
        << setw(12) << "Set" << endl;

    cout << left << setw(12) << "Read"
        << setw(12) << read_v
        << setw(12) << read_l
        << setw(12) << read_s << endl;

    cout << left << setw(12) << "Sort"
        << setw(12) << sort_v
        << setw(12) << sort_l
        << setw(12) << sort_s << endl;

    cout << left << setw(12) << "Insert"
        << setw(12) << insert_v
        << setw(12) << insert_l
        << setw(12) << insert_s << endl;

    cout << left << setw(12) << "Delete"
        << setw(12) << delete_v
        << setw(12) << delete_l
        << setw(12) << delete_s << endl;

    return 0;
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