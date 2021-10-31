launcher:  main.o
	gcc -o launcher main.o

main.o : main.c
	gcc -o main.o -W -Wall -Wextra -Werror -c main.c

clean :
	rm -rf *.o *.zip

mrproper : clean
	rm launcher

zip : 
	zip -r mallocWorld.zip .