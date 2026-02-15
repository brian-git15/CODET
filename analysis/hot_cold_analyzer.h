#pragma once
#include <string>
#include <vector>

/**
 * HotColdAnalyzer:
 * ----------------
 * Analyzes functions, loops, and branches to classify them as "hot" or "cold".
 * Hot = frequently executed or critical path
 * Cold = rarely executed or background code
 * 
 * The results are used by the report generator to highlight critical paths for
 * optimization and memory placement decisions.
 */

namespace HotColdAnalyzer {

    struct HotColdResult {
        std::string filePath; 
        std::string nodeName;
        std::string type;
        std::string classification;
    };

    extern std::vector<HotColdResult> results;

    void classifyFunction(const std::string& filePath, const std::string& functionName);

    void classifyLoop(const std::string& filePath, const std::string& loopNode);

    void classifyBranch(const std::string& filePath, const std::string& branchNode);

}
