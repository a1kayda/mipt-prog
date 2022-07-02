//
//  main.cpp
//  ratingofwords
//
//  Created by mac on 08/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//
#include "librate.h"


bool Isitletter(char& a)
{
    if( 'a' <= a && a <= 'z')
        return 1;
    return 0;
}
void Prepare(string& word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    for(int i = 0; i < word.size(); i++)
    {
        if(!Isitletter(word[i]))
        {
            word.erase(i, 1);
            i--;
        }
    }
}

bool Comparator(Stat& a, Stat& b)
{
    return (a.count > b.count);
}
/*
ifstream File_open(string name){
    ifstream fd;
    fd.open("/Users/mac/Desktop/prog/ratingofwords/ratingofwords/text.txt", ios_base::in);
    if (!fd.is_open()) {
        cout << "File not open" << endl;
        exit(-1);
    }
    return fd;
}
*/

map<string, int> Make_map (ifstream& fd, int& n)
{
    map<string, int> rate;
    string word;
    
    while(!fd.eof()) {
        fd >> word;
        Prepare(word);
        auto it = rate.find(word);
        if(it == rate.end()) {
            rate.insert(pair<string, int>(word, 1));
        }
        else {
            it->second++;
        }
    }

    vector<Stat> s;
    for(auto it = rate.begin(); it != rate.end(); it++) {
        struct Stat tmp;
        tmp.word = it->first;
        tmp.count = it->second;
        s.push_back(tmp);
    }
    sort(s.begin(), s.end(), Comparator);
    for(int i = 0; i < n; i++) {
        cout << s.at(i).word << ": " << s.at(i).count << endl;
    }
    fd.close();
    return rate;
}


int main() {
    int n;
	cin >> n;
    //cin >> n;
    ifstream fd ("text.txt");
   // File_open("/Users/mac/Desktop/prog/ratingofwords/ratingofwords/text.txt");
    Make_map(fd, n);
    return 0;
}

