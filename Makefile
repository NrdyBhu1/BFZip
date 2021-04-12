CC = g++
FLAGS = -std=c++11

all install: convto convfrom

convto: convto.cpp
  $(CC) $(FLAGS) convto.cpp -o build/convto

convfrom: convfrom.cpp
  $(CC) $(FLAGS) convfrom.cpp -o build/convfrom
