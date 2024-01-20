package src.tcp;

simple TCP
{
    parameters:
        int dataOffset = default(20);
        int initialState = default(10);
        double packetLossProb = default(0.1);
        double retransTimeout = default(1.0);
    gates:
        input fromUpperLayer;
        output toUpperLayer;
        input fromLowerLayer;
        output toLowerLayer;
}
