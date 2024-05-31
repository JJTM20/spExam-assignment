//
// Created by jjtor on 06/05/2024.
//

#ifndef EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
#define EKSAMENSPROJEKT_STOCHASTICSIMULATION_H

#include <bits/stdc++.h>
#include <chrono>
#include <functional>
#include <algorithm>
#include "Reaction.h"
#include "Molecule.h"

class Environment{
public:
    Environment(){};
};

class Reaction;
class Molecule {
private:
    std::string symbol;
    double current_amount;
public:
    Molecule(std::string name, double amount){symbol = name, current_amount = amount;}
    double get_current_amount() { return current_amount; }

    void set_current_amount(double val) { current_amount = val; }

    //Overloads
    Reaction operator+(Molecule molecule) const;
    Reaction operator+(Reaction reaction);
    Reaction operator>>(double delay);

};

class GlobalState {
private:
    double time = 0;
    std::list<Molecule> reactants; //Current molecules swimming around
    std::map<std::string, int> generic_lookup_table;

public:
    GlobalState(){};

    Environment environment;
    void AddReactant(Molecule reactant){reactants.push_back(reactant);}

    void AddTime(double time_to_add) { time += time_to_add; }

    double GetCurrentTime() { return time; }

    std::string LookUp(std::string molecule_to_find) {
        auto it = generic_lookup_table.find(molecule_to_find);
        return it->first;
    }
};



class Reaction{
private:
    std::vector<Molecule> reactants;
    double rate_parameter;
public:
    Reaction(){};
    double get_current_rate_parameter(){return rate_parameter;}
    void set_rate_parameter(double rp){rate_parameter = rp;}
    std::vector<Molecule> get_reactants(){return reactants;}
    void add_reactant(Molecule reactant){reactants.push_back(reactant);}
    void add_product(Molecule product){reactants.push_back(product);}


    //Overloads
    Reaction operator>>(double delay){};

    Reaction operator>>=(Molecule molecule){
        add_product(molecule);
        return *this;
    };

    Reaction operator>>=(Reaction reaction){};

};

class Vessel {
private:
    std::string name;
    std::list<Reaction> reactions;
public:
    Vessel(std::string n){name = n;}
    GlobalState global_state = GlobalState(); //Environment

    Molecule add(std::string name, double amount){
        auto molecule = Molecule(name, amount);
        global_state.AddReactant(molecule);
        return molecule;
    };
    void add(const Reaction reaction){
        //global_state.AddTime(reaction.get_current_rate_parameter());
        reactions.push_back(reaction);
    };
};




class StochasticSimulation {
private:

public:
    void RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState state);
    const double ComputeReactionTime(Reaction reaction);
};



#endif //EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
