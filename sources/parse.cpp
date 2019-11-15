//#include <header.hpp>
#include"header.hpp"


bool Json::is_array() const
{
	try
	{
		any_cast<vector<any>>(data);
		return true;
	}
	catch (const bad_any_cast& e)
	{
		return false;
	}
}

bool Json::is_object() const
{
	try
	{
		any_cast<map<string, any>> (data);
		return true;
	}
	catch (const bad_any_cast& e)
	{
		return false;
	}
}

Json Json::parse(const string& str)
{
	return Json(str);
}

Json Json::parseFile(const string& path_to_file)
{
	ifstream file(path_to_file);
	string str;
	string line;
	while (getline(file, line))
	{
		str += line;
	}
	return Json(str);
}

string parse_str(const string& str, size_t& pos)
{
	++pos;
	string string;

	for (size_t i = pos; i < str.size(); i++)
	{
		if (str[i] == ':' || str[i] == ',') {
			throw std::logic_error("Error");
		}
		else {
			if (str[i] == '"') {
				string = str.substr(pos, i - pos);
				pos = i;
				return string;
			}
		}
	}

	return string;
}

double parse_num(const string& str, size_t& pos)
{
	std::string string;

	for (size_t i = pos; i < str.size(); ++i)
	{
		if (isdigit(str[i]) || str[i] == '.') {
			string += str[i];
		}
		else if (str[i] == ',' || str[i] == ']' || str[i] == '}'
			|| isspace(str[i])) {
			pos = --i;
			return stod(string);
		}
		else {
			throw std::invalid_argument("Error");
		}
	}
	return stof(string);
}

bool parse_bool(const std::string& str, size_t& pos)
{
	string string;

	for (size_t i = pos; i < str.size(); ++i)
	{
		if (isalpha(str[i])) {
			string += str[i];
		}
		else if (str[i] == ',' || str[i] == ']' || str[i] == '}') {
			pos = --i;
			if (string == "false") {
				return false;
			}
			else if (string == "true") {
				return true;
			}
			else {
				throw std::invalid_argument("Wrong argument");
			}
		}
		else {
			throw std::invalid_argument("Error");
		}
	}
	return false;
}

vector<any> Json::parse_arr(const string& str, size_t& pos)
{
	vector<any> result;
	++pos;
	State st = find_value;

	for (size_t i = pos; i < str.size(); ++i)
	{
		if (str[i] == '"')
		{
			if (st == find_value)
			{
				result.emplace_back(parse_str(str, i));
				st = find_comma_or_end;
			}
			else {
				throw std::invalid_argument("Error");
			}
		}
		else if (str[i] == '{') {
			if (st == find_value)
			{
				result.emplace_back(Json(parse_object(str, i)));
				st = find_comma_or_end;
			}
			else {
				throw std::invalid_argument("Error");
			}
		}
		else if (str[i] == '[') {
			if (st == find_value)
			{
				result.emplace_back(Json(parse_arr(str, i)));
				st = find_comma_or_end;
			}
			else {
				throw std::invalid_argument("Error");
			}
		}
		else if (str[i] == ']') {
			if (st == find_comma_or_end)
			{
				pos = i;
				return result;
			}
			else {
				if (st == find_value) {
					if (isdigit(str[i])) {
						result.push_back(parse_num(str, i));
					}
					else {
						if (isalpha(str[i])) {
							result.push_back(parse_bool(str, i));
						}
					}

					return result;
				}
			}
		}
		else if (str[i] == ',') {
			st = find_value;
		}
		else {
			if (st == find_value)
			{

				if (isdigit(str[i]))
				{
					result.emplace_back(parse_num(str, i));
				}
				else if (isalpha(str[i])) {
					result.emplace_back(parse_bool(str, i));
				}
				st = find_comma_or_end;
			}
			else if (!isspace(str[i])) {
				throw std::logic_error("Error");
			}
		}
	}
	return result;
}


map<string, any> Json::parse_object(const string& str, size_t& pos)
{
	map<string, any> result;
	State st = find_key_or_end;
	string key;

	for (size_t i = pos; i < str.size(); ++i)
	{
		if (str[i] == '"')
		{
			if (st == find_key_or_end)
			{
				key = parse_str(str, i);
				st = find_colon;
			}
			else if (st == find_value) {
				result[key] = parse_str(str, i);
				st = find_key_or_end;
			}
			else {
				throw std::logic_error("Error");
			}
		}
		else if (str[i] == ':') {
			if (st == find_colon) {
				st = find_value;
			}
		}
		else if (str[i] == '{') {
			if (st == find_value)
			{
				result[key] = Json(parse_object(str, i));
				st = find_key_or_end;
			}
		}
		else if (str[i] == '}') {
			if (st == find_key_or_end || st == find_comma_or_end)
			{
				pos = i;
				return result;
			}
		}
		else if (str[i] == '[') {
			if (st == find_value)
			{
				result[key] = Json(parse_arr(str, i));
				st = find_key_or_end;
			}
		}
		else if (str[i] == ']') {
			if (st == find_key_or_end || st == find_comma_or_end)
			{
				pos = i;
				return result;
			}
		}
		else if (!isspace(str[i])) {
			if (st == find_value)
			{
				if (isdigit(str[i]))
				{
					result[key] = parse_num(str, i);
				}
				else {
					result[key] = parse_bool(str, i);
				}
				st = find_key_or_end;
			}
		}
	}
	return result;
}
