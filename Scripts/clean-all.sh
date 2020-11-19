#!/bin/bash
HOME=../Projects/
BASE=$PWD

for i in $HOME*
do
	echo "$i"
	echo "$BASE/$i"
	MYPRJ="$BASE/$i/*"
	for j in $MYPRJ
	do
		if  [[ $j != *startup ]] && [[ $j != *memory ]] ;
		then
			echo "PRJ DIRECTORY: $j"
			MYPRJ="$j/*"
			for z in $MYPRJ
			do
				if  [[ $z != *src ]] ;
				then
					echo "PRJ DIRECTORY COMPILER: $z"
					if [[ $z == *CMAKE ]] ;
					then
						cd $z
						rm -r cmake-build
					fi
				fi
			done
		fi
	done
done
