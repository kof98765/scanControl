#include "lua.h"

lua::lua()
{
    l=luaL_newstate();
    luaL_openlibs(l);

}
void lua::load(char *name,int w,int h)
{

}
