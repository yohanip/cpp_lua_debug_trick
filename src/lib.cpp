extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
}
#include <raylib.h>

int add(int a, int b) {
    return a + b;
}

static int lua_add(lua_State *L) {
    auto a = luaL_checknumber(L, 1);
    auto b = luaL_checknumber(L, 2);
    lua_pushnumber(L, add(a, b));
    return 1;
}

static int lua_InitWindow(lua_State *L) {
    auto width = luaL_checkinteger(L, 1);
    auto height = luaL_checkinteger(L, 2);
    auto title = luaL_checkstring(L, 3);
    InitWindow(width, height, title);
    return 1;
}

static int lua_WindowShouldClose(lua_State *L) {
    lua_pushboolean(L, WindowShouldClose());
    return 1;
}

static int lua_BeginDrawing(lua_State *L) {
    BeginDrawing();
    return 1;
}

static int lua_EndDrawing(lua_State *L) {
    EndDrawing();
    return 1;
}

static int lua_ClearBackground(lua_State *L) {
    auto color = (Color*)lua_touserdata(L, 1);
    if (color) {
        ClearBackground(*color);
    } else {
        lua_pushstring(L, "Color not specified");
        lua_error(L);
    }
    return 1;
}

static int lua_DrawText(lua_State *L) {
    auto text = luaL_checkstring(L, 1);
    auto x = luaL_checkinteger(L, 2);
    auto y = luaL_checkinteger(L, 3);
    auto size = luaL_checkinteger(L, 4);
    auto color = (Color*)lua_touserdata(L, 5);

    if (color) {
        DrawText(text, x, y, size, *color);
    } else {
        lua_pushstring(L, "Color not specified");
        lua_error(L);
    }
    return 1;
}

static int lua_CloseWindow(lua_State *L) {
    CloseWindow();
    return 1;
}

static int lua_IsKeyDown(lua_State *L) {
    lua_pushboolean(L, IsKeyDown(luaL_checkinteger(L, 1)));
    return 1;
}

static int lua_IsKeyPressed(lua_State *L) {
    lua_pushboolean(L, IsKeyPressed(luaL_checkinteger(L, 1)));
    return 1;
}

static const luaL_Reg funcs[] = {
    {"add", lua_add},
    {"InitWindow", lua_InitWindow},
    {"WindowShouldClose", lua_WindowShouldClose},
    {"ClearBackground", lua_ClearBackground},
    {"DrawText", lua_DrawText},
    {"BeginDrawing", lua_BeginDrawing},
    {"EndDrawing", lua_EndDrawing},
    {"CloseWindow", lua_CloseWindow},
    {"IsKeyDown", lua_IsKeyDown},
    {"IsKeyPressed", lua_IsKeyPressed},

    {NULL, NULL}
};

extern "C" int luaopen_libraylib_lua(lua_State *L) {
    // if we wanted to do raylib.some function then this is the code
    // luaL_newlib(L, funcs);
    // but i like to populate the global :p
    lua_pushglobaltable(L);
    luaL_setfuncs(L, funcs, 0);

    lua_pushinteger(L, KEY_LEFT_CONTROL);
    lua_setglobal(L, "KEY_LEFT_CONTROL");

    lua_pushinteger(L, KEY_R);
    lua_setglobal(L, "KEY_R");

    {
        auto color = (Color*)lua_newuserdata(L, sizeof(Color));
        *color = BLACK;
        lua_setglobal(L, "BLACK");
    }

    {
        auto color = (Color*)lua_newuserdata(L, sizeof(Color));
        *color = WHITE;
        lua_setglobal(L, "WHITE");
    }

    {
        auto color = (Color*)lua_newuserdata(L, sizeof(Color));
        *color = RED;
        lua_setglobal(L, "RED");
    }

    return 1;
}