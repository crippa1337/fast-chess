#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

#include "engine.h"
#include "options.h"
#include "uci.h"

int main(int argc, char const *argv[])
{
    CMD::Options options = CMD::Options(argc, argv);
    options.print_params();

    Engine engine;

    engine.setCmd("./DummyEngine.exe");
    engine.writeProcess("uci");
    auto output = engine.readProcess("uciok");

    for (const auto &item : output)
    {
        std::cout << item << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    engine.writeProcess("quit");
    engine.stopProcess();

    UciEngine uci;
    uci.setEngine(engine);
    uci.startEngine("./DummyEngine.exe");
    uci.sendUci();
    uci.stopEngine();

    UciEngine uciNew = UciEngine(engine);
    uciNew.startEngine("./DummyEngine.exe");
    uciNew.sendUci();
    uciNew.stopEngine();
    return 0;
}