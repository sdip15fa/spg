#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

string read(string value) {
    ifstream input;
    int olength;
    string line = "", output = "";
    size_t pos;
    bool a = true;
    int i = 0;
    input.open("pg_options.txt");
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
    input.close();
    return output;
}

char randupper() {
    char uppercase[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int i = rand() % 26;
    return uppercase[i];
}

char randlower() {
    char lowercase[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int i = rand() % 26;
    return lowercase[i];
}

char randspecial() {
    char special[7] = { '!', '#', '$', '%', '&', '*', '?' };
    int i = rand() % 7;
    return special[i];
}

char randnumbers() {
    char numbers[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
    int i = rand() % 10;
    return numbers[i];
}

void generate() {
    string output = "";
    int i1=0, digits = 0, upper = 0, lower = 0, special = 0, numbers = 0;
    digits = stoi(read("digits"));
    if (read("include_upper_case") == "true") {
        upper = rand() % (digits / 2) + 1;
        digits -= upper;
    }
    if (read("include_lower_case") == "true") {
        lower = rand() % (digits / 2) + 1;
        digits -= lower;
    }
    if (read("include_special_characters") == "true") {
        special = rand() % (digits / 2) + 1;
        digits -= special;
    }
    if (read("include_numbers") == "true") {
        numbers = digits;
    }
    else {
        if (read("include_upper_case") == "true") {
            upper += digits;
        }
        else if (read("include_lower_case") == "true") {
            lower += digits;
        }
        else if (read("include_special_characters") == "true") {
            special += digits;
        }
        else {
            cout << "error generating, please check your options.";
            return;
        }
    }
    for (int i = 0; i < stoi(read("digits")); i++) {
        i1 = rand() % 4;
        if (i1 == 0) {
            if (upper > 0) {
                output += randupper();
                upper--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 1) {
            if (lower > 0) {
                output += randlower();
                lower--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 2) {
            if (special > 0) {
                output += randspecial();
                special--;
            }
            else {
                i--;
            }
        }
        else if (i1 == 3) {
            if (numbers > 0) {
                output += randnumbers();
                numbers--;
            }
            else {
                i--;
            }
        }
    }
    cout << output;
}

int findposition(string value) {
    ifstream input;
    string line, output = "";
    size_t pos;
    bool a = true;
    int i = 0, position = 0;
    input.open("pg_options.txt");
    if (!input.is_open()) {
        cout << "pg_options.txt missing.";
        return 0;
    }
    while (getline(input, line)) {
        pos = line.find(value);
        if (pos == string::npos) {
            position = i;
            break;
        }
        i++;
    }
    input.close();
    return position;
}

void modifyvalue(string value, string newvalue) {
    ifstream oldfile;
    ofstream newfile;
    string line, content = "";
    int i = 0;
    newfile.open("pg_options_n.txt");
    oldfile.open("pg_options.txt");
    if (!oldfile.is_open()) {
        cout << "pg_options.txt missing.";
        return;
    }
    else {
        while (getline(oldfile, line)) {
            if (i < findposition(value)) {
                content += line;
            }
            else {
                break;
            }
            i++;
        }
        content += value + "=" + newvalue + "\n";
        i = 0;
        while (getline(oldfile, line)) {
            if (i > findposition(value)) {
                content += line;
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

int main()
{
    srand(time(NULL));
    init();
    generate();
}
