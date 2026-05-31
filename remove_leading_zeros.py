import sys

input_filename = sys.argv[1]
output_filename = input_filename.replace(".bin", "stripped_zeros.bin")


with open(input_filename, "rb") as f, open( output_filename, "wb") as out:
    data = f.read()
    i = 0
    # Skip leading zeros
    while i < len(data) and data[i] == 0:
        i += 1
    
    while i + 8 < len(data):
        header = data[i]
        length = header & 0x1F

        if length == 0:
            i += 8
            continue
        
        payload_length =  legnth -3 
        # Skip 1 byte Header + 2 bytes Index, take the rest of the length
        payload = data[i+3 : i+length]
        out.write(payload)
        i += length