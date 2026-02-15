#include "pipeline_wrapper.h"
#include "../controller/pipeline.h"

namespace PipelineWrapper {

    void analyzeProject(const std::string& project_path) {
        // Tell pipeline to scan the given folder
        Pipeline::runAnalysis(project_path);

        // Optionally generate reports
        Pipeline::generateReport(project_path);
    }
}
