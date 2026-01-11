local boom = "BOOM!!!!"

return function ()
    DrawText(
        string.format("Inner update says: %s", boom),
        50, 100, 20, RED
    )
end