package.loaded["inner_update"] = nil
local inner_update = require("inner_update")

local update = {}

function update.update()
    DrawText("Hello LUA, i love you!", 0, 0, 20, BLACK)
    inner_update()
end

return update