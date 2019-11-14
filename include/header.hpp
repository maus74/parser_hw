// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#pragma once
#include <any>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <exception>
using namespace std;
class Json
{
	any data;
public:
	enum State
	{
		find_key_or_end,
		find_colon,
		find_value,
		find_comma_or_end
	};
	Json(const map<std::string, any>& map);

	Json(const vector<std::any>& vector);

	Json(const string& s);

	bool is_array() const;

	bool is_object() const;


	any& operator[](const string& key);

	any& operator[](int index);


	map<string, any> parse_object(const string& s,
		size_t& stance);

	vector<any> parse_arr(const string& s, size_t& stance);

	static Json parse(const string& s);

	static Json parseFile(const string& path_to_file);
};
#endif // INCLUDE_HEADER_HPP_
