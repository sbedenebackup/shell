 aa='1'
if [ $a == 1 ]
then
	if [ $a == 2 ]
	then
		echo d
	elif [ $a == 3 ]
	then
		echo q
	fi
elif [ $a == 2 ]
then
	echo a
else
	echo f
fi
