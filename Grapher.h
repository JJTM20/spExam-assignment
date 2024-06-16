//
// Created by jjtor on 02/06/2024.
//

#ifndef EKSAMENSPROJEKT_GRAPHER_H
#define EKSAMENSPROJEKT_GRAPHER_H

#include <bits/stdc++.h>

#include <utility>

std::string cleanString(std::string str) {
    str.erase(std::remove(str.begin(), str.end(), ':'), str.end());
    return str;
}

class Grapher{
private:
    std::string start = "digraph{";
    std::string end = "}";
    std::ofstream out;
    int delay_index = 0;
    std::vector<std::string> molecule_labels = std::vector<std::string>();
    std::vector<double> delays = std::vector<double>();
public:
    Grapher(std::string name){
    std::string path="..\\out\\out_" + cleanString(name) + ".txt";
    out = std::ofstream(path);
    out << start;
    };
    ~Grapher(){
        out << end;
        std::cout << "Grapher destroyed. ";
    }

    void Graph(std::list<stochastic::Reaction> reactions){
        for (auto r:reactions) {
            auto delay = AddDelay(r.get_current_rate_parameter());
            for (auto reactant:r.get_reactants()) {
                AddMolecule(reactant.GetName());
                for (auto p:r.get_products()) {
                    AddArrow(reactant.GetName(), p.GetName(), r.get_current_rate_parameter());
                }
            }
        }
        std::cout << "Graphing done";
    }

    void AddMolecule(std::string label){
        if (std::find(molecule_labels.begin(), molecule_labels.end(), label) != molecule_labels.end()){
            return;
        }
        molecule_labels.push_back(label);
        out << label << "[label=\"" << label << R"(",shape="box",style="filled",fillcolor="cyan"];)" << "\n";
    }
    std::string AddDelay(double delay){
        delays.push_back(delay);
        auto r = "r" + std::to_string(delay_index);
        delay_index++;
        return r;
    }

    //Takes in (label, delay) || (delay, label)
    template<class T1, class T2>
    void AddArrow(T1 source, T2 target, double delay){
        out << source << "->" << target << "[label=\"" << (double)(delay / 0.01) * 0.01 <<"\"]\n";
    }
};


#endif //EKSAMENSPROJEKT_GRAPHER_H
