//
//  Header.h
//  ratingofwords
//
//  Created by mac on 14/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

struct Stat {
    int count;
    string word;
};
ifstream file_open(string name);
bool isletter(char& a);
void prepare(string& word);
bool comparator(Stat& a, Stat& b);
map<string, int> make_map (ifstream& fd, int& n);
