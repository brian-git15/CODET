#include "hot_cold_analyzer.h"
#include <iostream>

namespace HotColdAnalyzer {

    // Store all classifications
    std::vector<HotColdResult> results;

    void classifyFunction(const std::string& filePath, const std::string& functionName) {
        // Example heuristic: functions containing "ISR" are hot, others cold
        std::string classification = (functionName.find("ISR") != std::string::npos) ? "hot" : "cold";

        results.push_back({filePath, functionName, "function", classification});
    }

    void classifyLoop(const std::string& filePath, const std::string& loopNode) {
        // Example heuristic: all loops are hot for now
        results.push_back({filePath, loopNode, "loop", "hot"});
    }

    void classifyBranch(const std::string& filePath, const std::string& branchNode) {
        // Example heuristic: all branches are cold for now
        results.push_back({filePath, branchNode, "branch", "cold"});
    }
}
