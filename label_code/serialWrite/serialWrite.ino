#include <SoftwareSerial.h>


String words[117]={"aaaaaab","aaaaaac","aaaaaad","aaaaaae","aaaaaaf","aaaaaag","aaaaaah","aaaaaai","aaaaaaj","aaaaaak","aaaaaal","aaaaaam","aaaaaan","aaaaaao","aaaaaap",
"aaaaaaq","aaaaaar","aaaaaas","aaaaaat","aaaaaau","aaaaaav","aaaaaaw","aaaaaax","aaaaaay","aaaaaaz","aaaaaaA","aaaaaaB","aaaaaaC","aaaaaaD","aaaaaaE","aaaaaaF","aaaaaaG",
"aaaaaaH","aaaaaaI","aaaaaaJ","aaaaaaK","aaaaaaL","aaaaaaM","aaaaaaN","aaaaaaO","aaaaaaP","aaaaaaQ","aaaaaaR","aaaaaaS","aaaaaaT","aaaaaaU","aaaaaaV","aaaaaaW","aaaaaaX",
"aaaaaaY","aaaaaaZ","aaaaaazz","aaaaabb","aaaaabc","aaaaabd","aaaaabe","aaaaabf","aaaaabg","aaaaabh","aaaaabi","aaaaabj","aaaaabk","aaaaabl","aaaaabm","aaaaabn","aaaaabo",
"aaaaabp","aaaaabq","aaaaabr","aaaaabs","aaaaabt","aaaaabu","aaaaabv","aaaaabw","aaaaabx","aaaaaby","aaaaabz","aaaaabA","aaaaabB","aaaaabC","aaaaabD","aaaaabE","aaaaabF",
"aaaaabG","aaaaabH","aaaaabI","aaaaabJ","aaaaabK","aaaaabL","aaaaabM","aaaaabN","aaaaabO","aaaaabP","aaaaabQ","aaaaabR","aaaaabS","aaaaabT","aaaaabU","aaaaabV","aaaaabW",
"aaaaabX","aaaaabY","aaaaabZ","aaaaabkk","aaaaacb","aaaaacc","aaaaacd","aaaaace","aaaaacf","aaaaacg","aaaaach","aaaaaci","aaaaacj","aaaaack","aaaaacl","aaaaacm","aaaaacn"};

SoftwareSerial serial1(33, 11); // RX, TX
SoftwareSerial serial2(37, 35); // RX, TX
SoftwareSerial serial3(12, 14); // RX, TX
char * key;
char * key1;
char * key2;
char * key3;
String str1,str2,str3;

void setup() {
  
  serial1.begin(1200);
  serial2.begin(2400);
  serial3.begin(4800);
 
  }


void loop() {
  for (int i = 0; i<117;i++){
    
    str1=words[i]+"akh";
    str2=words[i]+"qdc";
    str3=words[i]+"nbm";
    
    str1.toCharArray(key1, str1.length());
    str2.toCharArray(key2, str2.length());
    str3.toCharArray(key3, str3.length());
    
    serial1.write(key1);
    serial2.write(key2);
    serial3.write(key3);}
   
}
