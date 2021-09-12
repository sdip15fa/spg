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
                else {
                    i++;
                }
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

char randupper(std::minstd_rand simple_rand) {
    char uppercase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int i = simple_rand() % 26;
    return uppercase[i];
}

char randlower(std::minstd_rand simple_rand) {
    char lowercase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int i = simple_rand() % 26;
    return lowercase[i];
}

char randspecial(std::minstd_rand simple_rand) {
    char special[7] = { '!', '#', '$', '%', '&', '*', '?' };
    int i = simple_rand() % 7;
    return special[i];
}

char randnumbers(std::minstd_rand simple_rand) {
    char numbers[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    int i = simple_rand() % 10;
    return numbers[i];
}

void generate() {
    minstd_rand simple_rand;
    using namespace std::chrono;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int time = duration_cast<nanoseconds>(t1.time_since_epoch()).count();
    using namespace std;
    simple_rand.seed(time);
    string output = "";
    int i1=0, digits = 0, upper = 0, lower = 0, special = 0, numbers = 0, l;
    digits = stoi(read("digits"));
    if (read("include_upper_case") == "true") {
        l = digits / 2.5;
        upper = simple_rand() % l + 1;
        digits -= upper;
    }
    if (read("include_lower_case") == "true") {
        l = digits / 2;
        lower = simple_rand() % l + 1;
        digits -= lower;
    }
    if (read("include_special_characters") == "true") {
        l = digits / 2;
        special = simple_rand() % l + 1;
        digits -= special;
    }
    if (read("include_numbers") == "true") {
        numbers = digits;
    }
    else {
        if (read("include_lower_case") == "true") {
            lower += digits;
        }
        else if (read("include_upper_case") == "true") {
            upper += digits;
        }
        else if (read("include_special_characters") == "true") {
            special += digits;
        }
        else {
            cout << "error generating, please check your options.\n";
            return;
        }
    }
    for (int i = 0; i < stoi(read("digits")); i++) {
        i1 = simple_rand() % 5;
        if (i1 == 0) {
            if (upper > 0) {
                output += randupper(simple_rand);
                upper--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 1) {
            if (lower > 0) {
                output += randlower(simple_rand);
                lower--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 2) {
            if (special > 0) {
                output += randspecial(simple_rand);
                special--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 3 || i1 == 4) {
            if (numbers > 0) {
                output += randnumbers(simple_rand);
                numbers--;
            }
            else {
                i--;
            }
        }
    }
    cout << output << endl;
    toClipboard(output);
}

int findposition(string value) {
    if (value == "include_special_characters") {
        return 1;
    }
    else if (value == "include_upper_case") {
        return 2;
    }
    else if (value == "include_lower_case") {
        return 3;
    }
    else if (value == "include_numbers") {
        return 4;
    }
    else if (value == "digits") {
        return 5;
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
