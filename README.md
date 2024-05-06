- [ ] 1. The library should overload operators to support the reaction rule typesetting directly in C++ code.
- [ ] 2. Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
- [ ] 3. Implement a generic symbol table to store and lookup objects of user-defined key and value types. Support
failure cases when a) the table does not contain a looked up symbol, b) the table already contains a symbol that
is being added. Demonstrate the usage of the symbol table with the reactants (names and initial counts).
- [ ] 4. Implement the stochastic simulation (Alg. 1) of the system using the reaction rules.
- [ ] 5. Demonstrate the application of the library on the three examples (shown in Fig. 1, 2, 3).
- [ ] 6. Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize.
- [ ] 7. Implement a generic support for (any) user-supplied state observer function object or provide a lazy trajectory
generation interface (coroutine). The observer itself should be supplied by the user/test and not be part of
the library. To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
without storing entire trajectory data. Record the peak hospitalization values for population sizes of NNJ and
NDK .
- [ ] 8. Implement support for multiple computer cores by parallelizing the computation of several simulations at the
same time. Estimate the likely (average) value of the hospitalized peak over 100 simulations.
- [ ] 9. Implement unit tests (e.g. test symbol table methods, their failure cases, and pretty-printing of reaction rules).
- [ ] 10. Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 100 simulations
a single core, multiple cores, or improved implementation). Record the timings and make your conclusions.
Make sure to include testing and benchmarking code as well as the sample results, measurements, plots and
conclusions into the report.
