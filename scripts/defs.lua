---@meta

---@class Color
Color = {}

---@type integer
KEY_LEFT_CONTROL = 0

---@type integer
KEY_R = 0

---@type Color
BLACK = {}
---@type Color
WHITE = {}
---@type Color
RED = {}

function add(a, b) end
function InitWindow(width, height, title) end
function WindowShouldClose() end
function ClearBackground(color) end
function DrawText(text, x, y, size, color) end
function BeginDrawing() end
function EndDrawing() end
function CloseWindow() end
function IsKeyDown(key) end
function IsKeyPressed(key) end