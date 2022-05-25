#include <iostream>

#include "work_mode/factory.h"

int main(int argc, char *argv[])
{
    ++argv;
    --argc;

    auto work_mode = galament::client::work_mode::Factory::CreateFromCommandLine({ argv, argv + static_cast<size_t>(argc) });
    if (work_mode == nullptr) {
        std::cerr << "Usage: host:port [--statistic]" << std::endl;
        return 1;
    }

    work_mode->Run();
    return 0;
}