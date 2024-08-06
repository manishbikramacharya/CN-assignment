The UDP (User Datagram Protocol) header is 8 bytes long, consisting of four 2-byte fields:

1. Source Port Number (2 bytes):It identifies the sender's port. For clients, it's usually an ephemeral port;  for servers, a well-known port (0-1023). If not used, it is set to zero.

2. Destination Port Number (2 bytes):It identifies the receiver's port. For clients, it's likely an ephemeral port; for servers, a well-known port.

3. Length (2 bytes):It specifies the total length of the UDP header and data in bytes. The minimum length is 8 bytes. The maximum length, considering the IPv4 limit, is 65,507 bytes.

4. Checksum (2 bytes):It's used for error-checking of the header and data. Optional in IPv4, but mandatory in most cases in IPv6. If unused, it is set to all zeros.