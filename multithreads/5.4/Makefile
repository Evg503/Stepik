all:
	g++ /home/box/shell.cpp -o /home/box/shell
clean:
	rm -f /home/box/shell /home/box/result.out
test: test1 test2 test3

test1:
	echo "who | sort | uniq -c | sort -nk1" | /home/box/shell
test2:
	echo "echo 1" | /home/box/shell
test3:
	echo -n "who|sort|uniq -c|sort -n -k1"|/home/box/shell
