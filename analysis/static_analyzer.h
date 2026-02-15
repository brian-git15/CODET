#pragma once
#include <string>
#include <vector>

namespace Pipeline {
    struct AnalysisCallbacks;
}

namespace StaticAnalyzer {

    struct FunctionMetrics {
        std::string filePath;
        std::string functionName;
        int loops = 0;
        int branches = 0;
    };

    extern std::vector<FunctionMetrics> staticResults;

    void parseFile(const std::string& filePath, const Pipeline::AnalysisCallbacks& callbacks);

}
