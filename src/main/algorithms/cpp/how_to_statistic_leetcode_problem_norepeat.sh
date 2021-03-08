ls ./*/ | grep -E "_[0-9]+$" |awk -F '_' '{print $NF}' | sort -n -u | wc -l
