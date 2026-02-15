/CODET
  /api
    serial_server.cpp      # Handles serial/CLI commands
    routes.cpp             # Maps endpoints to modules
  /controller
    pipeline.cpp           # Orchestrates analysis → profiling → optimization
  /analysis
    static_analyzer.cpp    # AST, loops, branches, tasks, ISRs
    profiler.cpp           # Lightweight instrumentation for embedded target
    hot_cold_analyzer.cpp  # Hot/cold path classification + WCET hints
  /optimizer
    branch_hint.cpp        # likely/unlikely hints
    loop_optimizer.cpp     # Loop unrolling/flattening
    function_optimizer.cpp # Inline/noinline for tasks/ISRs
    memory_optimizer.cpp   # Hot/cold data placement in RAM/Flash
  /report
    report_generator.cpp   # Reports, timing, memory, hot/cold paths
    graphviz_visualizer.cpp
  /storage
    flash_storage.cpp      # Optional persistent profiling results
/tests
  embedded_test_project.cpp
