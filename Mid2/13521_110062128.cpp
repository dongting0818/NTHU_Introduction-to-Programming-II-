 #include "function.h"
#include<iostream>
#include<string>
//#include "13521.h"
using namespace std;

void Number_Codec::encode()
{
    int temp = 0;
    string ans = "";
    for(int i=0;i<code_str.length();i++){
        temp = (int)code_str[i]-'a'+1;
        ans+=to_string(temp);
    }
    code_str = "";
    for(int i=0;i<ans.length();i++){
        code_str+=ans[i];
    }
}

void Two_Number_Codec::encode()
{
    int temp = 0;
    string ans = "";
    for(int i=0;i<code_str.length();i++){
        temp = (int)code_str[i]-'a'+1;
        if(temp<10){
            ans+='0';
            ans+=to_string(temp);
        }else{
            ans+=to_string(temp);
        }
    }
    code_str = "";
    for(int i=0;i<ans.length();i++){
        code_str+=ans[i];
    }
}

void The_Rail_Fence_Cipher_Codec::encode()
{
   size_t len = code_str.length();
   size_t upper_len, lower_len;
   string up = "";
   string low = "";
   if(len%2 == 1){
       upper_len = (len+1)/2;
       lower_len = (len-1)/2;
   }else{
       upper_len = lower_len = len/2;
   }
   for(int i=0;i<len;i++){
       if(i<upper_len){
           up += code_str[i];
       }else if(i<lower_len+upper_len){
           low += code_str[i];
       }
   }
   code_str = "";
   int i=0;
   while(i<upper_len){
       if(i<upper_len){
           code_str += up[i];
       }
       if(i<lower_len){
           code_str += low[i];
       }
       i++;
   }
}
