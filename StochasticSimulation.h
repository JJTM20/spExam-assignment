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
    double get_current_amount() const { return current_amount; }
    std::string GetName(){return symbol;}

    void set_current_amount(double val) { current_amount = val; }

    //Overloads
    Reaction operator+(Molecule molecule) const;
    Reaction operator+(Reaction reaction);
    Reaction operator>>(double delay) const;

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
    std::vector<Molecule> products;
public:
    Reaction(){
        rate_parameter = 0;
    };
    double get_current_rate_parameter() {return rate_parameter;}
    void set_rate_parameter(double rp){rate_parameter = rp;}
    std::vector<Molecule> get_reactants(){return reactants;}
    std::vector<Molecule> get_products(){return products;}
    void add_reactant(const Molecule& reactant){reactants.push_back(reactant);}
    void add_product(const Molecule& product){products.push_back(product);}

    //Overloads
    Reaction operator>>(double delay){
        auto r = Reaction();
        for (const auto& reactant:this->get_reactants()) {
            r.add_reactant(reactant);
        }
        r.set_rate_parameter(delay); //Delay = rate_parameter
        return r;
    };

    Reaction operator>>=(Molecule molecule){
        add_product(molecule);
        return *this;
    };

    Reaction operator>>=(Reaction reaction){ //TODO: Add copy assignment constructor to reaction to copy all of this, instead of manually doing so
        auto r = Reaction();
        for (const auto& reactant:reaction.get_reactants()) {
            r.add_product(reactant);
        }
        for (const auto& reactant:this->get_reactants()) {
            r.add_reactant(reactant);
        }
        r.set_rate_parameter(this->get_current_rate_parameter());
        return r;
    };

    Reaction operator>>=(Environment env){;
        return *this;
    };
};

class Vessel {
private:
    std::string name;
    std::list<Reaction> reactions;
public:
    Vessel(std::string n){name = n;}
    GlobalState global_state = GlobalState(); //Environment
    std::list<Reaction> GetReactions(){return reactions;}
    std::string GetName(){return name;}

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
    void RunSimulation(std::vector<Reaction> reaction_set, double end_time, GlobalState state, Vessel vessel);
    const double ComputeReactionTime(Reaction reaction);
};


// Pretty printing
template<class T>
std::ostream& operator<<(std::ostream& os, std::list<T> const& container){
    for (auto reaction:container) {
        os << "Reactants: [";
        for (auto reactant:reaction.get_reactants()) {
            os << reactant.GetName() << " ";
        }
        os << "] Rate parameter: ";
        os << "[" << reaction.get_current_rate_parameter() << "]";
        os << " Products: [";
        for (auto p:reaction.get_products()) {
            os << p.GetName() << " ";
        }
        os << "]\n";
    }
    return os;
}




#endif //EKSAMENSPROJEKT_STOCHASTICSIMULATION_H
