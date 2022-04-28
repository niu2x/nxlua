function math.clamp(value, min, max)
	value = math.min(value, max)
	value = math.max(value, min)
	return value
end

---
function math.rad2deg(rad)
	return rad/math.pi*180
end

---
function math.deg2rad(deg)
	return deg/180*math.pi
end

---
function math.sign(num)
	if num > 0 then
		return 1
	elseif num < 0 then
		return -1
	else
		return 0
	end
end
