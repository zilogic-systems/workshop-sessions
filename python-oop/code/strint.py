"""
### START: to-int
>>> int("987")
987
>>> int("A", 16)
10

### END: to-int
### START: format
>>> '{0}'.format(16)
'16'
>>> '{0}-{1}-{2}'.format(12, 10, 17)
'12-10-17'
>>> '{1}-{0}-{2}'.format(12, 10, 17)
'10-12-17'
>>> '{0:X},{1:X}'.format(16, 10)
'10,A'

### END: format
### START: pad-align
>>> '{0:4X},{1:4X}'.format(16, 10)
'  10,   A'
>>> '{0:<4X},{1:<4X}'.format(16, 10)
'10  ,A   '
>>> '{0:^4X},{1:^4X}'.format(16, 10)
' 10 , A  '

### END: pad-align
### START: fill
>>> '{0:.>4X},{1:.>4X}'.format(16, 10)
'..10,...A'
>>> '{0:0>4X},{1:0>4X}'.format(16, 10)
'0010,000A'

### END: fill
"""
