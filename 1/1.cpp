#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>

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


    // 1.1
    std::vector<int> numbrid;
    int summa = 0;
    for (std::string rida : read)
    {
        for (char ch : rida)
            if (isdigit(ch)){
                numbrid.push_back(std::stoi(&ch));}
        // for (int n : numbrid) std::cout << rida << " " << n << std::endl;
        // std::cout << numbrid[0] << " " << numbrid[numbrid.size()-1] << std::endl;
        summa += numbrid[0] * 10 + numbrid[numbrid.size()-1];
        numbrid.clear();
    }
    std::cout << "1.1: " << summa << std::endl;


    // 1.2
    std::set<std::string> nums_set = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    std::set<std::string> nums_rset = {"orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    std::map<std::string, int> nums_map;
    nums_map["zero"]  = 0;
    nums_map["one"]   = 1;
    nums_map["two"]   = 2;
    nums_map["three"] = 3;
    nums_map["four"]  = 4;
    nums_map["five"]  = 5;
    nums_map["six"]   = 6;
    nums_map["seven"] = 7;
    nums_map["eight"] = 8;
    nums_map["nine"]  = 9;
    nums_map["0"]     = 0;
    nums_map["1"]     = 1;
    nums_map["2"]     = 2;
    nums_map["3"]     = 3;
    nums_map["4"]     = 4;
    nums_map["5"]     = 5;
    nums_map["6"]     = 6;
    nums_map["7"]     = 7;
    nums_map["8"]     = 8;
    nums_map["9"]     = 9;

    summa = 0;
    for (std::string rida : read)
    {
        std::string str = rida;
        std::string rstr = rida;
        std::reverse(rstr.begin(), rstr.end());
        int num_min;
        size_t min = 1000;
        int num_max;
        size_t max = 1000;
        for (std::string num : nums_set)
        {
            size_t uus = str.find(num);
            if (uus != std::string::npos && uus < min)
            {
                min = uus;
                num_min = nums_map[num];
            }
            // std::cout << "min: " << min << " " << num << " " << num.length() << std::endl;
        }
        for (std::string rnum : nums_rset)
        {
            size_t ruus = rstr.find(rnum);
            if (ruus != std::string::npos && ruus < max)
            {
                max = ruus;
                std::reverse(rnum.begin(), rnum.end());
                num_max = nums_map[rnum];
            }
            // std::reverse(rnum.begin(), rnum.end());
            // std::cout << "max: " << rida.length() - 1 - max << " " << rnum << " " << rnum.length() << " " << num_max << std::endl;
        }

        // std::cout << num_min << " " << num_max << std::endl;
        summa += num_min * 10 + num_max;
        numbrid.clear();
    }


    std::cout << "1.2: " << summa << std::endl;

    return 1;
}