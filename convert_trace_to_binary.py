import sys

if len(sys.argv) < 2:
    print("Usage: python3 convert_trace_to_binary.py <input_file.bin>")
    sys.exit(1)

input_filename = sys.argv[1]
output_filename = input_filename.replace(".bin", "") + "_bits.txt"

# save as trace_bits.py
with open(input_filename, "rb") as f, open(output_filename, "w") as out:
    data = f.read()
    for i, byte in enumerate(data):
        # Convert byte to 8 bits, e.g., '11000000'
        bits = format(byte, '08b')
        out.write(f"{bits} ")
        if (i + 1) % 8 == 0: # New line every 8 bytes for readability
            out.write("\n")