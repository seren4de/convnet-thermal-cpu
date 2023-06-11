
#include <string.h>
#include <math.h>
using namespace std;
 

inline void increment(char &c,String r){
  c=r[valueAt(c,r)+1];
}
int valueAt(char source,String check){
  int val=-1;
  for (int i=0;check[i]!='\0';++i)
    if (source==check[i]){
      val=i;
      break;}
  return val;
}


void loopy(int i,String &str,int len,String range){
  if (i!=0){
    str[i]=range[0]-1;
    //why not range[0], (i tried it before) because we have to increment it later, 
    //so it would be incremented to range[1] which we dont want
    //cout<<str<<":";
    if (i!=len)
      increment(str[i],range);
    if (str[i-1]!=range[range.length()-1]){
      increment(str[i-1],range);
    //cout<<str<<":";
    }
    else
      loopy(i-1,str,len,range);
  }
}

String fillit(String &str,int len,String range){
  if (str[len]==range[range.length()-1])
    loopy(len,str,len,range);
  increment(str[len],range);
    //cout<<str<<"\n";
  return str;
}


bool checkUniqueString(String s){
  //checks if string doesn't have repeated character
  bool flag=true;
  for (int i=0;i<s.length()-1;++i)
    for (int j=i+1;j<s.length();++j)
      if (s[i]==s[j]){
        flag=false;
        break;}
  return flag;
}
void setup(){
Serial.begin(38400);
}
String repeatToLen(int len, char c){
  String s;
  for (int i=0;i<len;i++){
    s += c;
  }
  return s;
}
//Main starts here
void loop(){
  int min=5,max=6,opt=1;
  bool unique;
  String range,str;
  range="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*(){}[]:'<>/|\\?`~-_=+";
  unique=1;
  switch (opt){
    case 1:
      for (int i=min;i<=max;++i){
        str=repeatToLen(i,range[0]);
        //cout<<str;
        if (checkUniqueString(str))
            Serial.println(str);
        for (int j=1;j<pow(range.length(),i);++j){
          String t=fillit(str,i-1,range);
          if (unique){
              if(checkUniqueString(t))
                Serial.println(t);
                }
          }}
          break;
       default:
          Serial.println("This function is yet to be built.\n");}

} 
