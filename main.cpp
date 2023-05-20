


#include <vector>
#include <map>
#include <set>


#include <fstream>
#include <iostream>
#include <sstream>
//#include <locale>
#include <iomanip>

#include <algorithm>
#include <cstring> // strlen()

using std::cout;
using std::endl;

struct wlcount { // word, line count
    int amount;
    std::set<int> lines;
};

void removeChars (std::string &str, char* to_remove)
{
    for (int i = 0; i < strlen(to_remove) ; ++i){
        str.erase(remove(str.begin(), str.end(), to_remove[i]), str.end());
    }
}


int main()
{
    char to_remove[] = "(){}<>[]*$_-,;?!'1234567890°\"%\\'�≥—′″";

    std::map<std::string, wlcount> wmap;

    std::stringstream buffer;
    std::ifstream fin ("input_file.txt");
    buffer << fin.rdbuf();
    fin.close();

    std::string line;
    int line_count = 0;

    // Going through all the lines in the file
    while (getline(buffer, line)){
        line_count++;

        std::string word;
        std::stringstream ss (line);

        // Going through all the words in the line
        while (ss >> word){
            
            // remove random bits, but not '.'
            removeChars(word, to_remove);

            // remove '.' if it is the last or first char in string (that means it is not a link)
            while (word[word.length()-1] == '.'){word.erase(word.length()-1);}
            while (word[0] == '.'){word.erase(0);}

            // check if word is a link. If it is output it to console.
            if (word.find(".") != std::string::npos || word.find("www.") != std::string::npos || word.find("https://") != std::string::npos){
                cout << word << endl;
            }

            char rm[] = ":/";
            removeChars(word, rm);

            if (word.empty()){continue;}


            // add the word if such word was not added before
            if (wmap.count(word) > 0){
                // There is word already in the map
                wmap[word].amount++;
                wmap[word].lines.insert(line_count);
            }
            else {
                // There is no word in the map
                wmap[word] = {1, {}};
                wmap[word].lines.insert(line_count);
            }            
        }
    }

    // Here all the words from the files have been read and maped in wmap
    std::ofstream fout("output_file.txt");
    std::multimap<int, std::string, std::greater<int>> sortedMap;

    for (const auto& w : wmap){sortedMap.insert({w.second.amount, w.first});}

    fout << std::left;

    for (const auto& w : sortedMap){
        if (wmap[w.second].lines.size() > 1){
            fout << std::setw(15) << w.second << " apears " << w.first << " times." << " Lines  ";
            
            for (const auto& l : wmap[w.second].lines){fout << l << " ";}
            fout << endl;
        }
    }
    fout.close();

    return 0;
}