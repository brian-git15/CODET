#include "pipeline.h"
#include "../analysis/static_analyzer.h"
#include "../analysis/hot_cold_analyzer.h"
#include "../report/report_generator.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace Pipeline {

    // Single-pass analysis using parser-driven callbacks
    void runAnalysis(const std::string& projectPath, AnalysisCallbacks callbacks) {
        std::cout << "[Pipeline] Starting analysis on: " << projectPath << "\n";

        for (auto& p : fs::recursive_directory_iterator(projectPath)) {
            if (p.is_regular_file() && p.path().extension() == ".cpp") {
                std::string filePath = p.path().string();

                // Call the parser (simplified; parser triggers callbacks per node)
                StaticAnalyzer::parseFile(filePath, callbacks);
            }
        }

        std::cout << "[Pipeline] Analysis complete.\n";
    }

    // Reports consume data collected by analysis modules
    void generateReport(const std::string& outputPath) {
        std::cout << "[Pipeline] Generating reports in: " << outputPath << "\n";

        if (!fs::exists(outputPath)) fs::create_directories(outputPath);

        ReportGenerator::generateJSON(outputPath);
        ReportGenerator::generateCSV(outputPath);
        ReportGenerator::generateTXT(outputPath);

        std::cout << "[Pipeline] Reports generated.\n";
    }

}
