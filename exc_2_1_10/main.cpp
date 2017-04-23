#include <iostream>
#include <regex>
#include <string>
#include <map>

using namespace std;

int main()
{
	/**
     * 1) x
	 * 2) 1*x
     * 3) 1*x^2
     * 4) 1
	 */

	string input;
	string input2 = "x^1+2*x+3+4*x^5";
	cout << input2 << endl;
//	regex integer("(\\+{0,2}|-{0,2})[[:d:]]+");
//	regex myreg("(+|-)?    [[:d:]]*    x?    (\^[[:d]])?    ");
//	regex myreg("(+|-)?    [[:d:]]*  \*?   (x  (\^[[:d]]+)*  )?    ");
//	regex myreg("(\\+|-)?  [[:d:]]* \\*?  (x(\\^[[:d]]+)*)?    ");
//	regex myreg("(\\+|-)?[[:d:]]*\\*?(x(\\^[[:d:]]+)*)?");
//	regex myreg("(\\+|-)?\\d*\\*?(x(\\^\\d+)*)?");
//	regex myreg("(\\+|-)?     \\d*\\*?    (x    (\\^\\d+)*)?");
//	regex myreg("(\\+|-)?     (\\d+   |    (\\d+\\*)?    (x)  (\\^\\d+)?)");
//	regex myreg("((\\+|-)?    (\\d+   |   ( (\\d+\\*)?   x    (\\^\\d+)?))     )");
//	regex myreg("((\\+|-)?(\\d+|((\\d+\\*)?x(\\^\\d+)?)))");                                    // OK
//	regex myreg("( ((\\+|-)?\\d+)    |     ((\\+|-)?   (\\d+\\*)?x(\\^\\d+)?)  )");
//	regex myreg("(((\\+|-)?\\d+)|((\\+|-)?(\\d+\\*)?x(\\^\\d+)?))");
	/*
	regex myreg("((\\+|-)?\\d{1,})"
                "|"
                "((\\+|-)?"
                "(\\d+\\*)?"
                "x"
                "(\\^\\d+)?)");
	regex myreg("((\\+|-)?\\d+)"
                "|"
                "((\\+|-)?"         // +
                "(\\d*)?"           // 12
                "\\*"               // *
                "x"                 // x
                "\\^"               // ^
                "(\\d*))");         // 10           // GREAT
	regex myreg(
                "((\\+|-)?"         // +
                "(\\d*)?"           // 12
                "\\*?"               // *
                "x"                 // x
                "\\^"               // ^
                "(\\d*))"
                "|"
                "((\\+|-)?\\d+)");         // 10
                */
//	regex myreg("((\\+|-)?(\\d*)?\\*?x\\^(\\d*))|((\\+|-)?\\d+)");

    /**          (              1               ) (      5     ) */
    /**           (  2  ) (  3 )          (  4 )    (  6 ) (  7 )*/
	regex myreg("((\\+|-)?(\\d*)?\\*?x\\^?(\\d*))|((\\+|-)?(\\d+))");
//	regex myreg("((\\+|-)?  (\\d*)?  \\*?    x   \\^?  (\\d*))   |    ((\\+|-)?\\d+)");
	cmatch cm;

	map<int, int> m;
	//As long as the input is correct ask for another number
	while(true)
	{
		cout<<"Give me an integer!"<<endl;
		cin>>input;
		if(!cin) break;
		//Exit when the user inputs q
		if(input=="q")
			break;

		cout << "==============================" << endl;
#if 1
        for (int i = 0; regex_search(input2.c_str(), cm, myreg); ++i, input2 = cm.suffix().str())
        {
            cout << i << ":" << cm[0];
            for (unsigned i = 1; i < cm.size(); ++i )
                cout << "  | " << cm[i];
            cout << endl;
            cout << endl;
            cout << endl;
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

            cout << "st=" << st << " val=" << vl << endl;
            cout << endl;
            cout << endl;
            cout << endl;
        }

/*
        for(map<string, pair<string,string> >::const_iterator it = m.begin();
            it != m.end(); ++it)
        {
            std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
        }
*/
        for(auto it = m.begin(); it != m.end(); ++it)
        {
            std::cout << it->first << " " << it->second << endl;
        }


		break;
#elif 1
        string s = input;
        regex e = myreg;
        while (regex_search (s.c_str(),cm,e))
        {
            for (auto x:cm) cout << x << " ";
            cout << endl;
            s = cm.suffix().str();
        }
#elif 1
//        string::const_iterator searchStart( input2.cbegin() );
        string::iterator searchStart( input2.begin() );
		if( regex_search(searchStart, input2.end(), cm, myreg) )
        {
            cout << cm[0] << endl;
            cout << "-------------------------------" << endl;
            searchStart += cm.position() + cm.length();
        }
#else
        copy( sregex_token_iterator(input.begin(), input.end(), myreg, -1),
            sregex_token_iterator(),
            ostream_iterator<string>(cout, "\n"));
#endif

		cout << "==============================" << endl;
	}
}
/*
*/


