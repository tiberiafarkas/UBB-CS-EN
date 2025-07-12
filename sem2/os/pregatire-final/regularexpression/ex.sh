#!/bin/bash
1.Match words containing exactly 5 characters.
^[a-zA-Z]{5}$ - inceput de linie/5 caractere/sf de linie
( |^)+[a-zA-Z]{5}( |$) - spatiu sau inceput de linie/5 caractere/spatiu sau sfarsit de linie

2. Match words containing exactly 4 characters with the first two of them being 'lo'.
\b(lo){1}[a-zA-Z]{2}\b

3. Match all words containing at least 10 characters.
\b+[a-zA-Z]{10,}\b

4. Match words starting with the negative prefix un-.
\b(un)[a-zA-Z]+\b

5. Match words starting with one of the following negative prefixes: im-, in-
\b((im)|(in))[a-zA-Z]+\b

6. Match words ending with the suffix -less.
\b[a-zA-Z]*(less)\b

7. Match words consisting of lower-case letters only.
\b[a-z]+\b

8. Match acronyms, i.e. words consisting of capital letters only.
\b[A-Z]+\b

9. Match acronyms containing at least 2 capital characters. ??
\b(.*[A-Z]+.*){2,}\b

10. Match possessive nouns/pronouns 'in' singular.
\b.+('s){1}\b   '

11. Match years from the 18. century.
\b(17)[0-9]{2}\b

12. Match adjectives in the following format '17-year-old'.
\b[0-9]+(-[a-z]+-[a-z]+)\b

13. Match numbers followed by a full stop (dot).
\b[0-9]+\.

14. Match one or more questioning marks.
[?]+

15. Match possessive nouns both in singular and plural.
\b.+(('s)|(s'))\b

16. Match possessive nouns created from proper nouns, i.e. starting with a capital letter.
\b([A-Z]{1}[a-z]+('s))\b         ' 

17. Match words containing the string 'blah' at least twice.
\b.*(blah){2,}.*\b

18. Match URLs from the .org domain.
(http){1}(s)?(://www.).+(\.org)

19. Match phone numbers starting with the country code +420.
(\+420)( [0-9]{3}){3}

20. Match words starting with a number.
\b[0-9]+.+\b

21. Match words starting with co- such as the following:
\b(co).+\b

22. Match words consisting of the same letter repeating exactly 3 times.
\b([a-zA-Z]){3}\b

23. Match words containing three characters, where the first and last character are the same.
\b([a-zA-Z]){1}.{1}\1{1}\b
