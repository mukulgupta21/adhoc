#include <iostream>
#include "openssl/md5.h"
#include <cstdio>
#include <vector>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

char s[1000];
long long cnt = 0;
unsigned char digest[16];
vector <const unsigned char*> vstr;
int N;

int findMatch(const vector<const unsigned char*>& vmd5,
              const unsigned char* md5Digest);

int md5_digest(const char* text, int len, unsigned char* md5Digest);

bool isLower(char c)
{
  if( c >= 97 && c <= 122 )
    return true;
  return false;
}

bool isUpper(char c)
{
  if( c >= 65 && c <= 90 )
    return true;
  return false;
}

bool isSpecial(char c)
{
  if( c >= 32 && c <= 48 )
    return true;
  else if( c >= 58 && c <= 64 )
    return true;
  else if( c>= 91 && c <= 96 )
    return true;
  else if( c>= 123 && c <= 126 )
    return true;
  return false;
}

bool isNumber(char c)
{
  if( c >= '0' && c <= '9')
    return true;
  return false;
}

int CountBit(int n)
{
  int cnt = 0;
  while( n )
  {
    n = n & (n-1);
    cnt++;
  }
  return cnt;
}

/*
GenFlag
[in]: character
[out]: Optimized bitmap based on condition fulfilled.
*/
int GenFlag(char c)
{
  if( isLower(c) )
    return 1;
  else if( isUpper(c) )
    return 1 << 1;
  else if( isNumber(c) )
    return 1 << 2;
  else if( isSpecial(c) )
    return 1 << 3;
  return 0;
}

int gen_all_permutations(char *start, char *end, int flag)
{
  if( start > end )
  {
    if( flag == 15 )
    {
    //  cout << s << endl;
      cnt++;
      md5_digest(s, N, digest);
      if( findMatch(vstr, digest) )
      {
        cout << s << endl;
        for( int i = 0; i < 16; i++ )
          printf("%02x", (unsigned int)digest[i]);
        return 1;
      }
    }
    return 0;
  }

  for( char j = 32; j < 127; j++ )
  {
    int curFlag = GenFlag(j);
    if( !curFlag )
      continue;
    curFlag = curFlag | flag;
    int bitCount = CountBit(curFlag);
    if( end - start < 4 - bitCount )
      continue;
    *start = j;
    gen_all_permutations(start+1, end, curFlag);
  }

  return 0;
}

int HexToInt(char c)
{
  if( c >= '0' && c <= '9' )
    return c - '0';
  else
    return c - 'a' + 10;
}

int HexToBytes(const char* str, int len, unsigned char* pstr)
{
  for( int i = 0; i < len/2; i++ )
  {
    unsigned char bt = HexToInt(str[2*i]) * 16 + HexToInt(str[2*i+1]);
    *(pstr + i) = bt;
  }

  return 0;
}


vector<const unsigned char *> read_file(const char *fileName)
{
  ifstream fin;
  char str[33];
  fin.open(fileName, ifstream::in);
  vector <const unsigned char *> vstr;
  while( fin >> str )
  {
    unsigned char *pstr = new unsigned char[16];
    int len = strlen(str);

    assert( len == 32 );
    HexToBytes(str, len, pstr);
    vstr.push_back(pstr);
  }
  return vstr;
}

int findMatch(const vector<const unsigned char *>& vmd5,
              const unsigned char* md5Digest)
{
  for( int i = 0; i < (int)vmd5.size(); i++ )
  {
    bool flag = true;
    for( int j = 0; j < 16; j++ )
    {
      if( vmd5[i][j] != md5Digest[j] )
      {
        flag = false;
        break;
      }
    }
    if( flag )
      return 1;
  }
  return 0;
}

int md5_digest(const char* text, int len, unsigned char* md5Digest)
{
  MD5((unsigned char*) text, len, md5Digest);
  return 0;
}

int testMd5()
{
  md5_digest("AAA", 3, digest);
  unsigned char str[20];
  HexToBytes("e1faffb3e614e6c2fba74296962386b7", 32, str);
  bool flag = true;
  for( int i = 0; i < 16; i++ )
  {
    cout << (unsigned int)digest[i] << endl;
    cout << (unsigned int) str[i] << endl;
    cout << endl;
    if( digest[i] != str[i] )
    {
      flag = false;
      break;
    }
  }
  if( flag )
    cout << "Yes, they match";
  return 0;
}

int main ()
{
  cout << "Number of characters: \n";
  cin >> N;
  if( N > 6 )
  {
    cout << "This will take too long. Aborting...\n";
    return 0;
  }
  else if( N <= 0 )
  {
    cout << "Number of characters should be 1-6\n";
    return 0;
  }
  vstr = read_file("md5.txt");
  gen_all_permutations(s, s+N-1, 0);
  return 0;
}
