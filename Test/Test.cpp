//
// Created by jjtor on 12/06/2024.
//

#include "doctest.h"
#include "../StochasticSimulation.h"

namespace stochastic{
    //Exercise 9
    TEST_CASE("Test SymbolTable") {
            auto symbolTable = GlobalState().symbolTable;
        SUBCASE("LookUpSuccess"){
            symbolTable.Update("A", 1);
            CHECK((symbolTable.LookUp("A")->second == 1));
        }
        SUBCASE("LookUpSymbolNotExist"){
            CHECK((symbolTable.LookUp("A") == symbolTable.table.end()));
        }
    }

    TEST_CASE("Pretty Print"){
        auto r = Reaction();
        r.add_reactant(Molecule("M1", 1));
        r.add_reactant(Molecule("M2", 4));
        r.add_product(Molecule("M3", 0));
        r.set_rate_parameter(1);
        Vessel v = Vessel("TestVessel");
        v.add(r);
        std::stringstream prettyPrint;
        prettyPrint << v.GetReactions();
        CHECK((prettyPrint.str() == "Reactants: [M1 M2 \b \b] Rate parameter: [1] Products: [M3 \b \b]\n"));
    }
}