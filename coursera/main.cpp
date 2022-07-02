//
//  main.cpp
//  coursera
//
//  Created by mac on 13/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <initializer_list>
#include <fstream>
#include <iomanip>
using namespace std;
/*
 int Factorial(int n)
 {
        if(n <= 1)
        {
            return 1;
        }
        else
        {
            int fac = 1;
            for(int i = 1; i <= n; i++)
            {
                fac *= i;
            }
            return fac;
        }
 }
*/
/*
bool IsPalindrom(string a)
{
    if (a == "")
        return 1;
    string b = a;
    reverse(a.begin(), a.end());
    if (a == b)
        return 1;
    return 0;
}


vector<string> PalindromFilter (vector<string> words, int minLength)
{
    vector<string> res;
    for(int i = 0; i < words.size(); i++)
    {
        if(IsPalindrom(words[i]) == 1 && words[i].size() >= minLength)
            res.push_back(words[i]);
    }
    return res;
}
*/
/*
void UpdateIfGreater(int first, int & second)
{
    if(first > second)
        second = first;
}
 */
/*
 //добавление к вектору строк второго
void MoveStrings(vector<string>& source, vector<string>& destination)
{
    for(int i = 0; i < source.size(); i++)
    {
        destination.push_back(source[i]);
    }
    source.clear();
}
*/
/*
 //переворот вектора интов
void Reverse(vector<int>& v)
{
    int n;
    for( int i = 0; i < v.size()/2 ; i++)
    {
        n = v[i];
        v[i] = v[v.size()-i-1];
        v[v.size()-i-1] = n;
    }
}
vector<int> Reversed(const vector<int>& v)
{
    vector<int> res;
    res.assign(v.begin(), v.end());
    Reverse(res);
    return res;
}
 */
/*
//средняя температура

 int main() {
     int n, res = 0;
     //cin >> n;
     cin >> n;
     vector<int> temps(n);
     vector<int> result;
     for(auto i = 0; i < n; i++ )
     {
         cin >> temps[i];
     }
     for( auto i : temps)
         res += i;
     res /= temps.size();
     for(auto i = 0; i < temps.size(); i++ )
     {
         if(temps[i] > res)
        {
            result.push_back(i);
        }
     }
     cout << result.size() << endl;
     for(auto i = 0; i < result.size(); i++ )
     {
         cout<< result[i] << " ";
     }
     return 0;
 }
*/
/*
 Задача про очередь
void print_turn(vector<bool>& turn)
{
    for( auto i : turn)
    {
        cout << i << " ";
    }
    cout << endl;
}

void do_worry(vector<bool>& turn, int par)
{
    turn[par] = 1;
    //print_turn(turn);
}
void do_quiet(vector<bool>& turn, int par)
{
    turn[par] = 0;
    //print_turn(turn);
}
void do_come(vector<bool>& turn, int par)
{
    if(par > 0)
        for(int i = 0; i < par; i++)
            turn.push_back(0);
    else
        for(int i = 0; i < -par; i++)
            turn.pop_back();
   // print_turn(turn);
}
void do_worry_count(vector<bool>& turn)
{
    int res = 0;
    for(int i = 0; i < turn.size(); i++)
        if(turn[i] == 1)
            res++;
    cout << res << endl;
}
int what_com_is_it(vector<bool>& turn, vector<string> comm, string com)
{
    int c;
    for(c = 0; c < comm.size() - 1; c++)
        if(com == comm[c])
            return c;
    do_worry_count(turn);
    return 0;
}
void do_com (vector<bool>& turn, int c)
{
    int par;
    cin >> par;
    if( c == 0 )
        do_worry(turn, par);
    if( c == 1 )
        do_quiet(turn, par);
    if( c == 2 )
        do_come(turn, par);
}



int main() {
    int n, c;
    vector<bool> turn;
    vector<string> comm = { "WORRY", "QUIET", "COME", "WORRY_COUNT"};
    string com;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> com;
        c = what_com_is_it(turn, comm, com);
        if(com != comm[3])
            do_com(turn, c);
    }
    return 0;
}
 */

/*
 типа ежедневник
typedef struct Month
{
    int n;
    vector<string> a[31];
}Mnh;

void do_add(Mnh& diary)
{
    int i;
    string s;
    cin >> i >> s;
    diary.a[i-1].push_back(s);
}
void do_next(Mnh& diary)
{
    if(diary.n == 12)
        diary.n = 0;
    diary.n++;
    if(diary.n == 2)
        for(int i = 29; i <= 31; i++)
        {
            diary.a[28-1].insert(diary.a[28-1].end(), diary.a[i-1].begin(), diary.a[i-1].end());
            diary.a[i-1].clear();
        }
    if(diary.n == 4 || diary.n == 6 || diary.n == 9 || diary.n == 11)
    {
            diary.a[30-1].insert(diary.a[30-1].end(), diary.a[31-1].begin(), diary.a[31-1].end());
            diary.a[31-1].clear();
    }
}
void do_dump(Mnh& diary)
{
    int i;
    cin >> i;
    cout << diary.a[i-1]. size() << " ";
    if(diary.a[i-1]. size() == 0)
    {
        cout << endl;
        return;
    }
    for(int c = 0; c < diary.a[i-1]. size(); c++)
        cout << diary.a[i-1][c]<< " ";
    cout << endl;
}
void do_com(Mnh& diary, string com)
{
    if(com == "ADD")
        do_add(diary);
    if(com == "NEXT")
        do_next(diary);
    if(com == "DUMP")
        do_dump(diary);
}

int main()
{
    Mnh diary;
    diary.n = 1;
    int n;
    string com;
    cin >> n;
    for( int i = 0; i < n; i++)
    {
        cin >> com;
        do_com(diary, com);
    }
}
*/

/*
void compare_words(string& w1, string& w2)
{
    map<char, int> dw1, dw2;
    if(w1.size() != w2.size())
    {
        cout << "NO" << endl;
        return;
    }
    else
    {
        for(int i = 0; i < w1.size(); i++)
        {
            dw1[w1[i]]++;
            dw2[w2[i]]++;
        }
        if(dw1 == dw2)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
        
    
}
 int main()
{
    map<char, int> dw1, dw2;
    string w1, w2;
    int n;
    cin >> n;
    for( int i = 0; i < n; i++)
    {
        cin >> w1 >> w2;
        compare_words(w1, w2);
    }
    return 0;
}

*/
/*
 столицы и страны
void do_newbus(map<string, string>& dict)
{
	string country, new_capital;
	cin >> country >> new_capital;
	if(dict.count(country) == 0)
	{
		dict[country] = new_capital;
		cout << "Introduce new country " << country << " with capital " << new_capital << endl;
	}
	else if(dict[country] == new_capital)
	{
		cout << "Country " << country << " hasn't changed its capital" << endl;
	}
	else
	{
		cout << "Country " << country << " has changed its capital from " << dict[country] << " to " << new_capital << endl;
		dict[country] = new_capital;
	}
}
void do_busesforstop(map<string, string>& dict)
{
	string old_country_name, new_country_name, capital;
	cin >> old_country_name >> new_country_name;
	if(dict.count(new_country_name) == 0 && dict.count(old_country_name) != 0)
	{
		capital = dict[old_country_name];
		cout << "Country " << old_country_name << " with capital " << capital << " has been renamed to " << new_country_name << endl;
		dict.erase(old_country_name);
		dict[new_country_name] = capital;
		
	}
	else
	{
		cout << "Incorrect rename, skip" << endl;
		
	}
}
void do_stopsforbus(map<string, string>& dict)
{
	string country;
	cin >> country;
	if(dict.count(country) == 0)
		cout << "Country " << country << " doesn't exist" << endl;
	else
		cout << "Country " << country << " has capital " << dict[country] << endl;
	
}
void do_DMP(map<string, string>& dict)
{
	if(dict.empty())
		cout << "There are no countries in the world" << endl;
	else
	{
		for(auto str : dict)
		{
			cout << str.first << "/" << str.second << " ";
		}
		cout << endl;
		
	}
	
	
}

int main()
{
    int n;
	map<string, string> dict;
	string com;
    string coms[] = {"CHANGE_CAPITAL", "RENAME", "ABOUT", "DUMP"};
    cin >> n;
    for( int i = 0; i < n; i++ )
	{
		cin >> com;
		if( com == coms[0])
			do_newbus(dict);
		if( com == coms[1])
			do_busesforstop(dict);
		if( com == coms[2])
			do_stopsforbus(dict);
		if( com == coms[3])
			do_DMP(dict);
	}
	return 0;
}
 */
/*
 бляцкие автобусы
string posled = {1, '\n'};
map<string, vector<string>> dict;
bool comparator(string a, string b)
{
	if(dict[a][0][0] > dict[b][0][0])
		return 0;
	return 1;
}
void do_newbus()
{
	string bus;
	string stop;
	int n;
	vector<string> stops;
	cin >> bus >> n;
	stops.push_back(posled);
	for(int i = 0; i < n; i++)
	{
		cin >> stop;
		stops.push_back(stop);
	}
	dict[bus] = stops;
	posled[0]++;
}
vector<string> do_busesforstop(string stop)
{
	int n = 1;
	if(!stop.size())
	{
		cin >> stop;
		n = 0;
	}
	vector<string> buses;
	int i2 = 0;
	for(auto i1 : dict)
		for(int i = 1; i < i1.second.size(); i++)
			if(i1.second[i] == stop)
			{
				i2++;
				buses.push_back(i1.first);
			}
	sort(buses.begin(), buses.end(), comparator);
	if(n == 0)
		for(int i = 0; i < buses.size(); i++)
			cout << buses[i] << " ";
	if(i2 == 0)
		cout << "No stop";
	if(n == 0)
		cout << endl;
	return buses;
}
void do_stopsforbus()
{
	string bus;
	vector<string> buses;
	cin >> bus;
	if(dict[bus].empty())
	{
		cout << "No bus" << endl;
		dict.erase(bus);
		return;
	}
	for(int i = 1; i < dict[bus].size(); i++)
	{
		cout << "Stop " << dict[bus][i] << ": ";
		buses = do_busesforstop(dict[bus][i]);
		if(buses.size() == 1)
			cout << "no interchange";
		else
			for(int c = 0; c < buses.size(); c++)
			{
				if(buses[c] != bus)
					cout << buses[c] << " ";
			}
		cout << endl;
	}
	
}
void do_DMP()
{
	if(dict.empty())
		cout << "No buses" << endl;
	else
	{
		for(auto str : dict)
		{
			cout << "Bus "<< str.first << ": ";
			for(int i = 1; i < str.second.size(); i++)
				cout << str.second[i] << " ";
			cout << endl;
		}
		
	}
	
	
}

int main()
{
	int n;
	string com;
	string coms[] = {"NEW_BUS", "BUSES_FOR_STOP", "STOPS_FOR_BUS", "ALL_BUSES"};
	cin >> n;
	for( int i = 0; i < n; i++)
		{
			cin >> com;
			if( com == coms[0])
				do_newbus();
			if( com == coms[1])
				do_busesforstop("");
			if( com == coms[2])
				do_stopsforbus();
			if( com == coms[3])
				do_DMP();
		}
	return 0;
}
 */


/*
 снова автобусы
int main()
{
	int n, i1;
	map<set<string>, long int> sett;
	cin >> n;
	for( int i = 0; i < n; i++)
	{
		set<string> com;
		string comm;
		cin >> i1;
		for( int i2 = 0; i2 < i1; i2++)
		{
			cin >> comm;
			com.insert(comm);
		}
		if(sett[com] > 0)
			cout << "Already exists for " << sett[com] << endl;
		else
		{
			cout << "New bus " << sett.size() << endl;
			sett[com] = sett.size();
		}

	}
	return 0;
}

*/
/*
 синонимы
map<string, set<string>> dict;

void do_add()
{
	string first, second;
	cin >> first >> second;
	dict[first].insert(second);
	dict[second].insert(first);
}
void do_count()
{
	string s;
	cin >> s;
	cout << dict[s].size()<< endl;
}
void do_check()
{
	string first, second;
	long int i;
	cin >> first >> second;
	i = dict[first].size();
	dict[first].insert(second);
	if(dict[first].size() == i)
		cout<< "YES"<< endl;
	else
	{
		cout<< "NO"<< endl;
		dict[first].erase(second);
	}
}

int main()
{
	int n;
	string com;
	string coms[] = {"ADD", "COUNT", "CHECK"};
	cin >> n;
	for( int i = 0; i < n; i++)
	{
		cin >> com;
		if( com == coms[0])
			do_add();
		if( com == coms[1])
			do_count();
		if( com == coms[2])
			do_check();
	}
	return 0;
}
*/
/*
 
set<string> BuildMapValuesSet(const map<int, string>& m)
{
	set<string> res;
	for(auto i : m)
		res.insert(i.second);
	return res;
}
*/
/*
int main()
{
	set<string> s;
	int n;
	cin >> n;
	for(int i = 0; i < n; i++)
	{
		string str;
		cin >> str;
		s.insert(str);
		
	}
	cout<< s.size();
	return 0;
}
*/
/*
bool compare( string a, string b)
{
	for(int i1 = 0; i1 < a.size(); i1++)
		a[i1] = tolower(a[i1]);
	for(int i1 = 0; i1 < b.size(); i1++)
		b[i1] = tolower(b[i1]);
	if(a < b)
		return true;
	return false;
}
int main()
{
	int N;
	cin >> N;
	vector<string> a;
	for( int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		a.push_back(s);
	}

	sort(a.begin(), a.end(), compare);
	
	for( int i = 0; i < N; i++)
		cout << a[i] << " ";

	
	return 0;
	
}
*/
/*
string EstimateLength(const string& s) {
	return s.size() > 10 ? "long" : "short";
}
int main()
{
	{
		vector<string> w;
		w.push_back("One");
		{
			w.push_back("Two");
			{
				w.push_back("Three");
			}
		}
		for (auto s : w) {
			cout << s;
		}
	}
}
*/
/*
class SortedStrings {
public:
	void AddString(const string& s) {
		v.push_back(s);
	}
	vector<string> GetSortedStrings() {
		sort(v.begin(), v.end());
		return v;
	}
private:
	vector<string> v;
};
 */
/*
void PrintSortedStrings(SortedStrings& strings) {
	for (const string& s : strings.GetSortedStrings()) {
		cout << s << " ";
	}
	cout << endl;
}

int main() {
	SortedStrings strings;
	
	strings.AddString("first");
	strings.AddString("third");
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	strings.AddString("second");
	PrintSortedStrings(strings);
	
	return 0;
}
 */
/*
class Person {
public:
	void ChangeFirstName(int year, const string& firstname) {
		first_name[year] = firstname;
	}
	void ChangeLastName(int year, const string& lastname) {
		last_name[year] = lastname;
	}
	string GetFullName(int year) {
		string Fullname;
		int year1 = year;
		Fullname.clear();
		if(year < first_name.first(first_name.begin()))
			
		if(!first_name[year].empty())
			Fullname+=(first_name[year]);
		else
		{
			while(first_name[year].empty())
			{
				first_name.erase(year);
				year--;
			}
			Fullname+=(first_name[year]);
			if(year == 0)
				first_name.erase(year);
		}
		Fullname+=" ";
		if(!last_name[year1].empty())
			Fullname+=(last_name[year1]);
		else
		{
			while(last_name[year1].empty())
			{
				first_name.erase(year1);
				year1--;
			}
			Fullname+=(last_name[year1]);
			if(year1 == 0)
				first_name.erase(year1);
		}
		if(year == 0 && year1 == 0)
			return "Incognito";
		if(year == 0 && year1 != 0)
			Fullname+= "with unknown first name";
		if(year != 0 && year1 == 0)
			Fullname+= "with unknown last name";
		return Fullname;
	}
private:
	map<int, string> first_name;
	map<int, string> last_name;
};
*/
/*
class Person {
public:
	Person(string name1, string name2, int date)
	{
		birth = date;
		lname[birth] = name2;
		fname[birth] = name1;
	}
	void ChangeFirstName(int year, const string& first_name) {
		if(year < birth)
			return;
		fname[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		if(year < birth)
			return;
		lname[year] = last_name;
	}
	string GetFullName(int year) const
	{
		if(year < birth)
			return "No person";
		string name1, name2;
		name1.clear();
		name2.clear();
		for (auto i : fname)
		{
			if (i.first <= year)
				name1 = i.second;
			else
				break;
		}
		for (auto i : lname)
		{
			if (i.first <= year)
				name2 = i.second;
			else
				break;
		}
		if(!name1.empty() && !name2.empty())
			return name1 + " " + name2;
		else if(!name1.empty())
			return name1 + " with unknown last name";
		else if(!name2.empty())
			return name2 + " with unknown first name";
		else return "Incognito";
	}
	string GetFullNameWithHistory(int year) const
	{
		if(year < birth)
			return "No person";
		long int n;
		vector<string> name1, name2;
		string firstname, lastname;
		firstname.clear();
		lastname.clear();
		name1.clear();
		name2.clear();
		int i1 = 0, i2 = 0;
		for (auto i : fname)
		{
			i1++;
			if (i.first <= year)
				name1.push_back(i.second);
			else
				break;
		}
		for (auto i : lname)
		{
			i2++;
			if (i.first <= year)
				name2.push_back(i.second);
			else
				break;
		}
		n = name1.size();
		for(long int i = n - 1; i > 0; i--)
		{
			if(name1.at(i) == name1.at(i-1))
			{
				name1.erase(name1.begin()+i);
				
			}
		}
		n = name2.size();
		for(long int i = n - 1; i > 0; i--)
		{
			if(name2.at(i) == name2.at(i-1))
			{
				name2.erase(name2.begin()+i);
				
			}
		}
			
		for(long int i = name1.size() - 1; i >= 0; i--)
		{
			if(i == name1.size() - 1)
				firstname = name1.at(i);
			else
			{
				if(i==name1.size() - 2)
					firstname+=" (";
				firstname+=name1.at(i);
				if(i==0)
					firstname+=")";
				if(i > 0)
					firstname+=", ";
			}
		}
		for(long int i = name2.size() - 1; i >= 0; i--)
		{
			if(i == name2.size() - 1)
				lastname = name2.at(i);
			else
			{
				if(i==name2.size() - 2)
					lastname+=" (";
				lastname+=name2.at(i);
				if(i==0)
					lastname+=")";
				if(i > 0)
					lastname+=", ";
			}
		}
		if(!firstname.empty() && !lastname.empty())
			return firstname + " " + lastname;
		else if(!firstname.empty())
			return firstname + " with unknown last name";
		else if(!lastname.empty())
			return lastname + " with unknown first name";
		else return "Incognito";
	}
private:
		
	map<int, string> fname;
	map<int, string> lname;
	int birth;
};
 


int main() {
	Person person;
	
	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}
	
	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}
	
	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}
	
	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;
	
	person.ChangeFirstName(1966, "Polina");
	cout << person.GetFullNameWithHistory(1966) << endl;
	
	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}
	
	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;
	
	person.ChangeLastName(1989, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1995) << endl;
	
	return 0;
}
*/
/*
struct Specialization {
	string value;
	explicit Specialization(string new_value) {
		value = new_value;
	} };
struct Course {
	string value;
	explicit Course(string new_value) {
		value = new_value;
	}
};
struct Week {
	string value;
	explicit Week(string new_value) {
		value = new_value;
	}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;
	LectureTitle(Specialization new_day, Course new_month, Week new_year) {
		specialization = new_day.value;
		course = new_month.value;
		week = new_year.value;
	}
};


//LectureTitle title(Specialization("C++"), Course("White belt"), Week("4th"));
*/
/*
class FunctionPart { public:
	FunctionPart(char new_operation, double new_value) { operation = new_operation;
		value = new_value;
	}
	double Apply(double source_value) const {
		if (operation == '+')
			return source_value + value;
		else if (operation == '-')
			return source_value - value;
		else if (operation == '/')
			return source_value / value;
		else
			return source_value * value;
		}
	void Invert() {
		if (operation == '+')
			operation = '-';
		else if (operation == '-')
			operation = '+';
		else if (operation == '*')
			operation = '/';
		else
			operation = '*';
	}
private:
	char operation; double value;
};
class Function {
public:
	void AddPart(char operation, double value){ parts.push_back({operation, value});
	}
	double Apply(double value) const {
		for (const FunctionPart& part : parts) { value = part.Apply(value);
		}
		return value; }
	void Invert() {
		for (FunctionPart& part : parts) {
			part.Invert();
		}
		reverse(begin(parts), end(parts));
	}
private:
	vector<FunctionPart> parts;
};
*/

//struct Image {
//	double quality;
//	double freshness;
//	double rating;
//};
//
//struct Params {
//	double a;
//	double b;
//	double c;
//};
//
//Function MakeWeightFunction(const Params& params,
//							const Image& image) {
//	Function function;
//	function.AddPart('*', params.a);
//	function.AddPart('-', image.freshness * params.b);
//	function.AddPart('+', image.rating * params.c);
//	return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//	Function function = MakeWeightFunction(params, image);
//	return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//							  const Image& image,
//							  double weight) {
//	Function function = MakeWeightFunction(params, image);
//	function.Invert();
//	return function.Apply(weight);
//}
//
//int main() {
//	Image image = {10, 2, 6};
//	Params params = {4, 2, 6};
//	cout << ComputeImageWeight(params, image) << endl;
//	cout << ComputeQualityByWeight(params, image, 52) << endl;
//	return 0;
//}
//int main()
//{
//	ifstream input("input.txt");
////	ofstream output("output.txt");
////	if(!output.is_open())
////		exit(-1);
//	int n, m;
//	if(!input.is_open())
//		exit(-1);
//	int s;
//	input >> n >> m;
//	for(int i = 0; i < n; i++)
//	{
//		for(int i = 0; i < m; i++)
//		{
//			input >> s;
//			cout << setw(10) << s;
//			if(i != m-1)
//			{
//				cout << " ";
//				input.ignore(1);
//			}
//
//		}
//		cout << endl;
//	}
//	return 0;
//}
using namespace std;

class Rational {
public:
	Rational() {
		_numerator = 0;
		_denominator = 1;
	}
	
	Rational(int numerator, int denominator) {
		bool neg = 0;
		if(denominator < 0)
		{
			numerator = -numerator;
			denominator = -denominator;
		}
		if(numerator < 0)
			neg = 1;
		int a = numerator, b = denominator;
		if( neg == 1 )
			a = - a;
		while (a > 0 && b > 0)
		{
			if (a > b)
				a %= b;
			else
				b %= a;
		}
		numerator /= (a + b);
		denominator /= (a + b);
		_numerator = numerator;
		_denominator = denominator;
	}
	friend istream& operator >> (istream& stream, Rational& r);
	friend ostream& operator << (ostream& stream, const Rational& r);
	Rational operator + (Rational right)
	{
		return Rational (_numerator*right._denominator+right._numerator*_denominator,_denominator*right._denominator);
	}
	Rational operator - (Rational right)
	{
			return Rational (_numerator*right._denominator-right._numerator*_denominator,_denominator*right._denominator);
	}
	bool operator == (const Rational right)
	{
		if(_numerator == right._numerator && _denominator == right._denominator)
			return true;
		return false;
	}
	Rational operator * (Rational right)
	{
		return Rational (_numerator*right._numerator,_denominator*right._denominator);
	}
	Rational operator / (Rational right)
	{
		return Rational (_numerator*right._denominator,_denominator*right._numerator);
	}
	bool operator < (const Rational right)
	{
		if(_numerator*right._denominator-right._numerator*_denominator < 0)
			return true;
		return false;
	}
	bool operator >(const Rational right)
	{
		if(*this < right && *this == right)
			return false;
		return true;
	}
	bool operator >= (const Rational right)
	{
		if(*this < right)
			return false;
		return true;
	}
	bool operator <= (const Rational right)
	{
		if(*this < right && *this == right)
			return true;
		return false;
	}
	
	int Numerator() const {
		return _numerator;
	}
	
	int Denominator() const {
		return _denominator;
	}
	
private:
	int _numerator;
	int _denominator;
};
istream& operator >> (istream& stream, Rational& r)
{
	stream >> r._numerator >> r._denominator;
	return stream;
}
ostream& operator << (ostream& stream, const Rational& r)
{
	stream << r._numerator << "/" << r._denominator << endl;
	return stream;
}

int main() {
	{
		const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
