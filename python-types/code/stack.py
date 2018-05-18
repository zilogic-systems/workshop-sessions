"""
### START: grow
>>> stack = []
>>> stack.append('a')
>>> stack
['a']
>>> stack.append('b')
>>> stack
['a', 'b']
>>> stack.append('c')
>>> stack
['a', 'b', 'c']

### END: grow
### START: shrink
>>> stack
['a', 'b', 'c']
>>> stack.pop()
'c'
>>> stack
['a', 'b']
>>> stack.pop()
'b'
>>> stack
['a']

### END: shrink
"""
