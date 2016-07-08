CC = g++

all : gbdt_train.o gradient_boosting.o
	$(CC) -o do_train gbdt_train.o gradient_boosting.o

gdbt_train.o: gbdt_train.cpp
	$(CC) -W -Wall -c -o  gbdt_train.o gbdt_train.cpp

gradient_boosting.o: gradient_boosting.cpp
	$(CC) -W -Wall -c -o gradient_boosting.o gradient_boosting.cpp

clean : 
	rm -f *.o do_train
