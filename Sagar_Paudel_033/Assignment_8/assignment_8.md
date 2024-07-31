IN the programming language of your choice write a web application that allows you to upload a file?
Capture a traffic in wireshark while uploading a file. Follow the TCP stream and explain conncection initialization , connection maintainance and conncection termination.

**==> TCP stream into three main phases: connection initiation, connection maintenance, and connection termination.**

### Connection Initiation

TCP connections are established using a three-way handshake:

1. **SYN (Synchronize)**:
    - The client sends a TCP packet with the SYN flag set to the server to initiate a connection.
    - This packet includes an initial sequence number (ISN) chosen by the client.
    
    
2. **SYN-ACK (Synchronize-Acknowledge)**:
    - The server responds with a TCP packet with both SYN and ACK flags set.
    - This packet acknowledges the client's SYN packet and provides the server's ISN.
    
    
3. **ACK (Acknowledge)**:
    - The client sends an ACK packet back to the server.
    - This packet acknowledges the server's SYN-ACK packet.
       

### Connection Maintenance

Once the connection is established, data transfer begins. For a file upload:

1. **HTTP Request**:
    - The client sends an HTTP POST request with the file data.
    - The data is sent in segments, each contained within its own TCP packet.

    
2. **HTTP Response**:
    - The server processes the request and sends an HTTP response.
    - This might include status codes like 200 (OK) indicating the file was uploaded successfully.
     

### Connection Termination

TCP connections are terminated using a four-way handshake:

1. **FIN (Finish)**:
    - The client or server initiates the termination by sending a FIN packet.
    - This indicates that it has finished sending data.
    
    
2. **ACK (Acknowledge)**:
    - The receiver acknowledges the FIN packet.
    
    
3. **FIN (Finish)**:
    - The receiver then sends its own FIN packet to indicate it has finished sending data.
    
    
4. **ACK (Acknowledge)**:
    - The original sender acknowledges the FIN packet, completing the termination process.
    
