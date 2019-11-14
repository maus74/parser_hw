#include"header.hpp"

// конструкторы 

Json::Json(const map<string, any>& map)
{
	data = map;
}

Json::Json(const vector<any>& vector)
{
	data = vector;
}

Json::Json(const string& str)
{
	for (size_t i = 0; i < str.size(); i++) {

		if (str[i] == '{') {
			data = parse_object(str, i);
		}
		else {
			if (str[i] == '[') {
				data = parse_arr(str, i);
			}
		}
		
	}
}
