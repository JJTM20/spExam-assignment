//
// Created by jjtor on 02/06/2024.
//

#ifndef EKSAMENSPROJEKT_GRAPHER_H
#define EKSAMENSPROJEKT_GRAPHER_H

#include <bits/stdc++.h>

#include <utility>

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
    std::string path="..\\out\\out_" + name + ".txt";
    out = std::ofstream(path);
    out << start;
    };
    ~Grapher(){
        out << end;
        std::cout << "Grapher destroyed. ";
    }

    void Graph(std::list<Reaction> reactions){
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
        /*if (std::find(delays.begin(), delays.end(), delay) != delays.end()){
            return "r" + std::to_string(delay_index);
        }*/
        delays.push_back(delay);
        auto r = "r" + std::to_string(delay_index);
        //out << "r" + std::to_string(delay_index) << "[label=\"" << std::to_string(delay) << R"(",shape="oval",style="filled",fillcolor="yellow"];)" << "\n";
        delay_index++;
        return r;
    }

    //Takes in (label, delay) || (delay, label)
    template<class T1, class T2>
    void AddArrow(T1 source, T2 target, double delay){
        out << source << "->" << target << "[label=\"" << (int)(delay / 0.01) * 0.01 <<"\"]\n";
    }
};


#endif //EKSAMENSPROJEKT_GRAPHER_H
