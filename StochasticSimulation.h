//
// Created by jjtor on 06/05/2024.
//

#pragma once

#include <bits/stdc++.h>
#include <chrono>
#include <functional>
#include <algorithm>
#include "Reaction.h"
#include "Molecule.h"
#include <map>

namespace stochastic {


    class Environment {
    public:
        Environment() {};
    };

    class Reaction;

    class Molecule {
    private:
        std::string symbol;
        int current_amount;
    public:
        Molecule(std::string name, double amount) { symbol = name, current_amount = amount; }

        int get_current_amount() const { return current_amount; }

        std::string GetName() const { return symbol; }

        void set_current_amount(int val) { current_amount = val; }

        //Overloads
        Reaction operator+(Molecule molecule) const;

        Reaction operator+(Reaction reaction);

        Reaction operator>>(double delay) const;

    };

    class GlobalState {
    private:
        double time = 0;
        //std::list<Molecule> reactants; //Current molecules swimming around

        template<class T, class U>
        struct GenericLookupTable {
            std::map<T, U> table;

            auto LookUp(T search) {
                return table.find(search);

                /*if (auto it = table.find(search); it != table.end())
                    return it;*/
            }

            void Insert(Molecule m) {
                table.insert({m.GetName(), m.get_current_amount()});
            }

            void Update(T element, int value) {
                auto it = LookUp(element);
                if (it != table.end()) {
                    it->second += value;
                } else {
                    table.insert({element, value});
                    std::cout << element << " is not in symbol table. Has now been inserted";
                }
            }

        };

        std::list<Reaction> reactions;

    public:
        GlobalState() {};
        Environment environment;
        GenericLookupTable<std::string, int> symbolTable = GenericLookupTable<std::string, int>();

        void AddReactant(Molecule reactant) {
            //reactants.push_back(reactant);
            symbolTable.Insert(reactant);
        }

        void AddTime(double time_to_add) { time += time_to_add; }

        double GetCurrentTime() { return time; }
    };

    class Reaction {
    private:
        std::vector<Molecule> reactants;
        double rate_parameter;
        double delay;
        std::vector<Molecule> products;
    public:
        Reaction() {
            delay = std::numeric_limits<double>::infinity();
        };

        double get_current_rate_parameter() const { return rate_parameter; }

        double get_current_delay() const { return delay; }

        void set_delay(double d) { delay = d; }

        void set_rate_parameter(double rp) { rate_parameter = rp; }

        std::vector<Molecule> &get_reactants() { return reactants; }

        std::vector<Molecule> &get_products() { return products; }

        void add_reactant(const Molecule &reactant) { reactants.push_back(reactant); }

        void add_product(const Molecule &product) { products.push_back(product); }

        //Overloads
        Reaction operator>>(double rate) {
            auto r = Reaction();
            for (const auto &reactant: this->get_reactants()) {
                r.add_reactant(reactant);
            }
            r.set_rate_parameter(rate);
            return r;
        };

        Reaction operator>>=(Molecule molecule) {
            add_product(molecule);
            return *this;
        };

        Reaction operator>>=(Reaction reaction) { //TODO: Add copy assignment constructor to reaction to copy all of this, instead of manually doing so
            auto r = Reaction();
            for (const auto &reactant: reaction.get_reactants()) {
                r.add_product(reactant);
            }
            for (const auto &reactant: this->get_reactants()) {
                r.add_reactant(reactant);
            }
            r.set_rate_parameter(this->get_current_rate_parameter());
            return r;
        };

        Reaction operator>>=(Environment env) {
            ;
            return *this;
        };
    };

    class Vessel {
    private:
        std::string name;
        std::list<Reaction> reactions;
    public:
        Vessel(std::string n) { name = n; }

        GlobalState global_state = GlobalState(); //Environment
        std::list<Reaction> &GetReactions() { return reactions; }

        std::string GetName() { return name; }

        Molecule add(std::string name, double amount) {
            auto molecule = Molecule(name, amount);
            global_state.AddReactant(molecule);
            return molecule;
        };

        void add(const Reaction reaction) {
            reactions.push_back(reaction);
        };
    };

    stochastic::Reaction FindSmallestDelayReaction(stochastic::Vessel &vessel);
    class StochasticSimulation {
    private:
        std::string path = "..\\out\\trajectory.csv";
        std::ofstream trajectory;
    public:
        StochasticSimulation() {}

        void RunSimulation(Vessel vessel, double end_time);

        template<class Obs>
        void RunSimulation(Vessel vessel, double end_time, Obs observer){
            std::string mCount;
            std::string header;
            this->path = "..\\out\\trajectory_" + vessel.GetName() + ".csv";
            trajectory = std::ofstream(path);
            header += "Time,";
            trajectory << header;
            for (auto it = vessel.global_state.symbolTable.table.begin();
                 it != vessel.global_state.symbolTable.table.end(); ++it) {
                if (std::next(it) != vessel.global_state.symbolTable.table.end()) {
                    trajectory << it->first << ",";
                } else {
                    trajectory << it->first << "\n";
                }
            }
            std::cout << "Running simulation. Time: " + std::to_string(vessel.global_state.GetCurrentTime()) + "\n";

            while (vessel.global_state.GetCurrentTime() <= end_time) {
                observer(vessel.global_state.GetCurrentTime(), vessel);
                for (const auto &[key, value]: vessel.global_state.symbolTable.table) {
                    mCount += std::to_string(value) + ",";
                }
                mCount.pop_back();
                trajectory << vessel.global_state.GetCurrentTime() << ',' << mCount;
                trajectory << "\n";
                mCount.clear();
                for (auto &r: vessel.GetReactions()) {
                    auto delay = ComputeReactionTime(r, vessel);
                    r.set_delay(delay);
                    //Fix so it is taken directly from symbol table without for-range loop
                }

                // Pick reaction with shortest delay (reaction time)
                auto min_delay_reaction = FindSmallestDelayReaction(vessel);

                vessel.global_state.AddTime(min_delay_reaction.get_current_delay()); //Line 5
                for (auto &q: min_delay_reaction.get_reactants()) {
                    if (std::all_of(min_delay_reaction.get_reactants().begin(), min_delay_reaction.get_reactants().end(),
                                    [&](Molecule &i) {
                                        return vessel.global_state.symbolTable.LookUp(i.GetName())->second > 0;
                                    })) {
                        //TODO: Implement lookup/symbol table (To be..)
                        vessel.global_state.symbolTable.Update(q.GetName(), -1);
                    }
                }
                for (auto &p: min_delay_reaction.get_products()) {
                    vessel.global_state.symbolTable.Update(p.GetName(), 1);
                }
                std::cout << "Simulation step done. Time: " + std::to_string(vessel.global_state.GetCurrentTime()) + "\n";
            }
            std::cout << "Simulation done. Time: " + std::to_string(vessel.global_state.GetCurrentTime());
        }

        template<class Obs>
        void RunSimulationParallel(Vessel vessel, double end_time, int numberOfSims, Obs observer);

        static double ComputeReactionTime(Reaction &reaction, Vessel &vessel);
    };


// Pretty printing
    template<class T>
    std::ostream &operator<<(std::ostream &os, std::list<T> const &container) {
        for (auto reaction: container) {
            os << "Reactants: [";
            for (auto reactant: reaction.get_reactants()) {
                os << reactant.GetName() << " ";
            }
            os << "\b \b";
            os << "] Rate parameter: ";
            os << "[" << reaction.get_current_rate_parameter() << "]";
            os << " Products: [";

            if (!reaction.get_products().empty()) {
                for (const auto p: reaction.get_products()) {
                    os << p.GetName() << " ";
                }
                os << "\b \b";
            }
            os << "]\n";
        }
        return os;
    }
}