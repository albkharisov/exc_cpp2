#include <iostream>
#include <regex>
#include <string>
#include <map>

//using namespace std;

void print_manyChlen(std::map<int,int> &m);
void print_manyChlenNorm(std::map<int,int> &m);

std::string derivative(std::string polynomial);

void print_manyChlenNorm(std::map<int,int> &m)
{
    bool notfirst = false;
    std::stringstream ss;
    for(auto it = m.rbegin(); it != m.rend(); ++it)
    {
        int st = it->first;
        int vl = it->second;
        if (!notfirst)
        {
            notfirst = true;
        }
        else{
            if (vl > 0)
                ss << "+";
            else if ((vl == -1) && (st != 0))
                ss << "-";
        }

        if (vl == 0)
            continue;
        else if (st == 0)
            ss << vl;
        else if (((vl == 1) || (vl == -1)) && (st == 1))
            ss << "x";
        else if (st == 1)
            ss << vl << "*x";
        else if ((vl == 1) || (vl == -1))
            ss << "x^" << st;
        else
            ss << vl << "*x^" << st;
    }
    ss << std::endl;

    std::cout << ss.str();
}

void print_manyChlen(std::map<int,int> &m)
{
    for(auto it = m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

int main(void)
{
	std::string input;
	std::map<int, int> m;

	while (1)
    {
        std::cin >> input;

        std::string output = derivative(input);

        std::cout << output;
        std::cout << std::endl << std::endl;
        m.clear();
    }

}


std::string convertToString(std::map<int,int> &m);
void differentiate(std::map<int,int> &m);
void fill_map_from_string(std::map<int,int> &m, std::string &input);

std::string derivative(std::string polynomial)
{
    std::map<int,int> m;
    m.clear();
    fill_map_from_string(m, polynomial);
    differentiate(m);
    return convertToString(m);
}

void fill_map_from_string(std::map<int,int> &m, std::string &input)
{
    /**          (              1               ) (      5     ) */
    /**           (  2  ) (  3 )          (  4 )    (  6 ) (  7 )*/
	std::regex myreg("((\\+|-)?(\\d*)?\\*?x\\^?(\\d*))|((\\+|-)?(\\d+))");
	std::cmatch cm;

    for (int i = 0; regex_search(input.c_str(), cm, myreg); ++i, input = cm.suffix().str())
    {
        int st = 99;
        int vl = 99;
        if (cm[1] != "")
        {
            st = (cm[4] == "") ? 1 : atoi(cm[4].str().c_str());
            vl = (cm[3] == "") ? 1 : atoi(cm[3].str().c_str());

            if (cm[2] == "-")
                vl = -vl;

            m[st] += vl;
        }
        else{
            st = 0;
            vl = atoi(cm[7].str().c_str());
            if (cm[6] == "-")
                vl = -vl;

            m[st] += vl;
        }
    }

}

void differentiate(std::map<int,int> &m)
{
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        int st = it->first;
        int vl = it->second;
        m.erase(st);
        if (st == 0)
            continue;
        vl *= st;
        --st;
        m[st] += vl;
    }
}

std::string convertToString(std::map<int,int> &m)
{
    bool notfirst = false;
    std::stringstream ss;
    for(auto it = m.rbegin(); it != m.rend(); ++it)
    {
        int st = it->first;
        int vl = it->second;
        if (!notfirst)
        {
            notfirst = true;
        }
        else{
            if (vl > 0)
                ss << "+";
            else if ((vl == -1) && (st != 0))
                ss << "-";
        }

        if (vl == 0)
            continue;
        else if (st == 0)
            ss << vl;
        else if (((vl == 1) || (vl == -1)) && (st == 1))
            ss << "x";
        else if (st == 1)
            ss << vl << "*x";
        else if ((vl == 1) || (vl == -1))
            ss << "x^" << st;
        else
            ss << vl << "*x^" << st;
    }
    ss << std::endl;

    return ss.str();
}

