"""
### START: import
>>> import lang
>>> lang.is_vowel('a')
True

### END: import
### START: import-assign
>>> import lang
>>> is_vowel = lang.is_vowel
>>> is_vowel('a')
True

### END: import-assign
### START: import-from
>>> from lang import is_vowel
>>> is_vowel('a')
True

### END: import-from
### START: standard
>>> import calendar
>>> c = calendar.TextCalendar()
>>> print(c.formatmonth(1947, 8))
    August 1947
Mo Tu We Th Fr Sa Su
...

### END: standard
### START: package
>>> import utils.lang
>>> utils.lang.is_vowel('a')
True

### END: package
"""
