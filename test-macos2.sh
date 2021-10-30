cd macos
g++ pg.cpp -o spg-macos.run
chmod +x spg-macos.run
./spg-macos.run > spgtest.txt
cd ..
git config --global user.email "wcyat-githubactions@wcyat.me"
git config --global user.name "Github Actions"
git add -A
git commit -a -m update
git push origin master
