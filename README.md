##Simple, Lightweight Logging

Usage:


Specify a filename when constructing:

```c++
Logger example("FILENAME");
```

Log lines will be written to this file. Use the << operator to 
direct messages to the log stream and indicate the log level. 
If the log level is omitted, it defaults to verbose:

```c++
example << ERROR << "Out of Memory!" << std::endl;
```


This line will look like this in the log file:

```
Sat Mar 15 08:06:58 2014 -- [ERROR] -- Out of Memory!
```

If you dont care for the formatting, change the code :)


You must end the line with an endl. This tells the logger 
to write the line and prepend the timestamp to the line 
as well. 


You can change the logging level like so:

```c++
example.set_level(VERBOSE);
```

The level defaults to INFO is one is never set.


Note: This library requires C++11 compiler support
