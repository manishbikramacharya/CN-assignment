# TCP Packet Analysis Report

## Overview
This report on TCP values is based on the packet captured in Wireshark. The screenshot of that particular packet is in the current directory along with the tcpp22.pcapng file. If you click on frame number 22 of that file, it's the same as the screenshot.

### TCP Header Fields

1. *Source Port*:
   - *Value*: 0xe135 or (57653)
   - *Description*: The source port field with a value of 57653 in the TCP header indicates that the sending application is using port 57653 to communicate with the receiving host. The port number falls under Dynamic or Private port.

2. *Destination Port*:
   - *Value*: 0x01bb or (443)
   - *Description*: It indicates that the data is intended for the HTTPS service on the receiving host. This port number allows the receiving host to forward the data to the appropriate application that can handle HTTPS traffic, ensuring secure communication between the client and server.

3. *Sequence Number*:
   - *Value*: 1 (Relative Sequence Number), 0x287f0980 (Absolute Sequence Number)
   - *Description*: The relative sequence number is displayed as 1 to indicate the first byte of data after the Initial Sequence Number. The absolute sequence number is the actual value found in the TCP header, which is 679414144 (0x287f0980) in this case. This approach simplifies the tracking of packets in a TCP stream for users analyzing the data.

4. *Acknowledgment Number*:
   - *Value*: 1 (Relative Acknowledgment Number), 0x12d487d3 (Absolute Acknowledgment Number)
   - *Description*: The value 0x12D487D3 in the acknowledgment number field, when converted from hexadecimal to decimal, gives 315918291. This indicates that the receiver has successfully received all bytes up to 315918290 and expects the next byte to be 315918291. The relative acknowledgment number of 1 simplifies this to indicate that it is the first byte expected after the initial sequence.

5. *Data Offset*:
   - *Value*: 0x8 (1000 in binary)
   - *Description*: The value indicates that the TCP header is 32 bytes long, and the actual data payload begins after these 32 bytes.

6. *Reserved*:
   - *Value*: 0
   - *Description*: Indicates that nothing is reserved. If reserved, the value must be from 0 to 15.

7. *Flags*:
   - *Value*: 0x018
   - *Description*: Converting to binary 0000 0001 1000, the first 4 msb is of the Reserved field. The next 8 bits indicate different flags. It means ACK and PSH flags are on. The ACK flag tells us that the Acknowledgement field is significant. The PSH flag indicates that the receiver should pass this data to the application as soon as possible.

8. *Window Size*:
   - *Value*: 0x0800 or (2048 in decimal)
   - *Description*: The value indicates that the receiver can currently accept up to 2048 bytes of data from the sender.

9. *Checksum*:
   - *Value*: 0x357c
   - *Description*: The value indicates the result of the checksum computation for that particular TCP segment is 0x357c, which is used to check if an error has occurred while sending the packet.

10. *Urgent Pointer*:
    - *Value*: 0x0000
    - *Description*: The value indicates that the segment does not contain any urgent data and the URG flag is not active for that segment. As noted earlier, only ACK and PSH flags are active.

11. *Options*:
    - *Value*: 0x0101080a438b5518df08c81e
    - *Description*:
      - 0x01 is a NOP (No-Operation) option for padding.
      - 0x08 indicates a Timestamp option with a length of 10 bytes.
      - 0x438b5518 is the Timestamp value.
      - 0xdf08c81e is the Timestamp Echo Reply value.

### TCP Payload
This particular packet has a size of 39 bytes of TCP payload.