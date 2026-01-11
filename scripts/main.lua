require("libraylib_lua")
local update = require("update")

InitWindow(400, 400, "Hello Lua!")

local script_error = nil

local function reload_update_script()
    package.loaded["update"] = nil
    update = require("update")
end

while not WindowShouldClose() do
    if IsKeyDown(KEY_LEFT_CONTROL) and IsKeyPressed(KEY_R) then
        print("==> Reloading update.lua")
        script_error = nil
        local status, err = pcall(reload_update_script)
        if not status then
            script_error = err
            print(err)
        end
    end

    BeginDrawing()

    if not script_error then
        ClearBackground(WHITE)
        if update.update then
            local status, err = pcall(update.update)
            if not status then
                script_error = err
                print(err)
            end
        end
    else
        ClearBackground(RED)
        DrawText(script_error, 5, 5, 10, WHITE)
    end

    EndDrawing()
end

CloseWindow()