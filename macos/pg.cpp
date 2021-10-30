#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <chrono>
using namespace std;
char uppercasec[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char lowercasec[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char specialc[7] = { '!', '#', '$', '%', '&', '*', '?' };
char numbersc[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
string read(string value) {
    ifstream input("pg_options.txt");
    int olength;
    string line = "", output = "";
    size_t pos;
    bool a = true;
    int i = 0;
    if (!input.is_open()) {
        cout << "pg_options.txt missing.";
        return "error";
    }
    while (getline(input, line)) {
        pos = line.find(value);
        if (pos != string::npos) {
            while (a == true) {
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

char grand(std::minstd_rand simple_rand, char x[]) {
    int n = 0;
    int p = x[n];
    while(p != '\0')
    {
        n++;
        p = x[n];
    }
    int i = simple_rand() % n;
    return x[i];
}

void generate() {
    minstd_rand simple_rand;
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int time = duration_cast<nanoseconds>(t1.time_since_epoch()).count();
    using namespace std;
    simple_rand.seed(time);
    int i1=0, digits = 0, upper = 0, lower = 0, special = 0, numbers = 0, l;
    digits = stoi(read("digits"));
    double ld[4] = {2.5, 2, 2, 1};
    string readitems[4] = { "include_upper_case", "include_lower_case", "include_special_characters", "include_numbers" };
    int amount[4] = { 0 };
    bool include[4] = { false };
    for (int i = 0; i < 3; i++) {
        if (read(readitems[i]) == "true") {
            include[i] = true;
            l = digits / ld[i];
            amount[i] = simple_rand() % l + 1;
            digits -= amount[i];
        }
    }
    if (read("include_numbers") == "true") {
        amount[3] = digits;
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (include[i] == true) {
                amount[i] += digits;
            }
        }
    }
    for (digits = stoi(read("digits")); digits > 0; digits--) {
        i1 = simple_rand() % 4;
        if (amount[i1] != 0) {
            char g[4] = { grand(simple_rand, uppercasec), grand(simple_rand, lowercasec),  grand(simple_rand, specialc), grand(simple_rand, numbersc) };
            cout << g[i1];
            amount[i1]--;
        }
        else {
            digits++;
        }
    }
    cout << endl;
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
}

string convert(string b) {
    string c = "";
    if (b == "y") {
        c = "true";
    }
    else if (b == "n") {
        c = "false";
    }
    return c;
}

void modifyvalue(string value, string newvalue) {
    ifstream oldfile;
    ofstream newfile;
    string line, content = "";
    int i = 0;
    newfile.open("pg_options_n.txt");
    oldfile.open("pg_options.txt");
    if (!oldfile.is_open()) {
        cout << "pg_options.txt missing.\n";
        return;
    }
    else {
        while (getline(oldfile, line)) {
            if (i < findposition(value)) {
                content += line += "\n";
            }
            else {
                break;
            }
            i++;
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
    string iu = "", il = "", is = "", in = "", digits = "a";
    while (iu != "y" && iu != "n") {
        cout << "Include uppercase characters? (y|n) ";
        cin >> iu;
    }
    while (il != "y" && il != "n") {
        cout << "Include lowercase characters? (y|n) ";
        cin >> il;
    }
    while (is != "y" && is != "n") {
        cout << "Include special characters? (y|n) ";
        cin >> is;
    }
    while (in != "y" && in != "n") {
        cout << "Include numbers? (y|n) ";
        cin >> in;
    }
    while (!checkint(digits)) {
        cout << "How many digits? ";
        cin >> digits;
    }
    iu = convert(iu);
    il = convert(il);
    is = convert(is);
    in = convert(in);
    modifyvalue("include_upper_case", iu);
    modifyvalue("include_lower_case", il);
    modifyvalue("include_special_characters", is);
    modifyvalue("include_numbers", in);
    modifyvalue("digits", digits);
}

void init() {
    ifstream file;
    file.open("pg_options.txt");
    if (file.is_open()) {
        file.close();
        return;
    }
    else {
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
        core();
    }
    else if (input == "o") {
        options();
        core();
    }
    else {
        cout << "input error.\n";
        core();
    }
}

int main()
{
    cout << "g for generating passwords, o for options.\nPassword is copied to clipboard every time you generate.\n";
    init();
    core();
}
