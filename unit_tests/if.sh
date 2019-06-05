a='1'



if [ $a == 1 ] 
then
	echo a
fi



if [ $a == 1 ] then
	echo b
fi



if [ $a == 1 ] then
	echo c
fi



if [ $a == 1 ]
then
	echo d
elif [ $a == 2 ]
then
	echo e
else
	echo f
fi



if [ $a == 1 ] then
	echo g
elif [ $a == 2 ] then
	echo h
elif [ $a == 3 ]
then
	echo i
else
	echo j
fi



if [ $a == 1 ] then
	if [ $a == 1 ] then
		if [ $a == 1 ] then
			echo k
		elif [ $a == 2 ] then
			echo l
		fi
	elif [ $a == 2 ] then
		echo m
	else
		echo n
	fi
fi
