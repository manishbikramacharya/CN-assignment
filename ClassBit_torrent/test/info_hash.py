import hashlib

def read_bencoded_info(file_path):
    with open(file_path, 'rb') as f:
        bencoded_info = f.read()
    return bencoded_info

def calculate_sha1_hash(bencoded_info):
    sha1 = hashlib.sha1()
    sha1.update(bencoded_info)
    info_hash = sha1.hexdigest()
    return info_hash

# Path to your bencoded info string file
file_path = '../info_string.txt'

# Read the bencoded info from the file
bencoded_info = read_bencoded_info(file_path)

# Print the bencoded info to verify it
print("Bencoded info (hex):", bencoded_info.hex())
print("Bencoded info (string):", bencoded_info)

# Calculate the SHA-1 hash
info_hash = calculate_sha1_hash(bencoded_info)
print("Info hash:", info_hash)
