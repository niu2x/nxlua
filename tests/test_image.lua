local a = Image:new_local()
a:load("./1.png")

local b = Image:new_local()

b:resize(  a:height(), a:width())

-- local transform = ImageTransform()
-- transform = transform:mul(ImageTransform:translate(-b:width()/2, -b:height()/2)) 
-- transform = transform:mul(ImageTransform:rotate(-math.pi/2)) 
-- transform = transform:mul(ImageTransform:translate(a:width()/2, a:height()/2)) 

-- Image:resample(a, 0, 0, a:width(), a:height(), 
-- b, 0, 0, b:width(), b:height(), transform)


b:save('./3.png')