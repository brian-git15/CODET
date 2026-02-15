#pragma once
#include <string>
#include <vector>

namespace Pipeline {
    struct AnalysisCallbacks;
}

namespace StaticAnalyzer {

/**
 * FunctionMetrics:
 * ----------------
 * Aggregates metrics per function for large files.
 * Focus is on functions that are big or executed frequently.
 */
struct FunctionMetrics {
    std::string filePath;
    std::string functionName;
    int lineCount = 0;
    int loops = 0;
    int branches = 0;
    int duplicateComputations = 0;
    int unusedParameters = 0;
};

// All analyzed functions
extern std::vector<FunctionMetrics> staticResults;

/**
 * Parses a single C++ file.
 * Uses function-level aggregation for loops, branches, and variables.
 * Calls callbacks for hot/cold classification and optimization hints.
 */
void parseFile(const std::string& filePath, const Pipeline::AnalysisCallbacks& callbacks);

}
