#include <iostream>
#include "pipeline_wrapper.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: codet <project_path> <dst-fil>\n";
        return 1;
    }

    std::string project_path = argv[1];
    std::string dst_file = argv[2];

    PipelineWrapper::analyzeProject(project_path, dst_path);
    return 0;
}
