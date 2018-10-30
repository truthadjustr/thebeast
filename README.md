# thebeast
test
test2
test3

|Size |Additional|Data Size
|Index|bits      |
|-----|----------|---------------
|0    |0         |1 byte. Exception: if the data element type is nil, the
|     |          |data size is 0 bytes.
|1    |0         |2 bytes
|2    |0         |4 bytes
|3    |0         |8 bytes
|4    |0         |16 bytes
|5    |8         |The data size is contained in the additional 8 bits,
|     |          |which are interpreted as an unsigned integer.
|6    |16        |The data size is contained in the additional 16 bits,
|     |          |which are interpreted as an unsigned integer.
|7    |32        |The data size is contained in the additinal 32 bits,
|     |          |which are interpreted as an unsigned integer
