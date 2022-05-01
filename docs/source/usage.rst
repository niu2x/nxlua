Usage
=====

Install
------------
Download prebuild binaries from https://github.com/niu2x/nxlua/releases.

Examples
------------

Hello world
~~~~~~~~~~~~
.. code-block:: lua

   print('Hello World')

md5
~~~~~~~~~~~~
.. code-block:: lua
   
   local md5 = pipe.pipe('Hello World', 'digest(md5)|hex')
   print(md5)

sha256
~~~~~~~~~~~~
.. code-block:: lua
   
   local sha256 = pipe.pipe('Hello World', 'digest(sha256)|hex')
   print(md5)


aes-128-cbc
~~~~~~~~~~~~
.. code-block:: lua
   
   local key = string.rep('A', 32)
   local iv = string.rep('B', 16)

   local e = pipe.pipe('Hello World', string.format('encrypt(aes-128-cbc, %s, %s)', key, iv))
   print(e)

   local d = pipe.pipe(e, string.format('decrypt(aes-128-cbc, %s, %s)', key, iv))
   print(d)