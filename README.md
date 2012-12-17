integer
=======

Simple C++ binding of GNU Multiple Precision Arithmetic Library Integers.


Dependencies
------------

This library depends on several things. First one is programming language whih is __C++11__. Second one is [__GNU Multiple Precision Arithmetic Library__](http://gmplib.org/). `integer.yaml.hpp` requires also [__yaml-cpp__](http://code.google.com/p/yaml-cpp/) installed. `Integer::Random()` uses `/dev/urandom` file so it would be great if it will exists.

How to build?
-------------

The answer is: _no build needed_, because all off functions are inline in cause of their siplicity.

How to install?
---------------

At this moment there is no any Makefile so if you want install this library you should manyually call the following command:
    install *.hpp /usr/local/include/

How to use?
-----------

    #include <integer.hpp>
