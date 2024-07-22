This was done as a group

1. Version (4 bits)
   - Value: 4
   - Explanation: This value indicates that the IP version is 4, i.e., IPv4.

2. Header Length (IHL) (4 bits)
   - Value: 5
   - Explanation: This value indicates the number of 32-bit words in the header. 5 means the header is 20 bytes long (5 * 4 bytes).

3. Differentiated Services Field (DSCP) (6 bits)
   - Value: 0x2B
   - Explanation: The value 0x2B indicates a DSCP value corresponding to 43 in decimal, which is associated with a certain type of QoS behavior, specifically AF11 (Assured Forwarding).

4. ECN (2 bits)
   - Value: 00
   - Explanation: This value indicates that the packet is not using ECN. It is not ECN-capable, and any network devices should not set or interpret ECN-related bits for this packet.

5. Total Length (16 bits)
   - Value: 102
   - Explanation: This value indicates that the entire packet, including the header and data, is 102 bytes long.

6. Identification (16 bits)
   - Value: 0x510d (20749)
   - Explanation: This value indicates the identification value of the packet, which is used to uniquely identify fragments of an original IP datagram.

7. Flags (3 bits)
   - Value: 0x02 (Don't Fragment)
   - Explanation: The value 0x02 identifies the "Don't Fragment" flag, indicating that the packet should not be fragmented.

8. Fragment Offset (13 bits)
   - Value: 0
   - Explanation: Indicates where in the datagram this fragment belongs. 0 means the packet is not fragmented.

9. Time to Live (TTL) (8 bits)
   - Value: 57
   - Explanation: This value indicates that the packet can pass through 57 more routers before being discarded. The initial TTL is typically 64, meaning it has already passed through 7 routers (64 - 57).

10. Protocol (8 bits)
   - Value: TCP (6)
   - Explanation: This value indicates that the data portion of this IP packet contains a TCP segment, as indicated by the protocol number 6.

11. Header Checksum (16 bits)
   - Value: 0x0487
   - Explanation: This checksum is used for error-checking the header. A correct checksum ensures the integrity of the header data.

12. Source Address (32 bits)
   - Value: 162.159.134.234
   - Explanation: This value indicates the IP address of the sender.

13. Destination Address (32 bits)
   - Value: 192.168.1.164
   - Explanation: This value indicates the IP address of the receiver.

14. Transmission Control Protocol (TCP)
   - Source Port: 443
   - Destination Port: 52631
   - Sequence Number: 106
   - Acknowledgment Number: 1
   - Header Length: 62 bytes