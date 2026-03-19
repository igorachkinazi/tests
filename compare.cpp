#include <vector>
#include <map>
#include <utility>
#include <iostream>

typedef std::vector<std::pair<std::string,unsigned int>> discoveryContainer;


bool IsNewUpdate(discoveryContainer& ctx1, discoveryContainer& ctx2)
{
    if(ctx1.size() != ctx2.size())
        return true;

    for(auto ctxaddr : ctx1) {
        bool found  = false;
        for(auto sysaddr : ctx2) {
            if (ctxaddr.first == sysaddr.first && ctxaddr.second == sysaddr.second) {
                found = true;
                break;
            }
        }
        if(!found)
            return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
   (void)argc;
   (void)argv;

   discoveryContainer ctx1;
   discoveryContainer ctx2;

   ctx1.push_back(std::make_pair("127.0.0.2", 8009));
   ctx1.push_back(std::make_pair("127.0.0.3", 8009));
   ctx2.push_back(std::make_pair("127.0.0.2", 8009));
   ctx2.push_back(std::make_pair("127.0.0.3", 8009));
   ctx2.push_back(std::make_pair("127.0.0.1", 8009));


   std::cout << (IsNewUpdate(ctx1,ctx2) ? "update" : "same") << std::endl;
}

