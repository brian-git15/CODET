#include <iostream>
#include "pipeline_wrapper.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: codet_cli <project_path>\n";
        return 1;
    }

    std::string project_path = argv[1];
    std::cout << "Analyzing project: " << project_path << "\n";
    
    PipelineWrapper::analyzeProject(project_path);

    std::cout << "Analysis complete. Reports are in /reports\n";
    return 0;
}
