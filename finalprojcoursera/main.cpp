//
//  main.cpp
//  finalprojcoursera
//
//  Created by mac on 02/04/2019.
//  Copyright © 2019 mac. All rights reserved.
//- добавление события:                        Add Дата Событие
//- удаление события:                          Del Дата Событие
//- удаление всех событий за конкретную дату:  Del Дата
//- поиск событий за конкретную дату:          Find Дата
//- печать всех событий за все даты:           Print
#include <iostream>
#include <map>
#include <sstream>
#include <set>
#include <iomanip>
using namespace std;


class Date
{
public:
	Date (int nyear, int nmonth, int nday)
	{
		if (nmonth < 1 || nmonth > 12)
			throw out_of_range("Month value is invalid: " + to_string(nmonth));
		else if (nday < 1 || nday > 31)
			throw out_of_range("Day value is invalid: " + to_string(nday));
		_year = nyear;
		_month = nmonth;
		_day = nday;
	}
	
	int GetYear() const
	{
		return _year;
	};
	
	int GetMonth() const
	{
		return _month;
	};
	
	int GetDay() const
	{
		return _day;
	};
	
private:
	int _year; // can be less than zero
	int _month;
	int _day;
};

ostream& operator << (ostream& stream, const Date& date)
{
	stream << setfill('0') << setw(4) << to_string(date.GetYear());
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.GetMonth());
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.GetDay());
	return stream;
}

bool operator < (const Date& lhs, const Date& rhs)
{
	if (lhs.GetYear() != rhs.GetYear())
		return lhs.GetYear() < rhs.GetYear();
	else if (lhs.GetMonth() != rhs.GetMonth())
		return lhs.GetMonth() < rhs.GetMonth();
	else
		return lhs.GetDay() < rhs.GetDay();
}

Date ParseDate(const string& date)
{
	istringstream date_stream(date);
	bool f = 1;
	
	int year;
	f = f && (date_stream >> year);
	f = f && (date_stream.peek() == '-');
	date_stream.ignore(1);
	
	int month;
	f = f && (date_stream >> month);
	f = f && (date_stream.peek() == '-');
	date_stream.ignore(1);
	
	int day;
	f = f && (date_stream >> day);
	f = f && date_stream.eof();
	
	if (!f)
		throw logic_error("Wrong date format: " + date);
	return Date(year, month, day);
}

class Database
{
public:
	void AddEvent(const Date& date, const string& event)
	{
		if (!event.empty())
			_db[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event)
	{
		if (_db.count(date) > 0 && _db[date].count(event) > 0)
		{
			_db[date].erase(event);
			return 1;
		}
		return 0;
	}
	int  DeleteDate(const Date& date)
	{
		int to_del = 0;
		if (_db.count(date) > 0)
		{
			to_del = _db.at(date).size();
			_db.erase(date);
		}
		return to_del;
	}
	set<string> Find(const Date& date) const
	{
		set<string> res;
		if (_db.count(date) > 0)
			res = _db.at(date);
		return res;
	}
	void Print() const
	{
		for (const auto& r : _db)
			for (auto s : r.second)
				cout << r.first << ' ' << s << endl;
	}
	
private:
	map< Date, set<string> > _db;
};

int main()
{
	try
	{
		Database db;
		string com;
		
		while (getline(cin, com))
		{
			if(com == "")
				continue;
			stringstream input(com);
			string op;
			input >> op;
			map<string, char> ops_codes = {{"Add", 'A'}, {"Del",'D'}, {"Find", 'F'}, {"Print",'P'}};
			char op_code = ops_codes[op];
			switch(op_code)
			{
				case 'A' :
				{
					string date_str, event;
					input >> date_str >> event;
					const Date date = ParseDate(date_str);
					if (event != "" || event != " ")
						db.AddEvent(date, event);
					break;
				}
				case 'D' :
				{
					string date_str, event;
					input >> date_str;
					if (!input.eof())
						input >> event;
					const Date date = ParseDate(date_str);
					if (event.empty()) {
						const int num_of_events_to_del = db.DeleteDate(date);
						cout << "Deleted " << num_of_events_to_del << " events" << endl;
					} else {
						if (db.DeleteEvent(date, event))
							cout << "Deleted successfully" << endl;
						else
							cout << "Event not found" << endl;
					}
					break;
				}
				case 'F' :
				{
					string date_str, event;
					input >> date_str >> event;
					const Date date = ParseDate(date_str);
					set<string> events = db.Find(date);
					
					for (string e : events)
						cout << e << endl;
					break;
				}
				case 'P' :
				{
					db.Print();
					break;
				}
				default:
					cout << "Unknown command: " << op << endl;
					return 0;
			}
		}
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 0;
	}
	return 0;
}
