//
//  main.cpp
//  firstex
//
//  Created by mac on 08/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//

/*#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool compare(const string& lhs, const string& rhs)
{
    if(lhs.size()>rhs.size())
    {
        return 0;
    }
    if(lhs.size()<rhs.size())
    {
        return 1;
    }
    else
    {
        if(lhs<=rhs)
        {
            return 1;
        }
        return 0;
    }
}

int main(){
    vector<string> a;
    a.push_back("1000");
    a.push_back("45678");
    a.push_back("1");
    a.push_back("5");
    a.push_back("876");
    sort(a.begin(), a.end(), compare);
    for(auto i:a)
    {
        cout<<i<<" ";
    }
    cout<<"\n";
    return 0;
}
*/
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
 
 int main()
 {
     int n, i = 0;
     vector<int> N;
     cin >> n;
     while(n != 0)
     {
         N.push_back(n % 2);
         n /= 2;
         i++;
         if(n == 0)
         {
             N.push_back(0);
             i++;
         }
     }
     for(; i > 0; i--)
     {
         if(N[i-1] != 0)
             break;
     }
     for(; i > 0; i--)
     {
         cout << N[i-1];
     }
    return 0;
 }



