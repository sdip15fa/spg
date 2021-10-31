import wcyatfiles as files
import os
os.system("rm -r macos && cp -r linux macos && cd macos && rm *.run")
file = open("macos/pg.cpp")
r = False
for line in file:
  if "int main()" in line:
    r = True
  if r:
    if "cout" in line:
      continue
    if "core();" in line:
      files.appendfile("macos/pgtest.cpp", line.replace("core", "generate"))
    else:
      files.appendfile("macos/pgtest.cpp", line)
  else:
    if not "cout << endl" in line:
      files.appendfile("macos/pgtest.cpp", line)
print("running script...")
os.system("chmod 755 test-macos1.sh && ./test-macos1.sh")
testfile = open("macos/pgtest.txt")
for line in testfile:
  teststr = line
os.system("cd macos && rm pgtest.cpp pgtest pgtest.txt pg_options.txt")
special_characters = "!#$%&*?"
testu = any(ele.isupper() for ele in teststr)
testl = any(ele.islower() for ele in teststr)
testn = False
for i in teststr:
  if i.isdigit():
    testn = True
if not(any(c in special_characters for c in teststr) and testu and testl and testn and len(teststr) == 10):
  print("output = " + teststr)
  raise ValueError("Test failed")
else:
  print("test succeeded")
os.system("chmod 755 test-macos2.sh && ./test-macos2.sh")
