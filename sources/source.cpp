// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include<iostream>
#include<vector>
#include "header.hpp"
using namespace std;

int main()
{
    cout<<"qwe";
    Json object = Json::parse(R"(
        {
            "lastname" : "Ivanov",
            "firstname" : "Ivan",
            "age" : 25,
            "islegal" : false,
            "marks" : [
                4,5,5,5,2,3
            ],
            "address" : {
                "city" : "Moscow",
                "street" : "Vozdvijenka"
            }
        }
    )");
    cout<<any_cast<std::string>(object["lastname"]);
    int n;
    cin>>n;
}