#include <iostream>
#include <fstream>
#include <string>

using namespace std;
char quote = '"';

int main () {
  std::ifstream  data("generated.txt");
  std::string line [2000];
  std::string out;

  for (int i = 0;i<2000;i++){
      getline(data,line[i]);
  }
  for (int i = 0;i<2000;i++){
      out += quote+line[i]+quote+",";
  }
std::ofstream file("format.txt");
  
 file<<out;

}