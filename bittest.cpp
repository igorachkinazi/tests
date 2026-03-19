#include <bitset>
#include <cstddef>
#include <cstring>
#include <iostream>
 
int main()
{
   unsigned char bitbuf[1024];

   memset(bitbuf, 0, sizeof(bitbuf));
   std::bitset<8192> prefethBits(bitbuf);

   prefethBits[5] = 1;
   if(prefethBits[5])
       prefethBits[7] = 1;

   std::cout << (int)bitbuf[0] << '\n';
}
