#!/bin/bash

# Get the directory of the current script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Go up three levels from SCRIPT_DIR to get the project root
PROJECT_ROOT="$(dirname "$(dirname "$SCRIPT_DIR")")"

# Ensure the output directories exist
mkdir -p "${PROJECT_ROOT}/graph_images" "${PROJECT_ROOT}/graph"

# Generate caller graph
echo "Generating caller graph..."
cflow -o "${PROJECT_ROOT}/graph/callgraph.txt" "${PROJECT_ROOT}/src/"*.c
python3 "${PROJECT_ROOT}/graph/scripts/cflow_to_caller_dot.py" "${PROJECT_ROOT}/graph/callgraph.txt" "${PROJECT_ROOT}/graph/callgraph.dot"
dot -Tpng "${PROJECT_ROOT}/graph/callgraph.dot" -o "${PROJECT_ROOT}/graph_images/callgraph.png"

# Generate callee graph
echo "Generating callee graph..."
cflow -o "${PROJECT_ROOT}/graph/callee_graph.txt" "${PROJECT_ROOT}/src/"*.c
python3 "${PROJECT_ROOT}/graph/scripts/cflow_to_callee_dot.py" "${PROJECT_ROOT}/graph/callee_graph.txt" "${PROJECT_ROOT}/graph/callee_graph.dot"
dot -Tpng "${PROJECT_ROOT}/graph/callee_graph.dot" -o "${PROJECT_ROOT}/graph_images/callee_graph.png"

echo "Graphs generated in the 'graph_images' directory."
