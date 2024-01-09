#include "Crypter.h"

/*一种转换关系:11->[0]
 * 10->[1]
 * 01->[2]
 * 00->[3]
 * */
char BinToChar(char s,char w){
    return pswMap[(s=='1'&&w=='1')?0:
                  ((s=='1')?1:
                   ((w=='1')?2:3))];
}
string CharToBin(char a){
    return a==pswMap[0]?"11":
           (a==pswMap[1]?"10":
            (a==pswMap[2]?"01":
            (a==pswMap[3]?"00":"e")));
}

string Encrypt(string str){
    //Convert string to byte[]
    byte data[str.length()];
    memcpy(data, str.data(), str.length());

    string s;
    for(auto bit: data)
    {
        //Convert byte to 01str
        int i=to_integer<int>(bit);
        bitset<8> b(i);
        string sw=b.to_string();

        for(int a=0;a<sw.length();a+=2){
            s.push_back(BinToChar(sw[a],sw[a+1]));
        }
    }
    return ZipString(s);
}

string Decrypt(string str){
    str= UnZipString(str);
    string bin;
    int count=0;
    vector<byte> ByteSet;
    for(char c :str){
        bin+=CharToBin(c);
        count++;
        if(count==4){
            count=0;
            bitset<8> b(bin);
            bin.clear();
            ByteSet.push_back((byte)b.to_ulong());
        }
    }
    int size=ByteSet.size();
    char* p=new char[size];
    memcpy(p,ByteSet.data(),size);
    p[size]=0;
    string des(p);
    return des;
}

string ZipString(string str){
    string zip;
    int count=0;
    zip.push_back(str[0]);
    for(int i=1;i<str.length();i++){
        char last=str[i-1];
        char now=str[i];
        if(last==now){
            count++;
            if(str[i+1]!=now){
                zip+=to_string(count);
                count=0;
            }
        }else zip.push_back(now);
    }
    return zip;
}
string UnZipString(string str){
    string result;
    for(int i=0;i<str.length();i++){
        if(CharToBin(str[i])=="e"){
            string s;
            s.push_back(str[i]);
            int count= stoi(s);
            for(int c=0;c<count;c++)
                result.push_back(str[i-1]);
        }else result.push_back(str[i]);
    }
    return result;
}