"""
Check if a give character is a vowel

>>> is_vowel('a')
True
>>> is_vowel('b')
False

Check if a give string is a palindrome

>>> is_palindrome('radar')
True
>>> is_palindrome('help')
False

Get the -ing form for a given verb

>>> make_ing_form('go')
'going'
>>> make_ing_form('lie')
'lying'
>>> make_ing_form('move')
'moving'
>>> make_ing_form('bet')
'betting'
"""

VOWELS = "aeiou"

def is_vowel(ch):
    return ch.lower() in VOWELS

def is_palindrome(string):
    return string == string[::-1]

def make_ing_form(verb):
    if verb.endswith('ie'):
        return verb[:-2] + 'ying'
    if verb.endswith('e') and (verb[-2].endswith('e') or len(verb) == 2):
        return verb + 'ing'
    if verb.endswith('e'):
        return verb[:-1] + 'ing'
    try:
        if (verb[-3] not in VOWELS) and (verb[-2] in VOWELS) and (verb[-1] not in VOWELS):
            return verb + verb[-1] + 'ing'
    except IndexError:
        pass
    return verb + 'ing' 

