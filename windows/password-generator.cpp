#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <Windows.h>
using namespace std;
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
    int olength;
    string line = "", output = "";
    int i = 0;
    if (!input.is_open()) {
        cout << "pg_options.txt missing.";
        return "error";
    }
    while (getline(input, line)) {
        size_t pos = line.find(value);
        if (pos != string::npos) {
            while (true) {
                if (line[i] == '=') {
                    i++;
                    break;
                }
                i++;
            }
            olength = line.length() - value.length() - 1;
            for (int i2 = 0; i2 < olength; i2++) {
                output += line[i];
                i++;
            }
        }
    }
    return output;
}

bool checkint(string word) {
    bool has_only_digits = (word.find_first_not_of("0123456789") == string::npos);
    return has_only_digits;
}

char grand(std::minstd_rand simple_rand, int size, char x[]) {
    int i = simple_rand() % size;
    return x[i];
}

void generate() {
    char uppercasec[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' }, lowercasec[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }, specialc[7] = { '!', '#', '$', '%', '&', '*', '?' }, numbersc[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    minstd_rand simple_rand;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int time = std::chrono::duration_cast<std::chrono::nanoseconds>(t1.time_since_epoch()).count(), digits = 0, upper = 0, lower = 0, special = 0, numbers = 0, l, amount[4] = { 0 };
    simple_rand.seed(time);
    digits = stoi(read("digits"));
    double ld[3] = {2, 1.5, 2};
    string readitems[4] = { "include_upper_case", "include_lower_case", "include_special_characters", "include_numbers" }, output = "";
    bool include[4] = { false };
    for (int i = 0; i < 4; i++) {
        if (read(readitems[i]) == "true") {
            include[i] = true;
            amount[i] = 1;
            digits--;
        }
    }
    int addamount;
    for (int i = 0; i < 3; i++) {
        if (include[i]) {
            l = digits / ld[i];
            if (!(l < 1)) {
                addamount = simple_rand() % l;
                amount[i] += addamount;
                digits -= addamount;
            }
        }
    }
    if (include[3]) {
        amount[3] += digits;
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (include[i] == true) {
                amount[i] += digits;
            }
        }
    }
    for (digits = stoi(read("digits")); digits > 0; digits--) {
        int i1 = simple_rand() % 4;
        if (amount[i1] != 0) {
            char g[4] = { grand(simple_rand, 26, uppercasec), grand(simple_rand, 26, lowercasec),  grand(simple_rand, 7, specialc), grand(simple_rand, 10, numbersc) };
            cout << g[i1];
            output += g[i1];
            amount[i1]--;
        }
        else {
            digits++;
        }
    }
    cout << endl;
    toClipboard(output);
}

int findposition(string value) {
    ifstream file("pg_options.txt");
    int i = 0;
    string line;
    while (getline(file, line)) {
        size_t found = line.find(value);
        if (found != string::npos) {
            return i;
        }
        i++;
    }
    return i;
}

string convert(const string b) {
    string c = "false";
    if (b == "y") {
        c = "true";
    }
    return c;
}

void modifyvalue(const string value, const string newvalue) {
    ifstream oldfile;
    ofstream newfile;
    string line, content = "";
    newfile.open("pg_options_n.txt");
    oldfile.open("pg_options.txt");
    if (!oldfile.is_open()) {
        cout << "pg_options.txt missing.\n";
        return;
    }
    else {
        int i = 0;
        getline(oldfile, line);
        for (i; i < findposition(value); i++, getline(oldfile, line)) {
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
    const string out[4] = {" uppercase characters", " lowercase characters", " special characters", " numbers"}, values[5] = {"include_upper_case", "include_lower_case", "include_special_characters", "include_numbers", "digits"};
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
        if (options[i] == "y") {
            count += 1;
        }
    }
    if (count > stoi(options[4]) || stoi(options[4]) < 1) {
        cout << "Configuration invalid.\n";
    }
    else {
        for (int i = 0; i < 4; i++) {
            options[i] = convert(options[i]);
            modifyvalue(values[i], options[i]);
        }
        modifyvalue(values[4], options[4]);
    }
}

void init() {
    ifstream file;
    file.open("pg_options.txt");
    if (!file.is_open()) {
        ofstream fs;
        fs.open("pg_options.txt");
        fs << "#DO NOT MODIFY UNLESS YOU KNOW WHAT YOU ARE DOING\ninclude_special_characters=true\ninclude_upper_case=true\ninclude_lower_case=true\ninclude_numbers=true\ndigits=10";
        fs.close();
    }
}

void core() {
    string input;    
    cout << "(g|o): ";
    cin >> input;
    if (input == "g") {
        generate();
    }
    else if (input == "o") {
        options();
    }
    else {
        cout << "input error.\n";
    }
    core();
}

int main()
{
    cout << "g for generating passwords, o for options.\nPassword is copied to clipboard every time you generate.\n";
    init();
    core();
}
