#include <stdio.h>
#include <string.h>

int main()
{
   char instr[] = "traddr=127.0.0.3,trsvcid=4420\n";
   char traddr[32], trport[16];

   instr[strcspn(instr, ",")] = ' ';

   sscanf(instr, "traddr=%s trsvcid=%s", traddr, trport);

   printf("traddr: %s\n", traddr);
   printf("strlen traddr %d\n", strlen(traddr));
   printf("trport: %s\n", trport);
   printf("strlen trport %d\n", strlen(trport));

   return 0;
}
