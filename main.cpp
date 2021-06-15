#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void read(vector <string> &url, map <string, pair <set<int>, int>>& words)
{
    string text, word;
    int counter = 0;
    ifstream in;
    in.open("duomenys.txt");
    stringstream inS;
    inS << in.rdbuf();
    in.close();
    
    while(getline(inS, text))
    {
        counter++;
        while (inS >> word)
        {
            if(word.find("http://") != string::npos ||  word.find("www.") != string::npos)
                url.push_back(word);
            else
            {
                word.erase(remove_if(word.begin(), word.end(), [](char c) {return !isalpha(c);}), word.end());
                if(!word.empty())
                {
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    words[word].first.insert(counter);
                    words[word].second++;
                }
            }
        }
    }
}
void print(vector <string> url, map <string, pair <set<int>, int>> words)
{   
    ofstream out ("rez.txt");
    out << "Cross-reference lentele: " << endl;
    for(auto& word : words)
    {
        if (word.second.second > 1)
        {
            out << "Word: " << word.first << setw(20) << " Count: " << word.second.second << setw(20) << " Lines: ";
            for(auto line_number : word.second.first)
                    out << line_number << " ";
            out << endl;
        }
    }
    out.close();

    cout << "URL's:" << endl;
    for (int i = 0; i < url.size(); i ++) 
        cout << url[i] << endl;
}
int main()
{
    vector <string> url;
    map<string, pair <set<int>, int>>words;    
    read(url, words);
    print(url, words);
    return 0;
}
