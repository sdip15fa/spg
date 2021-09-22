Simple password generator. <br />
Sample runs: <br/>

![v1.0](https://gitlab.com/wcyat/simple-password-generator/-/raw/master/simple-password-generator-v1.0.png)
# Features
- Copy to clipboard
# Options
<pre>
- upper case (y/n)         default = y
- lower case (y/n)         default = y
- special characters (y/n) default = y
- numbers (y/n)            default = y
- digits                   default = 10
</pre>
# Windows
- download the [latest release](https://gitlab.com/wcyat/simple-password-generator/-/releases) (.exe)
# Linux
v1.2:
```
wget https://gitlab.com/wcyat/simple-password-generator/uploads/85bdc08b149b9f679bf8e87e7c9c933f/simple-password-generator-v1.2.run
```
```
./simple-password-generator-v1.2.run
```

# Build
## Windows
### Prerequisites
- windows 10 or later
- [visual studio](https://visualstudio.microsoft.com/downloads/) 2019 or later
### Steps
Clone/download the repository, open windows/password-generator.sln with visual studio, then build with release mode.
## Linux
### Prerequisites
- debian linux
- qmake and make installed:
```
sudo apt install qt5-qmake qt5-default build-essential make
```
### Steps
```
git clone https://gitlab.com/wcyat/simple-password-generator.git #clone the repository
cd simple-password-generator/linux/build
rm -r * #clear directory
cp -r ../code/* . #copy files from code folder
qmake -project
qmake
nano makefile #make sure pg.cpp is the only source and pg.o is the only object. remove other sources/objects
make #compile
mv build spg.run
```
Now you can run it.
```
./spg.run
```
