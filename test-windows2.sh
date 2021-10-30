cd windows
g++ password-generator.cpp -o spg.exe
cd ..
git config --global user.email "wcyat-azurepipelines@wcyat.me"
git config --global user.name "Azure pipelines"
git add -A
git commit -a -m update
git push origin master
