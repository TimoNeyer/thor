# Thor programming language

## Summary:

The Thor programming language is aimed to be a simplified version of c with the same
syntax. Therefore is has the same type of usecases, but it introduces some other ideas
like: [Garbage collector](#garbage-collector-heimdall), [dynamic strings](#dynamic-strings)
with automatic formating and a [python style importing syntax](#new-import-syntax) alongside the c style one


### Garbage collector Heimdall

This garbage collector will be optional for functions and variables with a syntax like

> Variables:
> @heimdall int var;
> @gc int var;  

> Functions:
> @heimdall int main();
> @gc int main(); 

### Dynamic Strings

The dynamic strings will support not only concatenation, but also multiple formats.
The syntax for a char will be replaced with the normal string, the normal string with the auto
formating with variables. the \`string\` characters will be used for raw strings, which can 
have all kinds of values. In format strings to display a { or } you need to escape this.
It also introduces the print function which optionally adds a `pre` and a `post`
(which defaults to newline) to the printed output but does not format it.
There is the new `str` keyword added as well for dynamic strings, alongside char
arrays for more constant and less requirering strings.

> int var1 = 4; 
>
> printf("var1: {var1})";
 var1: 4

> int var1 = 4;
>
> printf('var1: \{var1\})" or printf('var1: {var1}');
var1: {var1}

> str var1 = \`\//ehlo\`;
>
> printf(var1);
\//ehlo

###  New import syntax

To import other Thor files, it is possible to use the keywords import, from and as.

> from module.file import function as name
