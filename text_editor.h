#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <map>
#include <set>

using std::istream;
using std::string;
using std::list;
using std::vector;
using std::map;
using std::set;
using std::streambuf;

typedef list<string> text;
typedef text::iterator text_iterator;

static const size_t SIZE = 40;

class TextEditor {
public:
    TextEditor();
    virtual ~TextEditor();

    void start();

    void testUI();

    void readUserInput(istream& in);

    void showText();
    void editQuery();
    void insertLine(string& request);
    void appendLine();
    void moveLine(string& request);
    void deleteLine(string& request);
    void findWord(string& request);
    void sort();
    void count_words();
    map<string, int> help_count(set<string>&set_, list<string>& words);

    unsigned long size();

private:
    text container_;

    struct membuf : streambuf
    {
        membuf(char* begin, char* end) {
            this->setg(begin, begin, end);
        }
    };
};

// helper methods
namespace hlib {
    void fill_map(list<string>& container, map<int, string>& map_, string& word);

    template<typename K, typename V> void print_map(map<K, V>& map_);
    
    vector<int> parseRequest(string& request);

    std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
}

#endif