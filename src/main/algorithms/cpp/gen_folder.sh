dirName=$(sed 's/ /_/g' $1 | tr '[A-Z]' '[a-z]')
mkdir "./${dirName}"
# sed 's/[A-Z]/\l&/g' $1
