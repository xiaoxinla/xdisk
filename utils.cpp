#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <vector>
#include <json/json.h>
#include <sodium.h>
typedef unsigned char BYTE;
#define NPUB "swg232sd"

map<string,string> getQueryInfo(char* queryStr, const char* keys[], int len) {
    map<string, string> mmap;
    char value[256];
    for(int i=0; i<len; i++) {
        char *pch = strstr(queryStr, keys[i]);
        sscanf(pch+strlen(keys[i])+1, "%[^&]", value);
        mmap[keys[i]] = string(value);
    }
    return mmap;
}

map<string, string> getFormData(char *form, vector<string> keys) {
	map<string, string> map;
    char value[128];
    char *pch ;
    for(int i=0; i<keys.size(); i++) {
        pch = strstr(form, keys[i].c_str());
        if(pch!=NULL) {
            sscanf(pch+keys[i].length()+5, "%s", value);
            printf("%s : %s\n", keys[i].c_str(), value);
            map[keys[i]]=string(value);
        }
    }
    return map;
}

string genUUID() {
    uuid_t uuid;
    uuid_generate(uuid);
    char buf[35];
    uuid_unparse(uuid, buf);
    return string(buf);
}
string getFileDirListJson(vector<vector<string> > filedirs) {
    Json::Value root;
    if(filedirs.size()) {
        root["status"] = 1;
    } else {
        root["status"] = 1;
    }
    for(int i=0; i<filedirs.size(); i++) {
        Json::Value tmp;
        tmp["file_id"] = filedirs[i][0];
        tmp["file_name"] = filedirs[i][1];
        tmp["ctime"] = filedirs[i][2];
        tmp["size"] = atol(filedirs[i][3].c_str());
        tmp["status"] = atoi(filedirs[i][4].c_str());
        tmp["is_dir"] = atoi(filedirs[i][5].c_str());
        root["filedir"].append(tmp);
    }
    Json::FastWriter writer;
    string str = writer.write(root);
    return str;
};

BYTE fromHex(const BYTE &x)
{
    return isdigit(x) ? x-'0' : x-'A'+10;
}

string URLDecode(const string &sIn)
{
    string sOut;
    for( size_t ix = 0; ix < sIn.size(); ix++  )
    {
        BYTE ch = 0;
        if(sIn[ix]=='%')
        {
            ch = (fromHex(sIn[ix+1])<<4);
            ch |= fromHex(sIn[ix+2]);
            ix += 2;
        }
        else if(sIn[ix] == '+')
        {
            ch = ' ';
        }
        else
        {
            ch = sIn[ix];
        }
        sOut += (char)ch;
    }
    return sOut;
}

int getDBIndex(string str, int total) {
    if(str.empty()) {
        return 0;
    }
    char ch = str[0];
    return ch%total;
}
string encryptWithAES(const char* data, const char* key){
    unsigned char nonce[crypto_aead_chacha20poly1305_NPUBBYTES] = {0};
    unsigned char ikey[crypto_aead_chacha20poly1305_KEYBYTES] = {0};
    unsigned char ciphertext[crypto_aead_chacha20poly1305_ABYTES+strlen(data)];
    unsigned long long ciphertext_len;
    memcpy(ikey, key, strlen(key));
    memcpy(nonce, NPUB, strlen(NPUB));
    crypto_aead_chacha20poly1305_encrypt(ciphertext, &ciphertext_len,
        (unsigned char*)data, strlen(data),
        NULL, 0,
        NULL, nonce, ikey);
    char rst[128];
    int rlen = Base64_Encode(rst, (char *)ciphertext, ciphertext_len);
    return string(rst);
}

string decryptWithAES(const char* data, const char* key){
    BYTE msg[128];
    int slen = Base64_Decode((char*)msg, data, strlen(data));
    unsigned char nonce[crypto_aead_chacha20poly1305_NPUBBYTES] = {0};
    unsigned char ikey[crypto_aead_chacha20poly1305_KEYBYTES] = {0};
    unsigned char decrypted[128];
    unsigned long long decrypted_len;
    memcpy(ikey, key, strlen(key));
    memcpy(nonce, NPUB, strlen(NPUB));
    if (crypto_aead_chacha20poly1305_decrypt(decrypted, &decrypted_len,
        NULL,
        msg, slen,
        NULL,
        0,
        nonce, ikey) != 0) {
        return string();
    }
    decrypted[decrypted_len] = '\0';
    return string((char *)decrypted);

}

BYTE Decode_GetByte(char c);
char Encode_GetChar(BYTE num);

//===================================
//    Base64 解码
//===================================
BYTE Decode_GetByte(char c)
{
    if(c == '+')
        return 62;
    else if(c == '/')
        return 63;
    else if(c <= '9')
        return (BYTE)(c - '0' + 52);
    else if(c == '=')
        return 64;
    else if(c <= 'Z')
        return (BYTE)(c - 'A');
    else if(c <= 'z')
        return (BYTE)(c - 'a' + 26);
    return 64;

}

//解码
size_t Base64_Decode(char *pDest, const char *pSrc, size_t srclen)
{
    BYTE input[4];
    size_t i, index = 0;
    for(i = 0; i < srclen; i += 4)
    {
        //byte[0]
        input[0] = Decode_GetByte(pSrc[i]);
        input[1] = Decode_GetByte(pSrc[i + 1]);
        pDest[index++] = (input[0] << 2) + (input[1] >> 4);
        //byte[1]
        if(pSrc[i + 2] != '=')
        {
            input[2] = Decode_GetByte(pSrc[i + 2]);
            pDest[index++] = ((input[1] & 0x0f) << 4) + (input[2] >> 2);
        }

        //byte[2]
        if(pSrc[i + 3] != '=')
        {
            input[3] = Decode_GetByte(pSrc[i + 3]);
            pDest[index++] = ((input[2] & 0x03) << 6) + (input[3]);
        }
    }

    //null-terminator
    pDest[index] = 0;
    return index;

}

//===================================
//    Base64 编码
//===================================
char Encode_GetChar(BYTE num)
{
    return
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "+/="[num];

}

//编码
size_t Base64_Encode(char *pDest, const char *pSrc, size_t srclen)
{
    BYTE input[3], output[4];
    size_t i, index_src = 0, index_dest = 0;
    for(i = 0; i < srclen; i += 3)
    {
        //char [0]
        input[0] = pSrc[index_src++];
        output[0] = (BYTE)(input[0] >> 2);
        pDest[index_dest++] = Encode_GetChar(output[0]);

        //char [1]
        if(index_src < srclen)
        {
            input[1] = pSrc[index_src++];
            output[1] = (BYTE)(((input[0] & 0x03) << 4) + (input[1] >> 4));
            pDest[index_dest++] = Encode_GetChar(output[1]);
        }
        else
        {
            output[1] = (BYTE)((input[0] & 0x03) << 4);
            pDest[index_dest++] = Encode_GetChar(output[1]);
            pDest[index_dest++] = '=';
            pDest[index_dest++] = '=';
            break;
        }
        //char [2]
        if(index_src < srclen)
        {
            input[2] = pSrc[index_src++];
            output[2] = (BYTE)(((input[1] & 0x0f) << 2) + (input[2] >> 6));
            pDest[index_dest++] = Encode_GetChar(output[2]);
        }
        else
        {
            output[2] = (BYTE)((input[1] & 0x0f) << 2);
            pDest[index_dest++] = Encode_GetChar(output[2]);
            pDest[index_dest++] = '=';
            break;
        }

        //char [3]
        output[3] = (BYTE)(input[2] & 0x3f);
        pDest[index_dest++] = Encode_GetChar(output[3]);
    }
    //null-terminator
    pDest[index_dest] = 0;
    return index_dest;

}
