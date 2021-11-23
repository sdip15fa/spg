#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include <map>
#include <Windows.h>
using namespace std;

map<string, bool> include;
int digits;
char o[26];
string items[4] = { "upper", "lower", "special", "numbers" };

void print(string text) {
    cout << text;
}

char * lists(int x) {
    int pos[5] = {0, 26, 52, 59, 69}; 
    char lists[69] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '#', '$', '%', '&', '*', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    for (int i = 0; i < pos[x+1] - pos[x]; i++) {
        o[i] = lists[pos[x] + i];
    }
    return o;
}

void toClipboard(const std::string& s) {
    OpenClipboard(0);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

string read(string value) {
    ifstream input("pg_options.txt");
    string line, output = "";
    int i = 0;
    if (input.is_open()) {
        while (getline(input, line)) {
            if (line.find(value) != string::npos) {
                for (i; line[i] != '='; i++) {}
                i++;
                for (int i2 = 0; i2 < line.length() - value.length() - 1; i2++, i++) {
                    output += line[i];
                }
            }
        }
        return output;
    }
    cout << "pg_options.txt missing.";
}

bool checkint(string word) {
    return word.find_first_not_of("0123456789") == string::npos;
}

char grand(std::minstd_rand simple_rand, int size, char x[]) {
    return x[simple_rand() % size];
}

void generate() {
    minstd_rand simple_rand;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int addamount, time = std::chrono::duration_cast<std::chrono::nanoseconds>(t1.time_since_epoch()).count(), d = digits, upper = 0, lower = 0, special = 0, numbers = 0, l, amount[4] = { 0 }, size[4] = {26, 26, 7, 10};
    simple_rand.seed(time);
    string output = "";
    double ld[3] = {2, 1.5, 2};
    for (int i = 0; i < 4; i++) {
        if (include[items[i]]) {
            amount[i] = 1;
            d--;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (include[items[i]]) {
            l = d / ld[i];
            if (l >= 1) {
                addamount = simple_rand() % l;
                amount[i] += addamount;
                d -= addamount;
            }
        }
    }
    if (include[items[3]]) {
        amount[3] += d;
    }
    else {
        for (int i = 0; i < 3; i++) {
            include[items[i]] ? amount[i] += d : d;
        }
    }
    for (int d = digits; d > 0; d--) {
        int i1 = simple_rand() % 4;
        if (amount[i1] >= 1) {
            char o = grand(simple_rand, size[i1], lists(i1));
            cout << o;
            output += o;
            amount[i1]--;
        }
        else {
            d++;
        }
    }
    cout << endl;
    toClipboard(output);
}

int findposition(string value) {
    ifstream file("pg_options.txt");
    int i = 0;
    string line;
    for (getline(file, line); line.find(value) == string::npos; getline(file, line), i++) {}
    return i;
}

inline string convert(const string b) {
    return b == "y" ? "true" : "false";
}

void modifyvalue(const string value, const string newvalue) {
    ifstream oldfile;
    ofstream newfile;
    string line, content = "";
    newfile.open("pg_options_n.txt");
    oldfile.open("pg_options.txt");
    if (!oldfile.is_open()) {
        cout << "pg_options.txt missing.\n";
    }
    else {
        int i = 0;
        for (getline(oldfile, line); i < findposition(value); i++, getline(oldfile, line)) {
            content += line += "\n";
        }
        i++;
        content += value + "=" + newvalue + "\n";
        while (getline(oldfile, line)) {
            if (i > findposition(value)) {
                content += line += "\n";
            }
            i++;
        }
        oldfile.close();
        newfile << content;
        newfile.close();
        remove("pg_options.txt");
        rename("pg_options_n.txt", "pg_options.txt");
    }
}

void options() {
    string options[5] = { "" };
    const string out[4] = {" uppercase characters", " lowercase characters", " special characters", " numbers"}, values[5] = {"upper", "lower", "special", "numbers", "digits"};
    for (int i = 0; i < 4; i++) {
        while (options[i] != "y" && options[i] != "n") {
            cout << "Include" + out[i] + "? (y|n) ";
            cin >> options[i];
        }
    }
    options[4] = "N";
    while (!checkint(options[4])) {
        cout << "How many digits? ";
        cin >> options[4];
    }
    int count = 0;
    for (int i = 0; i < 4; i++) {
        options[i] == "y" ? count++ : count;
    }
    if (count > stoi(options[4]) || stoi(options[4]) < 1) {
        cout << "Configuration invalid.\n";
    }
    else {
        for (int i = 0; i < 5; i++) {
            i < 4 ? include[items[i]] = options[i] == "y": digits = stoi(options[i]);
            modifyvalue(values[i], i < 4 ? convert(options[i]) : options[i]);
        }
    }
}

void init() {
    ifstream file("pg_options.txt");
    if (!file.is_open()) {
        ofstream fs("pg_options.txt");
        fs << "#DO NOT MODIFY UNLESS YOU KNOW WHAT YOU ARE DOING\nspecial=true\nupper=true\nlower=true\nnumbers=true\ndigits=10";
    }
    for (int i = 0; i < 4; i++) {
        include[items[i]] = read(items[i]) == "true";
    }
    digits = stoi(read("digits"));
}

void core() {
    string input;
    cout << "(g|o): ";
    cin >> input;
    input == "g" ? generate() : input == "o" ? options() : print("Input error.\n");
    core();
}

int main()
{
    cout << "g for generating passwords, o for options.\nPassword is copied to clipboard every time you generate.\n";
    init();
    core();
}