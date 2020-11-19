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
						mkdir -p cmake-build
						cd cmake-build
						echo "Generate MAKEFILE"
						cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi-gcc.cmake ..
						echo "Compile..."
						make

						if [ $? -eq 0 ]
						then
							echo "Success!"
						else
							echo "Failure..." >&2
							exit 1
						fi
					fi
				fi
			done
		fi
	done
done
