#/bin/bash

function retshells {
	cat /etc/passwd | cut -f 7 -d ":" | sort | uniq
}
function countshells {
	cat /etc/passwd | grep $1$ | wc -l
}
function findpkg {
	rpm -qf $1
}

for i in $(retshells);
do
	echo $(countshells ${i}),${i},$(findpkg ${i})
done
