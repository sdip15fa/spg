Simple password generator. <br />
Sample runs: <br/>

![v1.0](https://gitlab.com/wcyat/simple-password-generator/-/raw/master/simple-password-generator-v1.0.png)
![link to video](https://gitlab.com/wcyat/simple-password-generator/-/raw/master/v2.0_-_v1.2.mp4) <br>
Left: v2.0, Right: v1.2, both running on windows 11, with default configuration but 999999 digits.
# Features
- Copy to clipboard (windows)
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
v2.1:
```
wget https://gitlab.com/wcyat/simple-password-generator/uploads/61ec45fc5585d662f1ba624ea2df0d4b/simple-password-generator-v2.1.run
chmod +x simple-password-generator-v2.1.run
```
```
./simple-password-generator-v2.1.run
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
- g++:
```
sudo apt install g++
#sudo apt install build-essential
```
### Steps
```
git clone https://gitlab.com/wcyat/simple-password-generator.git #clone the repository
cd simple-password-generator/linux
g++ pg.cpp -o spg.run
```
Now you can run it.
```
./spg.run
```
#### Optional
```
sudo cp spg.run /bin/spg
```
Now you can run it with:
```
spg
```
in any directories
## MacOS
### Prerequisites
- xcode
- git
### Steps
```
git clone https://gitlab.com/wcyat/simple-password-generator.git #clone the repository
cd simple-password-generator/macos
g++ pg.cpp -o spg.run
```
Now you can run it.
```
chmod 755 spg.run
./spg.run
```
