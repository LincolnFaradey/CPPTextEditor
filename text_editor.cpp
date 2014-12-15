#include "text_editor.h"

using namespace hlib;
using std::cout;
using std::endl;
using std::cin;
using std::stringstream;



char buffer[] = "Four score and seven years ago our fathers brought forth on this\n"
        "continent a new nation , conceived in liberty , and dedicated to the proposition that all\n"
        "men are created equal .\n"
        "Now we are engaged in a great civil war , testing whether that nation , or any nation so\n"
        "conceived and so dedicated , can long endure . We are met on a great battlefield of\n"
        "that war .  We have come to dedicate a portion of that field , as a final resting place for\n"
        "those who here gave their lives that that nation might live . It is altogether fitting and\n"
        "proper that we should do this .\n"
        "But , in a larger sense , we can not dedicate , we can not consecrate , we can not\n"
        "hallow this ground . The brave men , living and dead , who struggled here , have\n"
        "consecrated it , far above our poor power to add or detract . The world will little note ,\n"
        "nor long remember what we say here , but it can never forget what they did here . It is\n"
        "for us the living , rather , to be dedicated here to the unfinished work which they who\n"
        "fought here have thus far so nobly advanced . It is rather for us to be here dedicated\n"
        "to the great task remaining before us — that from these honored dead we take \n"
        "increased devotion to that cause for which they gave the last full measure of devotion\n"
        "— that we here highly resolve that these dead shall not have died in vain — that this\n"
        "nation , under God , shall have a new birth of freedom — and that government of the\n"
        "people , by the people , for the people , shall not perish from the earth .";

TextEditor::TextEditor() : container_() {
}

TextEditor::~TextEditor() {
    cout << "Distructor has been invoked\n";
}

void TextEditor::start() {
    testUI();
    readUserInput(cin);
}

void TextEditor::testUI() {
    membuf sbuf(buffer, buffer + sizeof(buffer));
    istream in(&sbuf);
    string line;
    while (getline(in, line)) {
        container_.push_back(line);
    }
}

void TextEditor::readUserInput(istream& in) {
    cout << "****************************** Text Editor *************************************" << endl;
    string tmp;
    for (int i = 0; i < SIZE; ++i) {
        getline(in, tmp);
        if (tmp.length() > 0 && tmp.at(0) == '#') editQuery();
        if (tmp.at(0) != '#') container_.push_back(tmp);
    }
}

void TextEditor::showText() {
    cout << "****************************** PLAIN TEXT **************************************" << endl;
    list<string>::iterator it;
    for (it = container_.begin(); it != container_.end(); ++it) {
        cout << *it << endl;
    }

    cout << "*******************************" << size() << "***********************************" << endl;
}

void TextEditor::editQuery() {
    showText();
    string request;
    cout << "*********************************** EDITOR MODE ***********************************" << endl
            << "input 'I' and 'j' for insert a new text line in line 'j', where j is number\n"
            << "input 'A' for append a new text line\n"
            << "input 'M', 'j' and 'k' for move line j to line k, where j and k are numbers \n"
            << "input 'D' and 'j' for delete line j, where j is number\n"
            << "input 'F' and 'word' for search all lines that contain the 'word'\n"
            << "input 'S' for sort\n"
            << "input 'C' for display amout of words\n"
            << "input 'Q' for quit from the Editor mode\n";

    getline(cin, request);
    if (request.length() == 0) return;
    switch (request.at(0)) {
        case 'I':
            insertLine(request);
            break;
        case 'A':
            appendLine();
            break;
        case 'M':
            moveLine(request);
            break;
        case 'D':
            deleteLine(request);
            break;
        case 'F':
            findWord(request);
            break;
        case 'S':
            sort();
            break;
        case 'C':
            count_words();
            break;
        case 'Q':
            break;
        default:
            break;
    }
    if (request.length() > 0 && request.at(0) != 'Q')  editQuery();
    cout << "********************************************************************************" << endl;

}

void TextEditor::insertLine(string& request) {
    string tmp;
    cout << "Input new string:\n";
    getline(cin, tmp);
    vector<int>  req_arr = parseRequest(request);
    text_iterator it = container_.begin();
    advance(it, req_arr[0]);
    container_.insert(it, tmp);
}

void  TextEditor::appendLine() {
    string tmp;
    cout << "Input new string:\n";
    getline(cin, tmp);
    container_.push_back(tmp);
}

void TextEditor::moveLine(string& request) {
    vector<int> req_vec = parseRequest(request);
    text_iterator it = container_.begin();
    advance(it, req_vec[0]);
    auto tmp = *it;
    container_.erase(it);
    advance(it, req_vec[1]+1);
    container_.insert(it, tmp);
}

void TextEditor::deleteLine(string& request) {
    vector<int> req_vec = parseRequest(request);
    text_iterator it = container_.begin();
    advance(it, req_vec[0]);
    container_.erase(it);
}

void TextEditor::findWord(string& request) {
    map<int, string> found;
    vector<string> req_vec;
    split(request, ' ', req_vec);
    string word = req_vec[1];
    fill_map(container_, found, word);
    print_map(found);
}

void TextEditor::sort() {
    container_.sort();
    cout << "************************************ SORTED ************************************" << endl;
    showText();
    cout << "********************************************************************************" << endl;
}

void TextEditor::count_words() {
    set<string> tmp;
    list<string> all_words;
    text_iterator it;
    for (it = container_.begin(); it != container_.end(); ++it) {
        vector<string> t_vec;
        split(*it, ' ', t_vec);
        vector<string>::iterator iter;
        for (iter = t_vec.begin(); iter != t_vec.end(); ++iter) {
            tmp.insert(*iter);
            all_words.push_back(*iter);
        }
    }

    map<string, int> amount_of_words = help_count(tmp, all_words);
    hlib::print2_map(amount_of_words);
}

map<string, int> TextEditor::help_count(set<string>& set_, list<string>& words) {
    map<string, int> tmp;
    set<string>::iterator set_it;
    list<string>::iterator list_it;
    int counter = 0;

    for (set_it = set_.begin(); set_it != set_.end(); ++set_it) {
        for (list_it = words.begin(); list_it != words.end(); ++list_it) {
            if (*set_it == *list_it) ++counter;
        }
        tmp[*set_it] = counter;
        counter = 0;
    }

    return tmp;
}

unsigned long TextEditor::size() {
    return container_.size();
}

namespace hlib {
    void fill_map(text& container, map<int, string>& map_, string& word) {
        text_iterator it;
        int counter = 0;
        for (it = container.begin(); it != container.end(); ++it) {
            string tmp = *it;
            if (tmp.find(word) != string::npos) {
                map_[counter] = tmp;
            }
            ++counter;
        }
    }

    void print_map(map<int, string>& map_) {
        map<int, string>::iterator map_it;
        for (map_it = map_.begin(); map_it != map_.end(); ++map_it) {
            cout << "Line #" << map_it->first << " : Prase - " << map_it->second << endl;
        }
    }

    void print2_map(map<string, int>& map_) {
        map<string, int>::iterator map_it;
        for (map_it = map_.begin(); map_it != map_.end(); ++map_it) {
            cout << map_it->first << " | #" << map_it->second << endl;
        }
    }

    vector<int> parseRequest(string& request) {
        vector<int> vec;
        vector<string> str_vec;
        split(request, ' ', str_vec);
        vector<string>::iterator it;
        it = str_vec.begin();
        for (++it; it != str_vec.end(); ++it) {
            int j = stoi(*it);
            vec.push_back(j);
        }
        return vec;
    }

    vector<string>& split(const string &s, char delim, vector<std::string> &elems) {
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }
}