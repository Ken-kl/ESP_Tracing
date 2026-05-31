#!/bin/bash

INPUT="instruction_trace.log"
OUTPUT="clean_trace.log"

if [ ! -f "$INPUT" ]; then
    echo "Error: $INPUT not found."
    exit 1
fi

grep "^PC: " "$INPUT" > "$OUTPUT"

echo "Cleanup complete. Filtered output saved to $OUTPUT"