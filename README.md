# neural-network
a library for making neural networks

This library was written in C++ by me, NUMBUKU, and depends heavily on two other C libraries I wrote.
It also uses some standard libraries: stdio, stdlib, math and iostream. This particular
file is for defining a neural network and the neuron.h file is for defining a neuron and some methods
that go with that. I got most of my knowledge from this playlist: 
https://youtube.com/playlist?list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi by 3Blue1Brown and this video: 
https://www.youtube.com/watch?v=dPWYUELwIdM by freeCodeCamp.org, I heavily recommend watching those videos
so you can understand what the library is actually doing. I also want to say that I am not a professional
programmer and that most of the things I wrote here might be horribly inefficient, so if you find any
flaws, please notify me and I will try to fix them.

The library works as the following. To define a new neural network use: 
"neural_net 'the name of your net'(number of collumns, number of rows, number of inputs, number of outputs);".
To calculate the output use: "'the name of your net'.calc_out(the list of inputs);". To calculate how bad
the net performed use: "'the name of your net'.calc_cost(the list of the wanted outputs);". To try to 
improve the net's performance use: 
"'the name of your net'.improve(the list of the wanted outputs, how much it is allowed to change the parameters);"
The namespace is "net::neural_net::".

To include the file have it in the same folder and type: '# include "neural_net.h"'.

That's it, I hope you learn something.
