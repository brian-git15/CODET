#include "static_analyzer.h"
#include "../analysis/hot_cold_analyzer.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>

namespace StaticAnalyzer {

std::vector<FunctionMetrics> staticResults;

void parseFile(const std::string& filePath, const struct Pipeline::AnalysisCallbacks& callbacks) {
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    std::string line;
    std::string currentFunction;
    int lineCount = 0, loopCount = 0, branchCount = 0;
    std::unordered_map<std::string,int> expressionMap; // Detect duplicate computations
    std::unordered_map<std::string,bool> parameterUsed; // Track parameter usage

    // Function, loop, branch detection (simplified)
    std::regex funcRegex(R"(\b[A-Za-z_][A-Za-z0-9_]*\s+[A-Za-z_][A-Za-z0-9_]*\s*\((.*)\)\s*\{)");
    std::regex loopRegex(R"(\b(for|while)\s*\()");
    std::regex branchRegex(R"(\b(if|else if|switch)\s*\()");
    std::regex exprRegex(R"([\w\+\-\*\/%]+)"); // crude placeholder

    while (std::getline(file, line)) {
        lineCount++;

        std::smatch match;

        // --- Detect function ---
        if (std::regex_search(line, match, funcRegex)) {
            currentFunction = match.str(0);
            loopCount = 0;
            branchCount = 0;
            expressionMap.clear();
            parameterUsed.clear();

            // Extract parameters
            std::string paramStr = match[1].str();
            std::regex paramRegex(R"(\b[A-Za-z_][A-Za-z0-9_]*\b)");
            std::smatch paramMatch;
            std::string::const_iterator searchStart(paramStr.cbegin());
            while (std::regex_search(searchStart, paramStr.cend(), paramMatch, paramRegex)) {
                parameterUsed[paramMatch.str()] = false;
                searchStart = paramMatch.suffix().first;
            }

            staticResults.push_back({filePath, currentFunction, 0, 0, 0, 0, 0});
            if (callbacks.onFunction) callbacks.onFunction(currentFunction);

            // Hot/Cold classification based on function structure
            HotColdAnalyzer::classifyFunction(filePath, currentFunction);
        }

        // --- Detect loops ---
        if (std::regex_search(line, match, loopRegex)) loopCount++;

        // --- Detect branches ---
        if (std::regex_search(line, match, branchRegex)) branchCount++;

        // --- Track expressions for duplicates ---
        auto exprBegin = std::sregex_iterator(line.begin(), line.end(), exprRegex);
        auto exprEnd = std::sregex_iterator();
        for (auto it = exprBegin; it != exprEnd; ++it) {
            std::string expr = it->str();
            if (!expr.empty()) expressionMap[expr]++;
        }

        // --- Track parameter usage ---
        for (auto& [param, used] : parameterUsed) {
            if (!used && line.find(param) != std::string::npos) parameterUsed[param] = true;
        }
    }

    // --- Final metrics per function ---
    int duplicateCount = 0;
    for (auto& [expr, count] : expressionMap) if (count > 1) duplicateCount++;

    int unusedCount = 0;
    for (auto& [param, used] : parameterUsed) if (!used) unusedCount++;

    staticResults.back().lineCount = lineCount;
    staticResults.back().loops = loopCount;
    staticResults.back().branches = branchCount;
    staticResults.back().duplicateComputations = duplicateCount;
    staticResults.back().unusedParameters = unusedCount;

    std::cout << "[StaticAnalyzer] Function " << currentFunction
              << " lines: " << lineCount
              << ", loops: " << loopCount
              << ", branches: " << branchCount
              << ", duplicate computations: " << duplicateCount
              << ", unused params: " << unusedCount << "\n";
}
