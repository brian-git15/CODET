#pragma once
#include <string>

namespace Pipeline {

    // Run analysis on the user's codebase
    void runAnalysis(const std::string& projectPath);

    // Generate reports in a user-specified folder
    void generateReport(const std::string& outputPath);

}
