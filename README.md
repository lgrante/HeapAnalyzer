Welcome file.html

# My own malloc implementation

## 1\. How to use?

Follow these steps to replace my malloc by the malloc from the C standard library (it will be replaced only during execution time).

1.  Enter command “make”  
    `$ make`
    
2.  Then you just have to set LD_PRELOAD environment variable and run your executable:  
    `$ LD_PRELOAD=$PWD/libmy_malloc.so [your_executable]`  
    **Example**  
    `$ LD_PRELOAD=$PWD/libmy_malloc.so ls` This will run ls command with my malloc implementation.
    

An that’s all!

## 2\. Have a look on your heap!

It’s possible to see every block on your page during program execution using my malloc implementation. Use this flag to compile malloc with debug mode:  
`make debug`  
Then if you execute your programm with malloc (as shown before) you will see something like that as output:

[![debug-mode-output.png](https://i.postimg.cc/s2Nx0T6S/debug-mode-output.png)](https://postimg.cc/hJVKX1qP)

You can also choose how many block to dispay. You just have to prodive these arguments to `make debug` command:

**Example**

`$ make debug block-nb=50` If you compile malloc with these command the debug mode will display 50 block of memory.  
Have fun!

