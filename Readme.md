# Thor programming language

## Summary:

The thor programming language will be aimed to bridge the gap between user friednliness
of languages like python and the versatility of C and an easy to parse Syntax, as this
will be my first programming language

### Garbage collector Heimdall

This garbage collector will be optional for functions and variables with a syntax like

 Variables:
~~~
 new @heimdall int var;

 new @gc int var;  
~~~

 Functions:

~~~
 new @heimdall int main();

 new @gc int main(); 
 ~~~

Alongside that there will be the keyword `yield` which will be similar to the return statement,
but with the key difference that the returned object will be allocated in memory and returned 
by value. Implies @gc for the variable


### Dynamic Strings

The dynamic strings will support not only concatenation, but also multiple formats.
The syntax for a char will be replaced with the normal string, the normal string with the auto
formating with variables. the \`string\` characters will be used for raw strings, which can 
have all kinds of values. In format strings to display a { or } you need to escape this.
It also introduces the print function which optionally adds a `pre` and a `post`
(which defaults to newline) to the printed output but does not format it.
There is the new `str` keyword added as well for dynamic strings, alongside char
arrays for more constant and less requirering strings.

~~~
...

new int var1 = 4; 

printf("var1: {var1})";

# >> var1: 4

new int var1 = 4;

printf("var1: \{var1\}"); 
printf('var1: {var1}');

# > var1: {var1}
# > var1: {var1} 

new str var1 = `\//ehlo\`;

printf(var1);

\//ehlo
~~~

###  New import syntax

To import other Thor files, it is possible to use the keywords import, from and as.

``` from module[.file] import function as name```

It is possible to use `import [library (other thor file or c library)] as None.

This leads to importing without the need to prepend any module name. Otherwise it 
is necessary to use `:` to mark the use of a module.

```
import stdlib as None;

import stdio 

new int random = rand()

stdio:print("something");

```

### `new` to define variables and classes

```
 new int x;

 x = 3;

 new class Type{}
 ```
   

### when executing, specify entrypoint, if not `main` is used

` thor run -e [function_name] [directory/file]`

or simply ` thor run .` to compile a project in the current folder with the entrypoint 
called `main`

## example:
```
 #!/bin/thor run -e entrypoint . 

import stdio as None;

 new int function(arg:str){
   
       new int a = 9;
 
       print("a = {a}");

       print("arg = {arg}");

   }

   new int entrypoint(){
       function("ehlo");
   }
```

Compiled with `thor run -e entrypoint test.th` or `thor run -e entrypoint .` if 
it is the only thor file in the current directory



## More advanced example
```
   import stdio as std

   new class MyClass{
       
    new void __init__(cls){
           new int cls.default = 1;
           std:print("default value is {cls.default}");
       }

       new void classmethod(cls){
           std:nop()
       }
   }
   ```
