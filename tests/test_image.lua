local a = Image:new_local()
a:load("./1.png")
print(a:save("./r0.png"))

local b = a:crop(0, 0, 256, 256)
b:save('./r1.png')

local c = Image:new_local()
c:resize(1024, 1024)
c:fill(255, 0, 0, 0)
c:save("./r2.png")

local d = a:rotate(math.pi/6)
d:save("./r3.png")

local e = a:scale(0.3)
e:save("./r4.png")

a:draw(d:scale(0.3), 0, 0)

a:save("./r5.png")