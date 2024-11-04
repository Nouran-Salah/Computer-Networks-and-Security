import re
import sys

def parse_cflow_line(line):
    """Extract function names and their hierarchy level based on indentation."""
    level = len(re.match(r'^\s*', line).group())
    func_name = re.search(r'(\w+)\(', line).group(1)
    return level, func_name

def convert_cflow_to_dot(cflow_file, dot_file, rankdir="LR", node_shape="box", node_color="lightblue", 
                         font_name="Arial", font_size=10, arrow_color="black", arrow_size=0.7):
    """Convert a cflow output file to a .dot file for a caller graph with custom styling."""
    with open(cflow_file, 'r') as f, open(dot_file, 'w') as out:
        out.write("digraph CallGraph {\n")
        out.write(f"    rankdir={rankdir};\n")
        out.write(f"    node [shape={node_shape}, style=filled, fillcolor={node_color}, fontname={font_name}, fontsize={font_size}];\n")
        out.write(f"    edge [color={arrow_color}, arrowsize={arrow_size}];\n")

        stack = []
        prev_level = -1

        for line in f:
            if '(' not in line:
                continue
            level, func_name = parse_cflow_line(line)

            # Adjust stack based on current level
            while len(stack) > level:
                stack.pop()

            # Draw the relationship in the call graph
            if stack:
                out.write(f'    "{stack[-1]}" -> "{func_name}";\n')

            # Update stack to reflect current level
            if len(stack) <= level:
                stack.append(func_name)
            else:
                stack[-1] = func_name

            prev_level = level

        out.write("}\n")

if __name__ == "__main__":
    # Ensure the script is called with at least two arguments: input and output file paths
    if len(sys.argv) < 3:
        print("Usage: python3 cflow_to_dot.py <input_cflow_file> <output_dot_file> [rankdir] [node_shape] [node_color] [font_name] [font_size] [arrow_color] [arrow_size]")
        sys.exit(1)

    # Get input and output file paths from command-line arguments
    input_cflow_file = sys.argv[1]
    output_dot_file = sys.argv[2]

    # Optional parameters with defaults
    rankdir = sys.argv[3] if len(sys.argv) > 3 else "LR"
    node_shape = sys.argv[4] if len(sys.argv) > 4 else "box"
    node_color = sys.argv[5] if len(sys.argv) > 5 else "lightblue"
    font_name = sys.argv[6] if len(sys.argv) > 6 else "Arial"
    font_size = int(sys.argv[7]) if len(sys.argv) > 7 else 10
    arrow_color = sys.argv[8] if len(sys.argv) > 8 else "black"
    arrow_size = float(sys.argv[9]) if len(sys.argv) > 9 else 0.7

    # Convert cflow output to dot format with styling
    convert_cflow_to_dot(input_cflow_file, output_dot_file, rankdir, node_shape, node_color, font_name, font_size, arrow_color, arrow_size)
