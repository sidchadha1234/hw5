#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void solvehelper(string floating1,size_t count,std::string in1,const set<string>& dictionary,std::set<std::string>& finalans);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> fword;
    //in is const and we cannot edit it so create a copy

    string incopy;
    for(auto i : in){
      incopy+=i;
    }
    solvehelper(floating,0,incopy,dict,fword);
    return fword;
    // Add your code here
}


// Define any helper functions here
//dictionary is the wordbank, in1 is the check, floating1 is the floatingptr, count is the marker, final word is the answer
void solvehelper(string floating1, size_t count, std::string in1, const set<string>& dictionary, std::set<std::string>& finalans){
  //if you reach the end of in1 and the size of float is 0 (no more floating characters):
  //if you've reached the end of the dictionary end the function
  //otherwise insert the possible word into the total set 

  if(count == in1.size() && floating1.size()==0){
    if(dictionary.find(in1) == dictionary.end()) return ;
    else finalans.insert(in1);
  }

  //if there is a dash in the current character begin the recursive opreation
  if(count >= in1.size()) return ;//avoid segfaults
  
  if(in1[count]=='-'){
    int dcount = 0;
    for(auto i:in1){
      if(i=='-') dcount+=1; //variable that counts characters in in1;
    
    }
  
  
  //create another string "cpoint" that is a copy of the floating characters
  string cpoint=floating1;
  //if there are more vars than whats been guessed use all possible combinations for alphabet 
  if(dcount>(int)cpoint.size()){
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(auto alphaind : alphabet){
      if(cpoint.find(alphaind) != string::npos){
        int g=cpoint.find(alphaind);

        string tempfloat=cpoint;

        in1[count]=alphaind;
        tempfloat.erase(g,1);
        solvehelper(tempfloat,count+1,in1,dictionary,finalans);
      }
      else{
        in1[count]=alphaind;
        solvehelper(cpoint,count+1,in1,dictionary,finalans);      
        }
    }
  }
  //if you've reached the size, delete what you have in tempfloat and recursively call
  else if(dcount==(int)cpoint.size()){
    size_t i = 0;
    while(i<cpoint.size()){
      string tempfloat=cpoint;      
      in1[count]=cpoint[i];
    
      tempfloat.erase(i,1);
      solvehelper(tempfloat,count+1,in1,dictionary,finalans);
      i++;
    }
  }
}
//if there is no dash call solve helper to the next character and return after
else{
  solvehelper(floating1,count+1,in1,dictionary,finalans);
  return;
}
}
