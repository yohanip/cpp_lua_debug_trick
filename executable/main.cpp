#include "../src/lib.hpp"
#include <iostream>
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

void add_lua_path(lua_State* L, const char *which, const char* new_path) {
    // package
    lua_getglobal(L, "package");

    // package.cpath
    lua_getfield(L, -1, which);

    // new_cpath = old .. ";" .. new_path
    const char* old_path = lua_tostring(L, -1);
    lua_pop(L, 1);

    lua_pushfstring(L, "%s;%s", old_path, new_path);
    lua_setfield(L, -2, which);

    lua_pop(L, 1); // pop package
}

static int msghandler (lua_State *L) {
    const char *msg = lua_tostring(L, 1);
    if (msg == NULL) {  /* is error object not a string? */
        if (luaL_callmeta(L, 1, "__tostring") &&  /* does it have a metamethod */
            lua_type(L, -1) == LUA_TSTRING)  /* that produces a string? */
        return 1;  /* that is the message */
        else
        msg = lua_pushfstring(L, "(error object is a %s value)",
                                luaL_typename(L, 1));
    }
    luaL_traceback(L, L, msg, 1);  /* append a standard traceback */
    return 1;  /* return the traceback */
}

static int docall (lua_State *L, int narg, int nres) {
    int status;
    int base = lua_gettop(L) - narg;  /* function index */
    lua_pushcfunction(L, msghandler);  /* push message handler */
    lua_insert(L, base);  /* put it under function and args */
    status = lua_pcall(L, narg, nres, base);
    lua_remove(L, base);  /* remove message handler from the stack */
    return status;
}

int main() {
    std::cout << add(1, 2) << std::endl;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    add_lua_path(L, "cpath", "install/lib/?.so");
    add_lua_path(L, "path", "scripts/?.lua");
    luaL_loadfile(L, "scripts/main.lua");
    auto status = docall(L, 0, 0);

    if (status != LUA_OK) {
        auto msg = lua_tostring(L, -1);
        if (msg) {
            std::cerr << msg << std::endl;
        }
    }

    lua_close(L);
}