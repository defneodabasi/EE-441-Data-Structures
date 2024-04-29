#include "adhoc.h"
#include "queue.cpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Hash function:
size_t calculateHash(string message, int sourceId, int destId) {
    size_t hash_value = 0;
    for (char c: message) { //for (int i =0;i<message.size(),i++)
        hash_value = hash_value * 31 + c;
    }
    return hash_value ^ sourceId ^ destId;
}

//Packet class
Packet::Packet(){
    message = "";
    sourceId = 0;
    destId = 0;
    hash = calculateHash(message, sourceId, destId);
}

Packet::Packet(int SourceId, int DestId, string Message){
    message = Message;
    sourceId = SourceId;
    destId = DestId;
    hash = calculateHash(message, sourceId, destId);
}


int Packet::getSourceId(){
    return sourceId;
}

int Packet::getDestId(){
    return destId;
}

string Packet::getMessage(){
    return message;
}

bool Packet::checkIntegrity(){
    //cout << "hash: "<< hash. <<end;
    //cout << "calculated hash: " << calculateHash(message,sourceId,destId) << endl;
    if(hash == calculateHash(message,sourceId,destId)){
        return true;

    }else{
        return false;
    }
}

void Packet::corrupt(){

    if (message.empty()) {
        return;
    }

    // Finding the index to be changed.
    int index = rand() % message.length();

    // Generate a random ASCII character (0 to 127 a total of 128 chars)
    int num = rand() % 128;

    char randomChar = static_cast<char>(num);
    // Modify the message with the randomChar
    message[index] = randomChar;
}

//MacPacket class

//Implementation of the default constructor.
MacPacket::MacPacket(){
    macSourceId = 0;
    macDestId = 0;
    type = MacPacketType::Empty;
}

//Implementation of the constructor

MacPacket::MacPacket(MacPacketType Type, int macsourceid, int macdestid, vector<int>& Path, Packet& Packet){
    type = Type;
    macSourceId = macsourceid;
    macDestId = macdestid;
    path = Path;
    packet = Packet;
}

//Implement the static functions which are shorthands for creating certain types of mac packets.

MacPacket MacPacket::createMessagePacket(int SourceId, int DestId, vector<int>& Path, Packet& Packet){
    return MacPacket(MacPacketType::Message, SourceId, DestId, Path, Packet);
}

MacPacket MacPacket::createSuccessPacket(int SourceId, int DestId, vector<int>& Path){
    Packet packet = Packet();
    return MacPacket(MacPacketType::Success, SourceId, DestId, Path, packet);
}

MacPacket MacPacket::createFailurePacket(int SourceId, int DestId, vector<int>& Path){
    Packet packet = Packet();
    return MacPacket(MacPacketType::Failure, SourceId, DestId, Path, packet);
}

//Implementation of the functions

MacPacketType MacPacket::getType() {
    return type;
}

int MacPacket::getMacSourceId() {
    return macSourceId;
}

int MacPacket::getMacDestId() {
    return macDestId;
}

vector<int>& MacPacket::getPath() {
    return path;
}

Packet& MacPacket::getPacket()  {
    return packet;
}

//Node Class

//Default constructor
Node::Node(){
    id = 0; //Invalid/Empty value
}

//Constructor
Node::Node(int Id, vector<int>& Neighbors){
    id = Id;
    neighbors = Neighbors;
}

int Node::getId(){
    return id;
}

vector<int>& Node::getNeighbors(){
    return neighbors;
}

MacPacket Node::receive(MacPacket packet){
    if (packet.getType() == MacPacketType::Message){
        // message is not broken
        /*
        cout << "NodeId " << id << endl;
        cout<<"inside message"<<endl;
        cout << "macSourceId " << packet.getMacSourceId() <<endl;
        cout << "macDestId " << packet.getMacDestId() <<endl;
        cout << " " << endl;
        */
        if (packet.getPacket().checkIntegrity()){
            buffer = packet;
            // Final destination is reached (6)
            if (id == packet.getPacket().getDestId()){
                cout << "[Node " << id << "] Message successfully received: \""<< packet.getPacket().getMessage();
                cout << "\". Sending acknowledgment to Node "<< packet.getMacSourceId() <<"..." << endl;
                //if a reached to the final destination successfully

                //vector<int> reversePath(path.rbegin(), path.rend());
                return MacPacket::createSuccessPacket(id, packet.getMacSourceId(), packet.getPath());
            } else if ((id == packet.getMacDestId()) || (id == packet.getPacket().getSourceId())){
                vector<int> temp_path = packet.getPath();
                int nextNodeId = 0;
                for(int p = 0; p < temp_path.size(); p++){
                    if(temp_path[p] == id){
                        nextNodeId = temp_path[p+1];
                        break;
                    }
                }
                cout <<"[Node " << id << "] Packet received. Sending to Node "<< nextNodeId <<"..."<< endl;
                return MacPacket::createMessagePacket(id, nextNodeId, temp_path, packet.getPacket());
            }
        }else{ // message is broken
            cout <<"[Node " << id << "] Packet corrupted: \""<< packet.getPacket().getMessage();
            cout <<"\". Requesting resend from Node "<< packet.getMacSourceId()<<"..."<<endl;
            return MacPacket::createFailurePacket(id, packet.getMacSourceId(), packet.getPath());
        }

    }else if(packet.getType() == MacPacketType::Success){
        /*
        cout << "NodeId " << id << endl;
        cout<<"inside message"<<endl;
        cout << "macSourceId " << packet.getMacSourceId() <<endl;
        cout << "macDestId " << packet.getMacDestId() <<endl;
        cout << " " << endl;
        */
        buffer = packet;
        if (id == packet.getPath().at(0)){ //if the packet is success packet in source.
            //the node is source return empty mac packet
            cout <<"[Node " << id << "] Acknowledgment received." << endl;
            return MacPacket(); //end the simulation
        }else if (id == packet.getMacDestId()){
            vector<int> temp_path = packet.getPath();
            int prevNodeId = 0;
            for(int p = 0; p < temp_path.size(); p++){
                if(temp_path[p] == id){
                    //take the prev of id
                    prevNodeId = temp_path[p-1];
                    break;
                }
            }
            cout <<"[Node " << id << "] Acknowledgment received. Sending to Node " << prevNodeId << "..." << endl;
            return MacPacket::createSuccessPacket(id, prevNodeId, packet.getPath());
        }
    }else if(packet.getType() == MacPacketType::Failure){
        //[Node 4] Resending previous packet to Node 6...
        cout <<"[Node " << id << "] Resending previous packet to Node " << packet.getMacSourceId() << "..." << endl;
        return MacPacket::createMessagePacket(id, packet.getMacSourceId(), packet.getPath(), buffer.getPacket());

    }

}

//Network class
Network::Network(float corr_rate){
    corruptionRate = corr_rate;
}

//returns the pointer which is pointing at the node with the given input id
Node* Network::getNode(int node_id){
    for (Node& node : nodes){
        if (node.getId() == node_id){
            return &node; //return Node* is referred as the address of that node
        }
    }
    //if the node is not found
    return nullptr;
}

void Network::addNode(int node_id, vector<int>& node_neighbors){
    //Creating a new node
    Node newNode = Node(node_id, node_neighbors);

    //adding the new node to the network
    nodes.push_back(newNode);

    //Now neighbors of the nodes will be updated
    for (int neighborId : node_neighbors){
        newNode.getNeighbors().push_back(neighborId);
    }
    /*
    cout << "Node :" << node_id << " is created with following neighbors : ";
    for (int neighbor : newNode->getNeighbors()){
        cout << neighbor << " ";
    }
    cout << endl;

    cout << "Nodes in the network are: ";
    for(Node node : nodes){
        cout << node.getId() << " ";
    }
    cout << endl;

    */
}

//now I should find the node to be removed and remove this node from the other neighbors as well
void Network::removeNode(int node_id){

    Node* remove_node = getNode(node_id);

    if(remove_node){ //if remove node exists

        //cout << "Node " << node_id << " removed from the network." << endl;


        for (int neighbor_id : remove_node->getNeighbors()){

            Node* neighbor_node = getNode(neighbor_id);
            if(neighbor_node){//if neighbor node exists

                vector<int>& my_neighbors = neighbor_node->getNeighbors();

                //Removing the reference to the node being removed
                for (int i = my_neighbors.size()-1; i >= 0; i--){

                    if (my_neighbors[i] == node_id){

                        my_neighbors.erase(my_neighbors.begin() + i);
                        break;

                    }

                }

            }
        }
        for(int j=nodes.size()-1; j>= 0; j--){
            if(nodes.at(j).getId() == node_id){
                nodes.erase(nodes.begin()+j);
                break;
            }
        }

    }

    /*
    cout << "Nodes in the network are: "<<endl;
    for(Node node : nodes){
        cout <<"Node: " <<node.getId() << "with neighbors: ";
        for (int id: node.getNeighbors()){
            cout <<id;
        }
        cout << endl;
    }
    */

}

vector<int> Network::calculatePath(int source_id, int dest_id){

    //This part is conducted for the case that
    //if some nodes are deleted our visited and prev arrays size should still be including the maximum node_id

    int max_val = 0;
    for (Node node: nodes){

        if (node.getId() > max_val){
            max_val = node.getId();
        }
    }

    Queue q;
    vector<int> parent(max_val+1, -1); // Using -1 to indicate no parent
    vector<bool> visited(max_val+1, false);

    // Start from the source
    q.QInsert(source_id);
    visited[source_id] = true;

    //BFS algorithm:
    while (!q.QEmpty()) {
        int current = q.QDelete();

        // Check if we reached the destination
        if (current == dest_id) {
            break;
        }

        // Process neighbors
        Node* currentNode = getNode(current);
        if (currentNode != nullptr) {
            for (int neighbor : currentNode->getNeighbors()) {
                if (!visited[neighbor]) {
                    q.QInsert(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = current;

                }
            }
        }
    }

    // Check if a path exists
    if (parent[dest_id] == -1) {
        cout << "No such path exists" <<endl;
        return {};  // Return an empty vector if no path exists
    }

    // Reconstruct the path from source to destination
    vector<int> path;
    //very clean way to add to the path
    for (int at = dest_id; at != -1; at = parent[at]) {
        //insert adds to the beginning of the vector
        path.insert(path.begin(), at);
    }

    return path;
}

void Network::simulate(Packet packet) {
    // Calculate the path
    vector<int> calculatedPath = calculatePath(packet.getSourceId(), packet.getDestId());

    // Print the calculated path
    cout << "Message to send: \"" << packet.getMessage() << "\". Path: ";
    for (int node : calculatedPath) {
        cout << "-> " << node << " ";
    }
    cout << endl;

    // Create the initial MacPacket
    MacPacket macPacket = MacPacket::createMessagePacket(calculatedPath[0], calculatedPath[1], calculatedPath, packet);

    // Send the packet through the path
    for (size_t i = 0; i < calculatedPath.size(); ) {
        Node* currentNode = getNode(calculatedPath[i]);
        MacPacket response = currentNode->receive(macPacket);

        // Check the type of the response packet
        if (response.getType() == MacPacketType::Empty) {
            // End of simulation
            break;
        } else if (response.getType() == MacPacketType::Success || response.getType() == MacPacketType::Failure) {
            // Move to the previous node for Success or Failure packets
            if (i > 0) i--;
        } else {
            // Move to the next node for Message packets
            if (i < calculatedPath.size() - 1) i++;
        }

        // Check for corruption
        if (response.getType() == MacPacketType::Message && (float) rand() / RAND_MAX < corruptionRate) {
            response.getPacket().corrupt();
        }

        macPacket = response;
    }
}
