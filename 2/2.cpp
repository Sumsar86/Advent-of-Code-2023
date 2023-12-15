#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>



std::string removeLeadingSpaces(const std::string& input) 
{
    size_t pos = input.find_first_not_of(" \t"); // Find the first non-space character
    if (pos != std::string::npos) 
    {
        return input.substr(pos); // Return the substring starting from the first non-space character
    } else 
    {
        return ""; // If the string is all spaces, return an empty string
    }
}

std::vector<std::string> splitString(std::string& s, std::string delimiter, std::string delimiter2 = "") 
{
    std::vector<std::string> tokens = {};
    std::string token;
    size_t pos = 0;
    if (delimiter2 != "")
    {
        while ((pos = std::min(s.find(delimiter), s.find(delimiter2))) != std::string::npos) 
        {
            token = s.substr(0, pos);
            tokens.push_back(removeLeadingSpaces(token));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(removeLeadingSpaces(s));
    }
    else
    {
        while ((pos = s.find(delimiter)) != std::string::npos) 
        {
            token = s.substr(0, pos);
            tokens.push_back(removeLeadingSpaces(token));
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(removeLeadingSpaces(s)); 
    }
    return tokens;
}

unsigned int mangu_joud(std::map<std::string, unsigned int> kott)
{
    unsigned int summa = 1;
    for (const auto& k : kott) 
    {
        summa *= k.second;   
    }
    return summa;
}


int main()
{
    std::string rida;
    std::vector<std::string> read;
    std::ifstream f("sis.txt");
    while(std::getline(f, rida)){
        if (rida.empty()){
            break;
        }
        read.push_back(rida);
    }
    f.close();

    unsigned int summa = 0; 
    std::map<std::string, unsigned int> kott = {
        {"red", 12}, 
        {"green", 13}, 
        {"blue", 14}
    };


    // 1.1

    for (std::string rida : read) 
    {
        std::vector<std::vector<std::map<std::string, unsigned int>>> tulemused = {};
        std::vector<std::string> tookenid = {};
        unsigned int id = 0;

        tookenid = splitString(rida, ";", ":");

        std::string num = std::move(tookenid[0]);
        tookenid.erase(tookenid.begin());
        num = num.substr(num.find(' '), num.length() - 1);
        id = std::stoi(num);


        for (std::string tooken : tookenid)
        {   
            std::vector<std::string> tulem = {};
            std::vector<std::map<std::string, unsigned int>> tulemus = {};
            std::vector<std::string> varvid = splitString(tooken, ",");
            for (std::string varv : varvid)
            {
                tulem = splitString(varv, " ");
                std::map<std::string, unsigned int> m = {{tulem[1], std::stoi(tulem[0])}};
                tulemus.push_back(m);
            }

            tulemused.push_back(tulemus);
        }
        tookenid.clear();

        
        bool sobib = true;
        for (const auto& tulemus : tulemused) 
        {
            for (const auto& t : tulemus) 
            {
                for (const auto& it : t) 
                {
                    if (it.second > kott[it.first])
                        sobib = false;
                }
            }
        }
        if (sobib)
        {   
            summa += id;
        }
    }

    std::cout << "1.1: " << summa << std::endl;


    // 1.2

    summa = 0; 
    for (std::string rida : read) 
    {
        std::map<std::string, unsigned int> min_kott = {
            {"red", 0}, 
            {"green", 0}, 
            {"blue", 0}
        };
        std::vector<std::vector<std::map<std::string, unsigned int>>> tulemused = {};
        std::vector<std::string> tookenid = {};
        unsigned int id = 0;

        tookenid = splitString(rida, ";", ":");

        std::string num = std::move(tookenid[0]);
        tookenid.erase(tookenid.begin());
        num = num.substr(num.find(' '), num.length() - 1);
        id = std::stoi(num);


        for (std::string tooken : tookenid)
        {   
            std::vector<std::string> tulem = {};
            std::vector<std::map<std::string, unsigned int>> tulemus = {};
            std::vector<std::string> varvid = splitString(tooken, ",");
            for (std::string varv : varvid)
            {
                tulem = splitString(varv, " ");
                std::map<std::string, unsigned int> m = {{tulem[1], std::stoi(tulem[0])}};
                tulemus.push_back(m);
            }

            tulemused.push_back(tulemus);
        }
        tookenid.clear();

        
        for (const auto& tulemus : tulemused) 
        {
            for (const auto& t : tulemus) 
            {
                for (const auto& it : t) 
                {
                    if (it.second > min_kott[it.first])
                        min_kott[it.first] = it.second;
                }
            }
        }
        summa += mangu_joud(min_kott);
    }  

    std::cout << "1.2: " << summa << std::endl;

    return 1;
}