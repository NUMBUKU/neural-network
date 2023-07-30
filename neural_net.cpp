/*
    This library was written in C++ by me, NUMBUKU, and depends heavily on two other C libraries I wrote.
    It also uses some standard libraries: stdio, stdlib, math, iostream, cstdlib and ctime. This particular
    file is for defining a neural network and the neuron.h file is for defining a neuron and some methods
    that go with that. I got most of my knowledge from this playlist: 
    https://youtube.com/playlist?list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi by 3Blue1Brown and this video: 
    https://www.youtube.com/watch?v=GVsUOuSjvcg by Veritasium, I heavily recommend watching those videos so
    you can understand what the library is actually doing. I also want to say that I am not a professional
    programmer and that most of the things I wrote here might be horribly inefficient, so if you find any
    flaws, please notify me and I will try to fix them.

    The library works as the following. To define a new neural network use: 
    "neural_net 'the name of your net'(number of collumns, number of rows, number of inputs, number of outputs);".
    To calculate the output use: "'the name of your net'.calc_out(the list of inputs);". To calculate how bad
    the net performed use: "'the name of your net'.calc_cost(the list of the wanted outputs);". To try to 
    improve the net's performance use: 
    "'the name of your net'.improve(the list of the wanted outputs, how much it is allowed to change the parameters);"
    The namespace is "net::neural_net::".

    That's it, I hope you learn something.
*/

# include <iostream>
# include <cstdlib>
# include <ctime>
# include <neuron.h>

namespace net{
class neural_net{
    private:
        // variables for the sizes of the network
        unsigned int col, inputs, outputs, rows;
        node * outl = newList();
        double out;
        neuron * net = new neuron [neural_net::col, neural_net::rows];
        neuron * outn = new neuron [outputs];

        // method for changing the previous activation
        void change_previous (int collumn, double avia, double share){
            // for (int x = collumn; x > 0; x--){
                for (int y = 0; y < neural_net::rows; y++){
                    //task: make something that can return the actual ia and not just the avia
                    node * impact = calc_impact(neural_net::net[collumn, y].prevact, neural_net::net[collumn, y].wgt, neural_net::outn[collumn, y].bias, neural_net::outn[collumn, y].act + avia);
                    double avib = atIndex(impact, 0);
                    double aviw = atIndex(impact, 1);
                    double avia1 = atIndex(impact, 2);
                    double constant = share/(abs(avib) + abs(aviw) + abs(avia1));
                    neural_net::outn[collumn, y].bias += constant * avib;
                    for (int m = 0; m < len(neural_net::outn[collumn, y].wgt); m++){
                        changeAtIndex(neural_net::outn[collumn, y].wgt, m, atIndex(neural_net::outn[collumn, y].wgt, m) + (constant * aviw));
                    }
                    if (collumn != 1){
                        change_previous(collumn-1, avia1, constant * avia1); // recursion for changing the activation before this
                    }
                }
            // }

            return;
        }
    public:
        //constructor
        neural_net (unsigned int collums, unsigned int rows, unsigned int outputs, unsigned int inputs){
            if (collums == 0 || rows == 0 || outputs == 0 || inputs == 0){
                throw "Invalid parameter, the parameters must be greater than zero.";
            } else {
                neural_net::col = collums;
                neural_net::rows = rows;
                neural_net::outputs = outputs;
                neural_net::inputs = inputs;
                for (int i = 0; i < neural_net::col; i++){
                    for (int j = 0; j < neural_net::rows; j++){
                        for (int k = 0; k < neural_net::inputs; k++){
                            app(neural_net::net[i, j].wgt, ((rand() % 200)/200) - 100); // assigning random values for weights and biasses
                        }
                        neural_net::net[i, j].bias = ((rand() % 2000)/200) - 1000;
                    }
                }
                for (int l = 0; l < neural_net::outputs; l++){
                    outn[l].bias = ((rand() % 2000)/200) - 1000;
                    for (int m = 0; m < neural_net::rows; m++){
                        app(neural_net::outn[l].wgt, ((rand() % 200)/200) - 100);
                    }
                }
            }
        }

        //public methods
        double calc_out (node * input){ // method for calculating the output, stores the list of outputs in neural_net::outl and stores the highest number in that list in neural_net::out
            node ** middle = new node * [neural_net::rows];
            for (int i = 0; i < neural_net::col; i++){
                switch (i){
                    case 0: // first layer
                        for (int j = 0; j < neural_net::rows; j++){
                            app(middle[i], calc_act(input, neural_net::net[0, j].wgt, neural_net::net[0, j].bias));
                        }
                        break;
                    default:
                        if (i == neural_net::col-1){ // last layer
                            for (int j = 0; j < neural_net::outputs; j++){
                                app(neural_net::outl, calc_act(middle[i-1], neural_net::outn[0, j].wgt, neural_net::outn[0, j].bias));
                            }
                            neural_net::out = max(neural_net::outl);
                            return neural_net::out;
                        } else { // middle layers
                            for (int j = 0; j < neural_net::rows; j++){
                                app(middle[i], calc_act(middle[i-1], neural_net::net[0, j].wgt, neural_net::net[0, j].bias));
                            }
                        }
                        break;
                }
            }
        }

        double calc_cost (node * wanted){ // calculates how bad the net performes compared to the wanted output, the higher the return value, the worse the net performs
            return cost(wanted, outl);
        }

        void improve (node * wanted, double money){ // tries to lower the cost to improve the net's performance by changing parameters like bias and weight
            if (len(wanted) != outputs){
                throw "Invalid parameter, the list should be as long as the amount of outputs";
            }

            for (int n = 0; n < outputs; n++){
                node * impact = calc_impact(neural_net::outn[n].prevact, neural_net::outn[n].wgt, neural_net::outn[n].bias, atIndex(wanted, n));
                double avib = atIndex(impact, 0);
                double aviw = atIndex(impact, 1);
                double avia = atIndex(impact, 2);
                double constant = money/(abs(avib) + abs(aviw) + abs(avia));
                neural_net::outn[n].bias += constant * avib;
                for (int m = 0; m < len(neural_net::outn[n].wgt); m++){
                    changeAtIndex(neural_net::outn[n].wgt, m, atIndex(neural_net::outn[n].wgt, m)+(constant * aviw));
                }
                change_previous(neural_net::col, avia, constant * avia);
            }

            return;
        }
};
}