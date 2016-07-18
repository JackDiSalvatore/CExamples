# compile the lib file and make the .so
# you may need -fPIC here on some platforms. and that if you get an error
# cc -c libex29.c -o libex29.o
# cc -shared -o libex29.so libex29.o

cc -c -fPIC libex29.c -o libex29.o
cc libex29.o -shared -o libex29.so

# make the loader program
cc -Wall -g -DNDEBUG ex29.c -ldl -o ex29

# try it out with some things that work
ex29 ./libex29.so print_a_message "hello there"

./ex29 ./libex29.so uppercase "hello there"

./ex29 ./libex29.so lowercase "HELLO tHeRe"

./ex29 ./libex29.so fail_on_purpose "i fail"

# try to give it bad arguments
./ex29 ./libex29.so fail_on_purpose

# try calling a function that is not there
./ex29 ./libex29.so adfasfasd asdfff

# try laoading a .so that is not there
./ex29 ./libex.so asdads asdasdas