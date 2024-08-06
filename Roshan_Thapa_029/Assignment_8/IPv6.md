# Assignment 8

## Length of an IPv6 Header

The IPv6 header is 40 bytes long. Unlike the IPv4 header, the IPv6 header has a fixed length, simplifying processing by network devices.

## Fields in the IPv6 Header and Their Purposes

- **Version (4 bits):** Identifies the IP protocol version, always set to 6 for IPv6.
- **Traffic Class (8 bits):** Used for Quality of Service (QoS) to prioritize types of traffic and manage congestion.
- **Flow Label (20 bits):** Labels packets belonging to the same flow, requiring special handling by routers like real-time service or resource reservation.
- **Payload Length (16 bits):** Specifies the length of the payload, including extension headers, in bytes. The maximum value is 65535 bytes.
- **Next Header (8 bits):** Identifies the type of header following the IPv6 header, such as an upper-layer protocol (e.g., TCP, UDP) or an extension header. This is similar to the Protocol field in IPv4.
- **Hop Limit (8 bits):** Specifies the maximum number of hops a packet can take. Each router decreases this value by one, and the packet is discarded when it reaches zero.
- **Source Address (128 bits / 16 bytes):** The IPv6 address of the originating node.
- **Destination Address (128 bits / 16 bytes):** The IPv6 address of the destination node.

## IPv6 Packet Analysis in Wireshark

When analyzing an IPv6 packet in Wireshark, the header fields and their purposes are as follows:

- **Version (4 bits):**
  - **Value:** 6/0110
  - **Purpose:** Indicates the IP version, which is IPv6.
- **Traffic Class (8 bits):**
  - **Value:** 0x00 (DSCP: CS0, ECN: Not-ECT)
  - **Purpose:** Used for QoS to differentiate and prioritize types of traffic.
- **Flow Label (20 bits):**
  - **Value:** 0x5f9a9 (393481 in decimal)
  - **Purpose:** Labels packets belonging to the same flow, requiring special handling by routers.
- **Payload Length (16 bits):**
  - **Value:** 76
  - **Purpose:** Specifies the length of the payload, including any extension headers in bytes, excluding the 40-byte base header.
- **Next Header (8 bits):**
  - **Value:** 17 (UDP)
  - **Purpose:** Identifies the type of header following the IPv6 header. In this case, it is UDP.
- **Hop Limit (8 bits):**
  - **Value:** 1
  - **Purpose:** Specifies the maximum number of hops the packet can traverse. Each router forwards the packet by decrementing this value by one, and the packet is discarded when it reaches zero.
- **Source Address (128 bits / 16 bytes):**
  - **Value:** fe80::4319:9907:3fc7:9fa4
  - **Purpose:** The IPv6 address of the originating node.
- **Destination Address (128 bits / 16 bytes):**
  - **Value:** ff02::fb
  - **Purpose:** The IPv6 address of the destination node.
