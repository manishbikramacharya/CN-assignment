Q)  What is the size of TCP  header ? , What are the different fields ? Describe its fields.

The size of a TCP (Transmission Control Protocol) header varies depending on the presence of optional fields. The minimum size of a TCP header is 20 bytes (160 bits), but it can be larger if options are included.

Here's a breakdown of the TCP header fields:

1. **Source Port (16 bits):** Specifies the port number used by the sender's application.

2. **Destination Port (16 bits):** Specifies the port number used by the receiver's application.

3. **Sequence Number (32 bits):** Indicates the position of the first byte of data in the segment relative to the beginning of the data stream. This field is used to ensure data is reassembled in the correct order and to detect lost data.

4. **Acknowledgment Number (32 bits):** Contains the value of the next sequence number that the sender of the segment is expecting to receive. This field is used to acknowledge receipt of data.

5. **Data Offset (4 bits):** Also known as the header length field. It indicates the size of the TCP header in 32-bit words. This field tells the receiver where the data begins in the segment.

6. **Reserved (3 bits):** Reserved for future use and should be set to zero. This field is used for future extensions and must be zero for the current version.

7. **Flags (9 bits):** Includes various control flags that indicate the state of the connection and control the flow of data. The common flags are:
   - **URG (1 bit):** Urgent pointer field significant.
   - **ACK (1 bit):** Acknowledgment field significant.
   - **PSH (1 bit):** Push function.
   - **RST (1 bit):** Reset the connection.
   - **SYN (1 bit):** Synchronize sequence numbers (used during the connection establishment).
   - **FIN (1 bit):** No more data from the sender (used during connection termination).

8. **Window Size (16 bits):** Specifies the size of the sender's receive window (buffer space) that is available. It is used for flow control to prevent the sender from overwhelming the receiver.

9. **Checksum (16 bits):** Used for error-checking the TCP header and data. It helps ensure data integrity by detecting corruption.

10. **Urgent Pointer (16 bits):** If the URG flag is set, this field points to the sequence number of the byte following urgent data. It is used to prioritize certain data.

11. **Options (Variable length):** This field is optional and can vary in size. It is used for various TCP features and extensions. The options field is followed by padding to ensure the TCP header length is a multiple of 32 bits.

12. **Padding (Variable length):** Added to ensure the TCP header length is a multiple of 32 bits. This ensures proper alignment of the TCP header and options.

In summary, the TCP header is more complex than the UDP header because TCP is a connection-oriented protocol that provides reliable, ordered, and error-checked delivery of data.