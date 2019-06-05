#/usr/bin/42sh

#comment
number=1
while [ $number -lt 4 ]
do
	if true
	then
		echo a
	else
		echo b
	fi
	i=$((i + 1))
done
