packet TCPSegment
{
    unsigned short srcPort = 0;
    unsigned short destPort = 0;
    unsigned int seqNr = 0;
    unsigned int ackNr = 0;

    bool cwr = false;
    bool ece = false;
    bool urg = false;
    bool ack = false;
    bool psh = false;
    bool rst = false;
    bool syn = false;
    bool fin = false;

    char dataOffset = 0;
    unsigned short dataWindow = 0;
}
