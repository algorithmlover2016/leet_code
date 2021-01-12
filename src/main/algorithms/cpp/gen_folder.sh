inputFile=${1:-"res"}
# dirName=$(sed 's/ /_/g' $1 | tr '[A-Z]' '[a-z]')
dirName=$(sed  's/\(.*\)\(\.\) \(.*\)/\3 \1/g' "${inputFile}" | sed 's/[ -]/_/g' | sed 's/[^[:alnum:]_]/_/g' | tr '[A-Z]' '[a-z]')
mkdir "./${dirName}" &&\
cd "./${dirName}" &&\
touch solution.cpp && touch description.txt && touch core.solution &&\
echo "#include \"../../head.h\"\n\n\n" >> solution.cpp
# sed 's/[A-Z]/\l&/g' $1
