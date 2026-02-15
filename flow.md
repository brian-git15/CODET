CLI (host machine)
   │
   ▼
/cli_extension/main.cpp
   │
   ▼
pipeline_wrapper.cpp
   │
   ▼
/controller/pipeline.cpp
   │
   ├──> /analysis
   │       - static_analyzer.cpp
   │       - profiler.cpp
   │       - hot_cold_analyzer.cpp
   │
   ├──> /optimizer (optional)
   │       - branch_hint.cpp
   │       - loop_optimizer.cpp
   │       - function_optimizer.cpp
   │       - memory_optimizer.cpp
   │
   ▼
/report
   - report_generator.cpp
   - graphviz_visualizer.cpp
   │
   ▼
/reports (JSON/CSV/Excel/PDF output)
