#include <iostream>
#include <regex>
#include <string>
#include <map>

using namespace std;

void differentiate(map<int,int> &m);
void print_manyChlen(map<int,int> &m);
void print_manyChlenNorm(map<int,int> &m);
void fill_map_from_string(map<int,int> &m, string &input);


void fill_map_from_string(map<int,int> &m, string &input)
{
    /**          (              1               ) (      5     ) */
    /**           (  2  ) (  3 )          (  4 )    (  6 ) (  7 )*/
	regex myreg("((\\+|-)?(\\d*)?\\*?x\\^?(\\d*))|((\\+|-)?(\\d+))");
	cmatch cm;

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

void print_manyChlenNorm(map<int,int> &m)
{
    bool notfirst = false;
    for(auto it = m.rbegin(); it != m.rend(); ++it)
    {
//        cout << it->second << "*x^" << it->first;
//        continue;
        int st = it->first;
        int vl = it->second;
        if (!notfirst)
        {
            notfirst = true;
        }
        else{
            if (vl > 0)
                cout << "+";
            else if ((vl == -1) && (st != 0))
                cout << "-";
        }

        if (vl == 0)
            continue;
        else if (st == 0)
            cout << vl;
        else if (((vl == 1) || (vl == -1)) && (st == 1))
            cout << "x";
        else if (st == 1)
            cout << vl << "*x";
        else if ((vl == 1) || (vl == -1))
            cout << "x^" << st;
        else
            cout << vl << "*x^" << st;
    }
    cout << endl;
}

void differentiate(map<int,int> &m)
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

int main(void)
{
	string input;
	map<int, int> m;

	while (1)
    {
        cin >> input;

        fill_map_from_string(m, input);

        print_manyChlenNorm(m);
        differentiate(m);
        print_manyChlenNorm(m);

        cout << endl << endl;
        m.clear();
    }

}




void print_manyChlen(map<int,int> &m)
{
    for(auto it = m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << " " << it->second << endl;
    }
}






