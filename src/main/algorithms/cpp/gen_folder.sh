# dirName=$(sed 's/ /_/g' $1 | tr '[A-Z]' '[a-z]')
dirName=$(sed  's/\(.*\)\(\.\) \(.*\)/\3 \1/g' $1 | sed 's/ /_/g' | tr '[A-Z]' '[a-z]')
mkdir "./${dirName}"
cd "./${dirName}" && touch solution.cpp && touch description.txt && touch core.solution
echo "#include \"../../head.h\"\n \n" > solution.cpp
# sed 's/[A-Z]/\l&/g' $1
