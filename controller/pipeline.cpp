#include "pipeline.h"
#include "../analysis/static_analyzer.h"
#include "../analysis/profiler.h"
#include "../analysis/hot_cold_analyzer.h"
#include "../report/report_generator.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace Pipeline {

    // ---------------------------
    // Run static analysis, profiling, hot/cold classification
    // ---------------------------
    void runAnalysis(const std::string& projectPath) {
        std::cout << "[Pipeline] Starting analysis for project: " << projectPath << "\n";

        // Step 1: Static analysis (AST, loops, branches, tasks, ISRs)
        StaticAnalyzer::analyzeFolder(projectPath);

        // Step 2: Lightweight profiling (host simulation)
        Profiler::profileFolder(projectPath);

        // Step 3: Hot/cold path classification and WCET hints
        HotColdAnalyzer::classifyFolder(projectPath);

        std::cout << "[Pipeline] Analysis complete.\n";
    }

    // ---------------------------
    // Generate reports in a user-specified folder
    // ---------------------------
    void generateReport(const std::string& outputPath) {
        std::cout << "[Pipeline] Generating reports in: " << outputPath << "\n";

        // Ensure the output folder exists
        if (!fs::exists(outputPath)) {
            fs::create_directories(outputPath);
        }

        // Call report generator modules
        ReportGenerator::generateJSON(outputPath);
        ReportGenerator::generateCSV(outputPath);
        ReportGenerator::generateTXT(outputPath);

        std::cout << "[Pipeline] Reports generated.\n";
    }

}
