#include <bits/stdc++.h>
using namespace std;

/*金鑰初始置換表*/
int T2[8][7]={57,49,41,33,25,17,9,
              1,58,50,42,34,26,18,
              10,2,59,51,43,35,27,
              19,11,3,60,52,44,36,
              3,55,47,39,31,23,15,
              7,62,54,46,38,30,22,
              14,6,61,53,45,37,29,
              21,13,5,28,20,12,4};

/*金鑰迴圈左移位數表*/
int T3[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

/*金鑰壓縮置換表*/
int T4[8][6]={14,17,11,24,1,5,
              3,28,15,6,21,10,
              23,19,12,4,26,8,
              16,7,27,20,13,2,
              41,52,31,37,47,55,
              30,40,51,45,33,48,
              44,49,39,56,34,53,
              46,42,50,36,29,32};

/*明文初始置換表*/
int T1[8][8]={58,50,42,34,26,18,10,2,
              60,52,44,36,28,20,12,4,
              62,54,46,38,30,22,14,6,
              64,56,48,40,32,24,16,8,
              57,49,41,33,25,17,9,1,
              59,51,43,35,27,19,11,3,
              61,53,45,37,29,21,13,5,
              63,55,47,39,31,23,15,7};
              
/*資料擴充套件表*/
int T5[8][6]={32,1,2,3,4,5,
              4,5,6,7,8,9,
              8,9,10,11,12,13,
              12,13,14,15,16,17,
              16,17,18,19,20,21,
              20,21,22,23,24,25,
              24,25,26,27,28,29,
              28,29,30,31,32,1};

/*S盒置換表*/
int S[8][4][16]={{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
                {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
                {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
                {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
                {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
                {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
                {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
                {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

/*P盒置換表*/
int P[4][8]={16,7,20,21,
             29,12,28,17,
             1,15,23,26,
             5,18,31,10,
             2,8,24,14,
             32,27,3,9,
             19,13,30,6,
             22,11,4,25};


/*最終置換表*/
int T6[8][8]={  40,8,48,16,56,24,64,32,
                  39,7,47,15,55,23,63,31,
                  38,6,46,14,54,22,62,30,
                  37,5,45,13,53,21,61,29,
                  36,4,44,12,52,20,60,28,
                  35,3,43,11,51,19,59,27,
                  34,2,42,10,50,18,58,26,
                  33,1,41,9,49,17,57,25};

/*

 *最終置換函式 64位->64位

 *函式說明：s為完成最後一輪迴圈得到的64位資料

 *返回值為密文或明文

*/
string final_permutation(string s)
{
    string rs="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            rs+=s[T6[i][j]-1];
        }
    }
    return rs;
}

/*

 *P盒置換函式 32位->32位

 *函式說明：s為S盒的輸出

*/
string P_box(string s)
{
    string rs="";
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<8;j++)
        {
            rs+=(s[P[i][j]-1]);
        }
    }
    return rs;
}

/*

 *S盒置換函式 48位->32位

 *函式說明：s為48位資料

 *返回值為32位

*/
string S_box(string s)
{
    string rs="";
    string s1;
    int k1,k2;//S盒的行號和列號
    int h=1;//決定使用那個S盒
    for(int i=0;i<=42;i=i+6,h++)
    {
        k1=(s[i]-'0')*2+(s[i+5]-'0')*1;
        k2=(s[i+1]-'0')*8+(s[i+2]-'0')*4+(s[i+3]-'0')*2+(s[i+4]-'0')*1;
        int x=S[h-1][k1][k2];
        s1="";
        int y=8;
        for(int j=1;j<=4;j++)
        {
            if(x<y)
            {
                s1+="0";
                y/=2;
            }else
            {
                s1+="1";
                x=x%y;
                y/=2;
            }
        }
        rs+=s1;
    }
    return rs;
}

/*

 *異或運算函式

 *要求位數相同

*/
string XOR(string s1,string s2)
{
    string rs="";
    for(int i=0;i<s1.length()&&i<s2.length();i++)
    {
        rs+=((s1[i]-'0')^(s2[i]-'0'))+'0';
    }
    return rs;
}

/*

 *資料擴充套件函式 32->48

 *函式說明：s為資料的右半部分 32位

 *擴充套件成48位的輸出

*/
string plaintext_righthalf_extended_permutation(string s)
{
    string rs="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<6;j++)
        {
            rs+=s[T5[i][j]-1];
        }
    }
    return rs;
}

/*

 *金鑰壓縮置換函式 56位->48位

 *函式說明：s為56為的金鑰

 *輸出為48位的子金鑰

*/
string secret_key_compression_replacement(string s)
{
    string rs="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<6;j++)
        {
            rs+=s[T4[i][j]-1];
        }
    }
    return rs;
}

/*

 *金鑰迴圈左移函式 56位->56位

 *函式說明：k為左移位數 s為金鑰

 *返回值位數不變

*/
string secret_ket_left_move(int k,string s)//金鑰迴圈左移k位
{
    string s1=s.substr(0,28);
    string s2=s.substr(28,28);
    string rs=s1.substr(k,28-k)+s1.substr(0,k)+s2.substr(k,28-k)+s2.substr(0,k);
    return rs;
}

/*

 *金鑰初始置換函式 64位->58位

 *函式說明：s為64位的初始金鑰

 *返回值為58位

*/
string secret_key_initial_permutation(string s)
{
    string rs="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<7;j++)
        {
            rs+=s[T2[i][j]-1];
        }
    }
    return rs;
}

/*

 *明文初始置換函式 64位->64位

 *函式說明：s為初始明文 64位

 *返回值為6位

*/
string plaintext_initial_permutation(string s)//明文初始置換
{
    string rs="";
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            rs+=s[T1[i][j]-1];
        }
    }
    return rs;
}

/*

 *16進位制轉2進位制函式

 *函式說明：s為16進位制字串

 *返回為2進位制字串

*/
string H(string s)
{
    string s1;
    string rs="";
    for(int i=0;i<s.length();i++)
    {
        int x;
        if(s[i]>='0'&&s[i]<='9')
        {
            x=s[i]-'0';
        }else
        {
            x=s[i]-'A'+10;
        }
        s1="";
        int y=8;
        for(int j=1;j<=4;j++)
        {
            if(x<y)
            {
                y/=2;
                s1+="0";
            }else
            {
                s1+="1";
                x=x%y;
                y=y/2;
            }
        }
        rs+=s1;
    }
    return rs;
}

/*

 *2進位制轉16進位制函式

 *str為2進位制字串

 *返回值為16進位制字串

*/
string G(string str)
{
    string rs="";
    char temp;
    for(int i=0;i<=str.length()-4;i=i+4)
    {
        int x=(str[i]-'0')*8+(str[i+1]-'0')*4+(str[i+2]-'0')*2+str[i+3]-'0';

        if(x>=10)
        {
            temp=(char)(x-10+'A');
        }else
        {
            temp=(char)(x+'0');
        }
        rs+=temp;
    }
    return rs;
}

/*

 *封裝函式f

 *函式說明：接收32位資料和48位的子金鑰 產生一個32位的輸出

 *str1:32位資料  str2:48位的子金鑰

 *返回值32位

*/

string f(string str1,string str2)
{
    string expendR=plaintext_righthalf_extended_permutation(str1);

    string rs=XOR(expendR,str2);

    rs=S_box(rs);

    rs=P_box(rs);

    return rs;
}

/*

 *子金鑰生成函式

 *函式說明：s為給定的金鑰

 *生成16個子金鑰

*/
string Keys1[20];
string Keys2[20];

void generateKeys1(string s)
{
    s=secret_key_initial_permutation(s);

    for(int i=1;i<=16;i++)
    {
        s=secret_ket_left_move(T3[i-1],s);
        Keys1[i]=secret_key_compression_replacement(s);
    }
}

void generateKeys2(string s)
{
    s=secret_key_initial_permutation(s);

    for(int i=1;i<=16;i++)
    {
        s=secret_ket_left_move(T3[i-1],s);
        Keys2[i]=secret_key_compression_replacement(s);
    }
}
/*

 *DES加密函式 64位->64位

 *函式說明：str1為64位的給定明文

 *返回值為64位的密文

*/
 string encrypt1(string str1)
 {
     //第一步:明文初始置換 64->64
     str1=plaintext_initial_permutation(str1);

     //第二步:資料分組
     string left=str1.substr(0,32);
     string right=str1.substr(32,32);

     string newleft;

     //第三步:16輪迭代
     for(int i=1;i<=16;i++)
     {
         newleft=right;

         right=XOR(left,f(right,Keys1[i]));

         left=newleft;
     }

     //第四步:合併資料 注意位R16L16
     string rs=right+left;

     //結尾置換
     rs=final_permutation(rs);
     cout<<"明文1最終置換結果(二進位制):"<<rs<<endl;
     cout<<"明文1最終置換結果(十六進位制):"<<G(rs)<<endl<<endl;
     return rs;

 }
 
 string encrypt2(string str1)
 {
     //第一步:明文初始置換 64->64
     str1=plaintext_initial_permutation(str1);

     //第二步:資料分組
     string left=str1.substr(0,32);
     string right=str1.substr(32,32);

     string newleft;

     //第三步:16輪迭代
     for(int i=1;i<=16;i++)
     {
         newleft=right;

         right=XOR(left,f(right,Keys2[i]));

         left=newleft;
     }

     //第四步:合併資料 注意位R16L16
     string rs=right+left;

     //結尾置換
     rs=final_permutation(rs);
     cout<<"明文2最終置換結果(二進位制):"<<rs<<endl;
     cout<<"明文2最終置換結果(十六進位制):"<<G(rs)<<endl<<endl;
     return rs;

 }
 /*

 *解密函式

 *str為密文

 *輸出明文

 */
 string decrypt1(string str)
 {
     //把密文當作明文進行初始明文置換
     str=plaintext_initial_permutation(str);

     //分組
     string left=str.substr(0,32);
     string right=str.substr(32,32);

     string newleft;

     //逆序的子金鑰使用 16輪迭代
     for(int i=16;i>=1;i--)
     {
         newleft=right;
         right=XOR(left,f(right,Keys1[i]));
         left=newleft;
     }

     //合併
     string rs=right+left;

     //最後置換
     rs=final_permutation(rs);

     return rs;
 }
  string decrypt2(string str)
 {
     //把密文當作明文進行初始明文置換
     str=plaintext_initial_permutation(str);

     //分組
     string left=str.substr(0,32);
     string right=str.substr(32,32);

     string newleft;

     //逆序的子金鑰使用 16輪迭代
     for(int i=16;i>=1;i--)
     {
         newleft=right;
         right=XOR(left,f(right,Keys2[i]));
         left=newleft;
     }

     //合併
     string rs=right+left;

     //最後置換
     rs=final_permutation(rs);

     return rs;
 }
int main()
{
   //明文 16進位制
   string str1="0000000000000000";
   string str3="1000000000000000";
   //金鑰16進位制
   string str2="0123456789ABCDEF";
   string str4="0123456789ABCDEF";

   string temp=str1;//儲存十六進位制的明文以便後面驗證演算法正確性
   cout<<"十六進位制明文1:"<<str1<<endl;
   cout<<"十六進位制明文2:"<<str3<<endl;
   cout<<"十六進位制金鑰1:"<<str2<<endl;
   cout<<"十六進位制金鑰2:"<<str4<<endl<<endl;  
   //進位制轉換 16->2
   str1=H(str1);
   str3=H(str3);
   str2=H(str2);
   str4=H(str4);
   cout<<"二進位制明文1:"<<str1<<endl;
   cout<<"二進位制明文2:"<<str3<<endl;
   cout<<"二進位制金鑰1:"<<str2<<endl;
   cout<<"二進位制金鑰2:"<<str4<<endl<<endl;

   //生成16個子金鑰
   generateKeys1(str2);
   generateKeys2(str4);

   //加密
   string rs1=encrypt1(str1);
   string rs2=encrypt2(str3);

   //解密
   //rs=decrypt(rs);
   return 0;
}
