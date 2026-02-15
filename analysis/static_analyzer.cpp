#include "static_analyzer.h"
#include "../analysis/hot_cold_analyzer.h"
#include <fstream>
#include <iostream>
#include <regex>

namespace StaticAnalyzer {

    // Store metrics for all functions in the project
    std::vector<FunctionMetrics> staticResults;

    void parseFile(const std::string& filePath, const struct Pipeline::AnalysisCallbacks& callbacks) {
        std::ifstream file(filePath);
        if (!file.is_open()) return;

        std::string line;
        std::string currentFunction;
        int loopCount = 0, branchCount = 0;

        std::regex funcRegex(R"(\b[A-Za-z_][A-Za-z0-9_]*\s+[A-Za-z_][A-Za-z0-9_]*\s*\(.*\)\s*\{)");
        std::regex loopRegex(R"(\b(for|while)\s*\()");
        std::regex branchRegex(R"(\b(if|else if|switch)\s*\()");

        while (std::getline(file, line)) {
            std::smatch match;

            // Function detection
            if (std::regex_search(line, match, funcRegex)) {
                currentFunction = match.str(0);
                loopCount = 0;
                branchCount = 0;

                staticResults.push_back({filePath, currentFunction, 0, 0});

                if (callbacks.onFunction) callbacks.onFunction(currentFunction);

                // Hot/Cold classification
                HotColdAnalyzer::classifyFunction(filePath, currentFunction);
            }

            // Loop detection
            if (std::regex_search(line, match, loopRegex)) {
                loopCount++;
                staticResults.back().loops = loopCount;

                if (callbacks.onLoop) callbacks.onLoop(match.str(0));

                HotColdAnalyzer::classifyLoop(filePath, match.str(0));
            }

            // Branch detection
            if (std::regex_search(line, match, branchRegex)) {
                branchCount++;
                staticResults.back().branches = branchCount;

                if (callbacks.onBranch) callbacks.onBranch(match.str(0));

                HotColdAnalyzer::classifyBranch(filePath, match.str(0));
            }
        }

        std::cout << "[StaticAnalyzer] Parsed " << filePath
                << " -> Function: " << currentFunction
                << ", Loops: " << loopCount
                << ", Branches: " << branchCount << "\n";
    }
}