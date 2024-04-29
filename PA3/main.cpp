#include "adhoc.cpp"


using namespace std;

int main()
{
 //   srand(static_cast<unsigned>(time(nullptr)));
 //   char randomChar = static_cast<char>(rand() % 128);
 //   cout << "Random ASCII Character " << randomChar << endl;
    /*
    string message = "Hello world!";

    vector<int> path = {1, 4, 6};

    vector<int> neig_1 = {4};
    vector<int> neig_4 = {1,6};
    vector<int> neig_6 = {4};

    Node node_1 = Node(1 , neig_1);
    Node node_4 = Node(4 , neig_4);
    Node node_6 = Node(6 , neig_6);

    Packet mypacket = Packet(1,6, message);

    MacPacket mymacpacket = MacPacket(MacPacketType::Message,1,4,path, mypacket);

    MacPacket temp1  = node_1.receive(mymacpacket);
    MacPacket temp2 = node_4.receive(temp1);
    temp2.getPacket().corrupt();

    MacPacket temp3 = node_4.receive(node_6.receive(temp2));
    temp3.getPacket().corrupt();

    node_1.receive(node_4.receive(node_6.receive(node_4.receive(node_6.receive(temp3)))));

    */
    srand(static_cast<unsigned>(time(0)));
    Network network(0.3); //assuming a corruption rate of 0.1

    vector<int> neighbors1 = {2,3,4};
    network.addNode(1, neighbors1);

    vector<int> neighbors2 = {1,3,4,5};
    network.addNode(2, neighbors2);

    vector<int> neighbors3 = {1,2,4};
    network.addNode(3, neighbors3);

    vector<int> neighbors4 = {1,2,3,6};
    network.addNode(4, neighbors4);

    vector<int> neighbors5 = {2,6,7};
    network.addNode(5, neighbors5);

    vector<int> neighbors6 = {4,5,7};
    network.addNode(6, neighbors6);

    vector<int> neighbors7 = {5,6};
    network.addNode(7, neighbors7);

    Packet packet(1, 7, "Hello world!");

    // Simulate the packet sending process
    network.simulate(packet);


    return 0;

}
