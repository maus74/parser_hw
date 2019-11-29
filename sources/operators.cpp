/*#include"header.hpp"

any& Json::operator[](const string& key)
{
	if (is_object())
	{
		auto& map = any_cast<std::map<string, any>&>(data);
		return map[key];
	}

}

std::any& Json::operator[](int index)
{
	if (is_array())
	{
		auto& vector = std::any_cast<std::vector<std::any>&>(data);
		return vector[index];
	}
	else {
		throw std::logic_error("Error");
	}
}
/*
const any& Json::operator[](const string& key) const
{
	if (is_object())
	{
		auto test = data;
		auto& mmap = any_cast<map<string, any>&>(test);
		return mmap[key];
	}
	else {
		throw std::logic_error("Error");
	}
}
*/
/*
const std::any& Json::operator[](int index) const
{
	if (is_array())
	{
		auto test = data;
		auto& vector = std::any_cast<std::vector<std::any>&>(test);
		return vector[index];
	}
	else {
		throw std::logic_error("Error!!!");
	}
}
*/
