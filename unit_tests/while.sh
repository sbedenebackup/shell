a=1

while [ $a == 1 ]
do
	echo f
done

while [ $a == 1 ] do
	echo f
done

while [ $a == 1 ] do
	echo f
	while [ $a == 1 ] do
		echo f
	done
done
