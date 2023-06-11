#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
using namespace std;
 
int getOptions(string s,string op,int opt=2){
  retry:
    cout<<s<<endl;
    string a;
    cout<<op<<endl;
    printf("\nHit what's in your mind_>");
    cin>>a;
  if (a.length()>1){
    cout<<"\nInvalid Option! ";
    goto retry;
  }
  if (a[0]<=48||a[0]>opt+48){
    cout<<"\nInvalid option! ";
    goto retry;
  }
  return a[0]-48;
}

int valueAt(char source,string check){
  int val=-1;
  for (int i=0;check[i]!='\0';++i)
    if (source==check[i]){
      val=i;
      break;}
  return val;
}

inline void increment(char &c,string r){
  c=r[valueAt(c,r)+1];
}

void loop(int i,string &str,int len,string range){
  if (i!=0){
    str[i]=range[0]-1;
    //why not range[0], (i tried it before) because we have to increment it later, 
    //so it would be incremented to range[1] which we dont want
    cout<<str<<":";
    if (i!=len)
      increment(str[i],range);
    if (str[i-1]!=range[range.length()-1]){
      increment(str[i-1],range);
    cout<<str<<":";
    }
    else
      loop(i-1,str,len,range);
  }
}

string println (string &str,int len,string range){
  if (str[len]==range[range.length()-1])
    loop(len,str,len,range);
  increment(str[len],range);
    cout<<str<<"\n";
  return str;
}

    
string getRange(){
    int ch;
    string r="";
    retry:
    do{
       cout<<endl<<"Select your range (0 for options): ";
       cin>>ch;
       if (ch==0)
         cout<<" 1. Lower-case\n 2. Upper-case\n 3. Lower-case and numeric\n 4. Upper-case and numeric\n 5. Alpha\n 6. Numeric\n 7. Alpha-numeric\n 8. Symbolic\n 9. Lower-case and Symbolic\n10. Upper-case and Symbolic\n11. Lower-case and symbo-numeric\n12. Upper-case and symbo-numeric\n13. Symbo-numeric\n14. Symbolic-alpha\n15. All\n16. Custom\n";
     }
    while (ch==0);;
    switch(ch){
      case  1: r="abcdefghijklmnopqrstuvwxyz";break;
      case  2: r="ABCDEFGHIJKLMNOPQRSTUVWXYZ";break;
      case  3: r="abcdefghijklmnopqrstuvwxyz0123456789";break;
      case  4: r="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";break;
      case  5: r="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";break;
      case  6: r="0123456789";break;
      case  7: r="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";break;
      case  8: r="!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case  9: r="abcdefghijklmnopqrstuvwxyz!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 10: r="ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 11: r="0123456789abcdefghijklmnopqrstuvwxyz!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 12: r="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 13: r="0123456789!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 14: r="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 15: r="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$^&*(){}[]:'<>/|\\?`~-_=+";break;
      case 16: cin>>r;break;
      default: std::cout<<"Error! Please try again!";
                    goto retry;
    }
    return r;
}

bool checkUniqueString(string s){
  //checks if string doesn't have repeated character
  bool flag=true;
  for (int i=0;i<s.length()-1;++i)
    for (int j=i+1;j<s.length();++j)
      if (s[i]==s[j]){
        flag=false;
        break;}
  return flag;
}
//Main starts here
int main(void){
  int min=7,max=7,opt=1;
  bool unique;
  ofstream file("generated.txt");
  string range,str;
  
switch (opt){
case 1:
  range="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unique=1;
  for (int i=min;i<=max;++i){
    str=string(i,range[0]);
    //cout<<str;
    if (checkUniqueString(str))
        file<<str<<endl;
    for (int j=1;j<2000;++j){
      string t=println(str,i-1,range);
      if (unique){
          if(checkUniqueString(t))
            file<<t<<endl;}
      else
          file<<t<<endl;}}
  break;
  default:
    cout<<"This function is yet to be built.\n";}
    } 