#pragma once
#include <string>
#include <functional>

namespace Pipeline {

    struct AnalysisCallbacks {
        std::function<void(const std::string& functionName)> onFunction;
        std::function<void(const std::string& loopType)> onLoop;
        std::function<void(const std::string& branchType)> onBranch;
    };

    // Run analysis using parser-driven callbacks
    void runAnalysis(const std::string& projectPath, AnalysisCallbacks callbacks);

    // Generate reports into user-specified folder
    void generateReport(const std::string& outputPath);

}
