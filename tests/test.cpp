#include <gtest/gtest.h>


#include "header.hpp"

TEST(Json, ExampleJson)
{
    std::string json = "{ \"lastname\" : \"Ivanov\" , \"firstname\" : \"Ivan\" "
                       ",  \"age\" : 25, \"islegal\" : false, \"marks\""
                       " : [4,5,5,5,2,3] , \"address\" : {  "
                       "\"city\" :"" \"Moscow\" ,  \"street\" :"
                       " \"Vozdvijenka\" } })";
    Json object = Json::parse(json);

    std::string s = "\"lastname\"";

    EXPECT_EQ(std::any_cast<double>(object["age"]), 25);
    EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(std::any_cast<std::string>(object[s]), "Ivanov");



    auto marks = any_cast<vector<any>>(object["marks"]);
    EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

    Json address = std::any_cast<Json>(object["address"]);
    EXPECT_EQ(std::any_cast<string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<string>(address["street"]), "Vozdvijenka");

}


