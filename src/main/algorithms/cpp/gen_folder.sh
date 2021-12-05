inputFile=${1:-"./res"}
# dirName=$(sed 's/ /_/g' $1 | tr '[A-Z]' '[a-z]')
dirName=$(sed  's/\(.*\)\(\.\) \(.*\)/\3 \1/g' "${inputFile}" | sed 's/[ -]/_/g' | sed 's/[^[:alnum:]_]/_/g' | tr '[A-Z]' '[a-z]')
mkdir "./${dirName}" &&\
cd "./${dirName}" &&\
touch solution.cpp && touch description.txt && touch core.md &&\
# add -e to enable interpretation of backslash escapes
# reference to https://unix.stackexchange.com/questions/65803/why-is-printf-better-than-echo/65819#65819 and
# https://github.com/git-for-windows/git/issues/3454#issuecomment-939253376
echo -e "#include \"../../head.h\"\n\n\n" >> solution.cpp
# sed 's/[A-Z]/\l&/g' $1
