Connection Establishment
TCP Connection Initialization (Three-Way Handshake)
SYN (Synchronize):The client sends a SYN packet to the server to initiate a connection. This packet contains the client's initial sequence number (ISN).

SYN-ACK (Synchronize-Acknowledge):The server responds with a SYN-ACK packet, acknowledging the client's SYN and providing its own ISN.

ACK (Acknowledge):The client sends an ACK packet back to the server, acknowledging the server's SYN-ACK. The connection is now established.

The first three frame shown in the picture above is the packets of TCP connection

**[SYN] Seq=0**,The client initiates the connection with a SYN packet and sets the initial sequence number (ISN) to 0. The SYN packet itself consumes 1 sequence number.

**[SYN, ACK] Seq=0 Ack=1**, The server responds with a SYN-ACK packet. The server's sequence number is set to 0 (its ISN), and it acknowledges the client's SYN by setting the acknowledgment number to 1 (Ack=1). This is because the SYN packet from the client consumed 1 sequence number.

**[ACK] Seq=1 Ack=1**, The client acknowledges the server's SYN-ACK by sending an ACK packet. The client's sequence number is incremented to 1 (Seq=1) to acknowledge the receipt of the server's SYN. The acknowledgment number is set to 1 (Ack=1) because it acknowledges the server's SYN, which consumed 1 sequence number.



Connection Maintenance(Data transfer)
Once the TCP connection is established, the client can send an HTTP request to the server and receive an HTTP response. As you can see in the picture above from frame 457 to 462.

The http request is made by the client using GET method whose length is 825 bytes that means 825 bytes transferred to server in frame 457.

Which then Acknowledge by server by incrementing ACK=len+1=826([ACK] Seq=1 Ack=826), that means yes it heard 825 bytes by pushing the 278 bytes length data ([PSH][ACK] Seq=1 Ack=826 Len=278) to client. Again which is acknowledge by client by incremneting ACK=len+1=279 and sequence number is set to 826([ACK] Seq=826 Ack=279).

After that server pushesh the required data(line based text data: text/html technically index.html) which is of 1046 bytes in total including http.

Again client acknowledges it by incearsing Ack=len+1=1047 ([ACK] Seq=826 Ack=1047)



Connection termination
After the http transaction the TCP connection is terminated. When terminating a TCP connection, a four-way handshake is typically used. This involves both sides sending and acknowledging FIN packets.

[FIN, ACK] Seq=826 Ack=1047 The client initiates the termination with a FIN packet. The sequence number is 826(data sent to server). The acknowledgment number is 1047, acknowledging the data received from the server.

[ACK] Seq=1047 Ack=827 The server acknowledges the client’s FIN packet by incrementing the acknowledgment number, Ack=ISN of client+1= 827. The server's sequence number is 1047.

**[FIN, ACK] Seq=1047 Ack=827**Again, The server also initiates the termination with a FIN packet. The sequence number is 1047(data sent to client). The acknowledgment number is 827, acknowledging the last data received from the client including the FIN packet.

[ACK] Seq=827 Ack=1048 The client also acknowledges the server’s FIN packet by incrementing the acknowledgment number, Ack=ISN of server+1= 1048. The client's sequence number is 827.