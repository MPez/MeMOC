CC = g++
CPPFLAGS = -g -Wall -O2
LDFLAGS =

#CPX_INCDIR  = /opt/CPLEX_Studio/cplex/include
#CPX_LIBDIR  = /opt/CPLEX_Studio/cplex/lib/x86-64_linux/static_pic

CPX_INCDIR = /opt/ibm/ILOG/CPLEX_Studio126/cplex/include/
CPX_LIBDIR = /opt/ibm/ILOG/CPLEX_Studio126/cplex/lib/x86-64_linux/static_pic/
CPX_LDFLAGS = -lcplex -lm -pthread

OBJ = main.o pannello.o

%.o: %.cpp
		$(CC) $(CPPFLAGS) -I$(CPX_INCDIR) -c $^ -o $@

cplex: $(OBJ)
		$(CC) $(CPPFLAGS) $(OBJ) -o cplex -L$(CPX_LIBDIR) $(CPX_LDFLAGS)

.PHONY: clean

clean:
		rm -rf $(OBJ) cplex

