import os

import wcyatfiles as files

file = open("windows/password-generator.cpp")
r = False
for line in file:
    if "int main()" in line:
        r = True
    if r:
        if "cout" in line:
            continue
        if "core();" in line:
            files.appendfile("windows/pgtest.cpp",
                             line.replace("core", "generate"))
        else:
            files.appendfile("windows/pgtest.cpp", line)
    else:
        if not "cout << endl" in line:
            files.appendfile("windows/pgtest.cpp", line)
os.system("chmod +x test-windows1.sh && sh test-windows1.sh")
testfile = open("windows/pgtest.txt")
for line in testfile:
    teststr = line
os.system("cd windows && rm pgtest.cpp pgtest pgtest.txt pg_options.txt")
special_characters = "!#$%&*?"
testu = any(ele.isupper() for ele in teststr)
testl = any(ele.islower() for ele in teststr)
testn = False
for i in teststr:
    if i.isdigit():
        testn = True
if not (any(c in special_characters for c in teststr) and testu and testl
        and testn and len(teststr) == 10):
    print("output = " + teststr)
    raise ValueError("Test failed")
else:
    print("test succeeded")
