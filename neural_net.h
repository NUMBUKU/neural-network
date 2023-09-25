/*
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

    That's it, I hope you learn something.
*/

# include <iostream>
# include "neuron.h"

namespace net {

class neural_net {
    private:
        // boolean for storing if the user wants all the variables of the net to be printed out in a format so that when run it replicates this net (for exporting the net)
        bool printnet;

        unsigned int iteration = 0;
        double coef;

        // recursive method for changing the previous activation
        void change_previous (int collumn, double avia, double share){
            node * impact = newList();
            for (int y = 0; y < neural_net::rows; y++){
                impact = calc_impact(middle[collumn-1], neural_net::net[collumn, y].wgt, neural_net::net[collumn, y].bias, neural_net::net[collumn, y].act + avia, neural_net::net[collumn, y].out, neural_net::coef);
                double avib = atIndex(impact, 0);
                double aviw = atIndex(impact, 1);
                double avia1 = atIndex(impact, 2);
                double constant = share/(abs(avib) + abs(aviw) + abs(avia1));
                neural_net::net[collumn, y].bias -= constant * avib;
                for (int m = 0; m < len(neural_net::net[collumn, y].wgt); m++){
                    changeAtIndex(neural_net::net[collumn, y].wgt, m, atIndex(neural_net::net[collumn, y].wgt, m) - (constant * aviw));
                }
                if (collumn != 1){
                    change_previous(collumn-1, avia1, constant * avia1); // recursion for changing the activation before this
                }
                impact = clear(impact);
            }

            return;
        }
    public:
        // public variables for the output of the net
        node * outl = newList();
        double out, certainty;
        unsigned int col, inputs, outputs, rows;
        node ** middle;

        // public variables for the neurons
        neuron * net;
        neuron * outn;

        //constructor
        neural_net (unsigned int collums, unsigned int rows, unsigned int outputs, unsigned int inputs, bool printnet_after_death = false, double coef = .1){
            if (collums == 0 || rows == 0 || outputs == 0 || inputs == 0){
                throw std::runtime_error("Invalid parameter, the parameters must be greater than zero.");
            } else {
                neural_net::col = collums;
                neural_net::rows = rows;
                neural_net::outputs = outputs;
                neural_net::inputs = inputs;
                neural_net::coef = coef;
                neural_net::net = new neuron [neural_net::col, neural_net::rows];
                neural_net::outn = new neuron [outputs];
                neural_net::middle = new node * [neural_net::col];
                neural_net::printnet = printnet_after_death;
                for (int i = 0; i < neural_net::col; i++){ // assigning values for weights and biasses
                    neural_net::middle[i] = newList();
                    for (int j = 0; j < neural_net::rows; j++){
                        neural_net::net[i, j].wgt = newList();
                        if (i == 0){
                            for (int k = 0; k < neural_net::inputs; k++){
                                app(neural_net::net[i, j].wgt, 1);
                            }
                        } else {
                            for (int k = 0; k < neural_net::rows; k++){
                                app(neural_net::net[i, j].wgt, 1);
                            }
                        }
                        neural_net::net[i, j].bias = 0;
                        outn[j].out = 0;
                    }
                }

                neural_net::middle[neural_net::col-1] = newList();
                for (int l = 0; l < neural_net::outputs; l++){
                    neural_net::outn[l].wgt = newList();
                    for (int m = 0; m < neural_net::rows; m++){
                        app(neural_net::outn[l].wgt, 1);
                    }
                    outn[l].bias = 0;
                    outn[l].out = 1;
                }
            }
        }

        // destructor
        ~neural_net (){
            if (neural_net::printnet){
                for (int x = 0; x < neural_net::col; x++){
                    for (int y = 0; y < neural_net::rows; y++){
                        std::cout << "name.net[" << x << ", " << y << "].bias = " << neural_net::net[x, y].bias << ";" << std::endl;
                        for (int c = 0; c < len(neural_net::net[x, y].wgt); c++){
                            std::cout << "changeAtIndex(name.net[" << x << ", " << y << "].wgt, " << c << ", " << atIndex(neural_net::net[x, y].wgt, c) << ");" << std::endl;
                        }
                        delete (neural_net::net[x, y].wgt);
                    }
                }
                for (int i = 0; i < neural_net::outputs; i++){
                    std::cout << "name.outn[" << i << "].bias = " << neural_net::outn[i].bias << ";" << std::endl;
                    for (int c = 0; c < len(neural_net::outn[i].wgt); c++){
                        std::cout << "changeAtIndex(name.outn[" << i << "].wgt, " << c << ", " << atIndex(neural_net::outn[i].wgt, c) << ");" << std::endl;
                    }
                }
            } else {
                for (int x = 0; x < neural_net::col; x++){            
                    for (int y = 0; y < neural_net::rows; y++){
                        delete (neural_net::net[x, y].wgt);
                    }
                }
            }

            for (int n = 0; n < neural_net::col; n++){
                delete (middle[n]);
            }
            delete (neural_net::outl);
            delete (neural_net::middle);
            delete (neural_net::net);
            delete (neural_net::outn);
        }


        //public methods
        double calc_out (node * input){ // method for calculating the output, stores the list of outputs in neural_net::outl and stores the highest number in that list in neural_net::out
            outl = clear(outl);
            for (int l = 0; l < neural_net::col; l++){
               middle[l] = clear(middle[l]);
            }

            for (int i = 0; i < neural_net::col+1; i++){
                if (i == 0){ // first layer
                    for (int j = 0; j < neural_net::rows; j++){
                        neural_net::net[0, j].act = calc_act(input, neural_net::net[0, j].wgt, neural_net::net[0, j].bias, 0, neural_net::coef);
                        if (neural_net::iteration == 0){
                            app(middle[0], neural_net::net[0, j].act);
                        } else {
                            changeAtIndex(middle[0], 0, neural_net::net[0, j].act);
                        }
                    }
                } else if (i == neural_net::col){ // last layer
                    for (int j = 0; j < neural_net::outputs; j++){
                        neural_net::outn[j].act = calc_act(neural_net::middle[neural_net::col-1], neural_net::outn[j].wgt, neural_net::outn[j].bias, 1, neural_net::coef);
                        if (neural_net::iteration == 0){
                            app(neural_net::outl, neural_net::outn[j].act);
                        } else {
                            changeAtIndex(neural_net::outl, j, neural_net::outn[j].act);
                        }
                    }

                    neural_net::out = indexOf(neural_net::outl, max(neural_net::outl));
                    neural_net::certainty = round((atIndex(neural_net::outl, neural_net::out) / total(neural_net::outl)) * atIndex(neural_net::outl, neural_net::out) * 1000)/10;
                    return neural_net::out;
                } else { // middle layers
                    for (int j = 0; j < neural_net::rows; j++){
                        neural_net::net[i, j].act = calc_act(neural_net::middle[i-1], neural_net::net[i, j].wgt, neural_net::net[i, j].bias, neural_net::net[i, j].out, neural_net::coef);
                        if (neural_net::iteration == 0){
                            app(middle[i], neural_net::net[i, j].act);
                        } else {
                            changeAtIndex(middle[i], i, neural_net::net[i, j].act);
                        }
                    }
                }
            }
            if (iteration == 0) neural_net::iteration++;
        }

        double calc_cost (node * wanted){ // calculates how bad the net performes compared to the wanted output, the higher the return value, the worse the net performs
            if (len(wanted) != outputs){
                throw std::runtime_error("Invalid parameter, the list should be as long as the amount of outputs");
            }

            double a = 0;
            for (int i = 0; i < outputs; i++){
                a += cost(atIndex(wanted, i), atIndex(outl, i));
            }

            return a;
        }

        void improve (node * wanted, double money){ // tries to lower the cost to improve the net's performance by changing parameters like bias and weight
            if (len(wanted) != outputs){
                throw std::runtime_error("Invalid parameter, the list should be as long as the amount of outputs");
            }

            for (int n = 0; n < outputs; n++){
                node * impact = calc_impact(neural_net::middle[neural_net::col-1], neural_net::outn[n].wgt, neural_net::outn[n].bias, atIndex(wanted, n), neural_net::outn[n].out, neural_net::coef);
                double avib = atIndex(impact, 0);
                double aviw = atIndex(impact, 1);
                double avia = atIndex(impact, 2);
                double constant = money/(abs(avib) + abs(aviw) + abs(avia));
                neural_net::outn[n].bias -= constant * avib;
                for (int m = 0; m < len(neural_net::outn[n].wgt); m++){
                    changeAtIndex(neural_net::outn[n].wgt, m, atIndex(neural_net::outn[n].wgt, m) - (constant * aviw));
                }
                change_previous(neural_net::col, avia, constant * avia);
            }

            return;
        }
};
}