local text = 'hello WORLD'

-- low level api 

local md5 = pipe.pipe(text, pipe.filter.digest_t('md5'))
print('md5', md5)

local md5_hex = pipe.pipe(md5, pipe.filter.hex_t())
print('md5_hex', md5_hex)

local sha1 = pipe.pipe(text, pipe.filter.digest_t('sha1'))
print('sha1', sha1)

local sha1_hex = pipe.pipe(sha1, pipe.filter.hex_t())
print('sha1_hex', sha1_hex)


local upper = pipe.pipe(text, pipe.filter.upper_t())
print('upper', upper)

local lower = pipe.pipe(text, pipe.filter.lower_t())
print('lower', lower)


local key = string.rep('0', 32)
local iv = string.rep('0', 16)

local aes256 = pipe.pipe(text, pipe.filter.encrypt_t('aes256', key, iv))
print('aes256 encrypt', aes256)

local un_aes256 = pipe.pipe(aes256, pipe.filter.decrypt_t('aes256', key, iv))
print('aes256 decrypt', un_aes256)


-- high level api

print('md5', pipe.pipe(text, "digest(md5)"), '')
print('md5_hex', pipe.pipe(text, "digest(md5)|hex"), '')
print('sha1', pipe.pipe(text, "digest(sha1)"), '')
print('sha1_hex', pipe.pipe(text, "digest(sha1)|hex"), '')
print('upper', pipe.pipe(text, "upper"), '')
print('lower', pipe.pipe(text, "lower"), '')

print('aes256 encrypt', pipe.pipe(text, "encrypt(aes256, 00000000000000000000000000000000, 0000000000000000)"), '')
print('aes256 decrypt', pipe.pipe(text, "encrypt(aes256, 00000000000000000000000000000000, 0000000000000000)|decrypt(aes256, 00000000000000000000000000000000, 0000000000000000)"), '')
