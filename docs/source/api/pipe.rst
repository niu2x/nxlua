pipe
====

Purpose
-------

Transform **input str** by various **filter**.

Support pipe style.

Eample
--------

**output** = hex str of **input str**'s  md5


Low Level API Usage
~~~~~~~~~~~~~~~~~~~

.. code-block:: lua

	local md5_filter = pipe.filter.digest_t('md5')
	local hex_filter = pipe.filter.hex_t()
	local output = pipe.pipe(input, md5_filter)
	output = pipe.pipe(output, hex_filter)


High Level API Usage
~~~~~~~~~~~~~~~~~~~~

.. code-block:: lua

	local output = pipe.pipe(input, 'digest(md5)|hex')


Filters
-------

pipe.filter.hex_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.unhex_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.lower_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.upper_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.base64_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.unbase64_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.zlib_t(level)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- level: compress level

pipe.filter.unzlib_t()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


pipe.filter.digest(algorithm)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- algorithm: digest algorithm name
	- blake2b512
	- blake2s256
	- md5
	- md5-sha1
	- sha1
	- sha224
	- sha256
	- sha3-224
	- sha3-256
	- sha3-384
	- sha3-512
	- sha384
	- sha512
	- sha512-224
	- sha512-256
	- shake128
	- shake256
	- sm3
	- ssl3-md5
	- ssl3-sha1

pipe.filter.encrypt_t/decrypt_t(algorithm, key, iv)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- key: key
- iv: iv
- algorithm: algorithm name
	- aes-128-cbc
	- aes-128-cfb
	- aes-128-cfb1
	- aes-128-cfb8
	- aes-128-ctr
	- aes-128-ecb
	- aes-128-ofb
	- aes-192-cbc
	- aes-192-cfb
	- aes-192-cfb1
	- aes-192-cfb8
	- aes-192-ctr
	- aes-192-ecb
	- aes-192-ofb
	- aes-256-cbc
	- aes-256-cfb
	- aes-256-cfb1
	- aes-256-cfb8
	- aes-256-ctr
	- aes-256-ecb
	- aes-256-ofb
	- aes128
	- aes192
	- aes256
	- aria-128-cbc
	- aria-128-cfb
	- aria-128-cfb1
	- aria-128-cfb8
	- aria-128-ctr
	- aria-128-ecb
	- aria-128-ofb
	- aria-192-cbc
	- aria-192-cfb
	- aria-192-cfb1
	- aria-192-cfb8
	- aria-192-ctr
	- aria-192-ecb
	- aria-192-ofb
	- aria-256-cbc
	- aria-256-cfb
	- aria-256-cfb1
	- aria-256-cfb8
	- aria-256-ctr
	- aria-256-ecb
	- aria-256-ofb
	- aria128
	- aria192
	- aria256
	- camellia-128-cbc
	- camellia-128-cfb
	- camellia-128-cfb1
	- camellia-128-cfb8
	- camellia-128-ctr
	- camellia-128-ecb
	- camellia-128-ofb
	- camellia-192-cbc
	- camellia-192-cfb
	- camellia-192-cfb1
	- camellia-192-cfb8
	- camellia-192-ctr
	- camellia-192-ecb
	- camellia-192-ofb
	- camellia-256-cbc
	- camellia-256-cfb
	- camellia-256-cfb1
	- camellia-256-cfb8
	- camellia-256-ctr
	- camellia-256-ecb
	- camellia-256-ofb
	- camellia128
	- camellia192
	- camellia256
	- chacha20
	- des3
	- sm4
	- sm4-cbc
	- sm4-cfb
	- sm4-ctr
	- sm4-ecb
	- sm4-ofb
