#ifndef LUA_H
#define LUA_H
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

}
class lua
{
public:
    lua();
    void load(char *name,int w,int h);
private:
    int status,result;
    lua_State *l;
};

#endif // LUA_H
