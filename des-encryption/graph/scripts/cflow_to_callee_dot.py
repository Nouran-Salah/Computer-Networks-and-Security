import re
import sys

def parse_cflow_line(line):
    # Extract function names and their hierarchy level based on indentation
    level = len(re.match(r'^\s*', line).group())
    func_name = re.search(r'(\w+)\(', line).group(1)
    return level, func_name

def convert_cflow_to_callee_dot(cflow_file, dot_file):
    with open(cflow_file, 'r') as f, open(dot_file, 'w') as out:
        out.write("digraph CalleeGraph {\n")
        out.write("    node [shape=box];\n")

        stack = []
        prev_level = -1

        for line in f:
            if '(' not in line:
                continue
            level, func_name = parse_cflow_line(line)

            # Adjust stack based on current level
            while len(stack) > level:
                stack.pop()

            # Reverse the direction: each function points to the functions it calls
            if stack:
                out.write(f'    "{func_name}" -> "{stack[-1]}";\n')

            if len(stack) <= level:
                stack.append(func_name)
            else:
                stack[-1] = func_name

            prev_level = level

        out.write("}\n")

if __name__ == "__main__":
    # Check if the script has the required arguments
    if len(sys.argv) != 3:
        print("Usage: python3 cflow_to_callee_dot.py <input_cflow_file> <output_dot_file>")
        sys.exit(1)
    
    # Get input and output file paths from command-line arguments
    input_cflow_file = sys.argv[1]
    output_dot_file = sys.argv[2]

    # Convert the cflow output to .dot format
    convert_cflow_to_callee_dot(input_cflow_file, output_dot_file)
