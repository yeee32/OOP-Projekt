#include <iostream>
#include <vector>
using namespace std;

class PackageBox;
class Person;
class Sender;
class Receiver;
class Packet;
class Package;
class Letter;
class PostalOffice;

class Person{
    private:
        int id;
        string name;
        string surname;
        string address;
    public:
        Person(int id, string name, string surname, string address);
        int GetId();
        string GetName();
        string GetSurname();
        string GetAddress();
        void PrintInfo();
};

Person::Person(int id, string name, string surname, string address){
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->address = address;
}

int Person::GetId(){
    return this->id;
}

string Person::GetName(){
    return this->name;
}

string Person::GetSurname(){
    return this->surname;
}

string Person::GetAddress(){
    return this->address;
}

void Person::PrintInfo(){
    cout << "ID: "<< this->GetId(); 
    cout << ", Name: " << this->GetName();
    cout << ", Surname: " << this->GetSurname();
    cout << ", Address: " << this->GetAddress();
}
class Packet{   
    private:
        Sender* sender;
        Receiver* receiver;
    public:
        virtual int GetId() = 0;
        virtual float GetVolume() = 0;
        virtual float GetWeight() = 0;
        virtual vector<float> GetDimensions() = 0;
        virtual void PrintInfo() = 0;
        virtual ~Packet() {}; 
};

class Package : public Packet{
    private:
        int id;
        float width;
        float height;
        float length;
        float weight;
    public:
        Package(int id, float w, float h, float l, float weight);
        int GetId() override { return this->id; };

        float GetVolume() override {
            return this->width * this->height * this->length;
        }

        float GetWeight() override {
            return this->weight;
        }

        vector<float> GetDimensions() override {
            vector<float> dims = {this->width, this->height, this->length};
            return dims;
        }

        void PrintInfo() override {
            cout << "ID: " << this->id;
            cout << " width: " << this->width;
            cout << " height: " << this->height;
            cout << " length: " << this->length;
            cout << " weight: " << this->weight;
            cout << endl;
        }
};

Package::Package(int id, float w, float h, float l, float weight){
    this->id = id;
    this->width = w;
    this->height = h;
    this->length = l;
    this->weight = weight;
}

class Letter : public Packet{
    private:
        int id;
        float height;
        float length;
    public:
        Letter(int id, int h, int l);
        int GetId() override { 
            return this->id; 
        };
        float GetVolume() override {
            return height * length;
        }
        float GetWeight() override { return 0.0; };
        vector<float> GetDimensions() override { return {this->height, this->length}; };

        void PrintInfo() override {
            cout << "ID: " << this->id;
            cout << " height: " << this->height;
            cout << " length: " << this->length;
            cout << endl;
        }
};

Letter::Letter(int id, int h, int l){
    this->id = id;
    this->height = h;
    this->length = l;
}

class PostalOffice{
    private:
        string name;
        float maxWeight;
        float maxW; 
        float maxH;
        float maxL;
        float modif;
    public:
        PostalOffice(string name, float modif);
        float CalculatePrice(Packet* packet);
        float CalculatePrice(Packet* packet, float discount);
        string GetName();
        void SetMaxDimensions(float maxW, float maxH, float maxL); // dimensions for package
        void SetMaxDimensions(float maxH, float maxL); // dimensions for letter
        vector<float> GetMaxDimensons();
        void SetMaxWeight(float weight);
        float GetMaxWeight();
    };

PostalOffice::PostalOffice(string name, float modif){
    this->name = name;
    this->modif = modif;
}

string PostalOffice::GetName(){
    return this->name;
}

void PostalOffice::SetMaxWeight(float weight){
    this->maxWeight = weight;
}

float PostalOffice::GetMaxWeight(){
    return this->maxWeight;
}

float PostalOffice::CalculatePrice(Packet* packet){
    const float minPrice = 20.0; 
    float volume = packet->GetVolume();     
    float weight = packet->GetWeight();    
    float price = 0.0;

    if (weight > 0){
        const float pricePerKg = 10.0;
        const float pricePerCubed = this->modif;

        price = pricePerKg * weight + pricePerCubed * (volume / 1000.0);
    } 
    else{

        const float pricePerSquared = this->modif;
        price = pricePerSquared * (volume / 100.0); 
    }


    price = price * this->modif;
    if(price < minPrice){
        return minPrice;
    } 
    else{
        return price;
    }
}

float PostalOffice::CalculatePrice(Packet* packet, float discount){
    return CalculatePrice(packet) * (1 - discount);
}

void PostalOffice::SetMaxDimensions(float maxH, float maxL){
    this->maxH = maxH;
    this->maxL = maxL;
}

void PostalOffice::SetMaxDimensions(float maxW, float maxH, float maxL){
    this->maxW = maxW;
    this->maxH = maxH;
    this->maxL = maxL;
}

vector<float> PostalOffice::GetMaxDimensons(){
    vector<float> maxDims = {this->maxW, this->maxH, this->maxL};
    return maxDims;
}

// neco jako z-box od zásilkovny
// address capacity
class PackageBox{
    private:
        string address;
        int capacity;
        int availableBoxes;
        PostalOffice* postOffice;
    public:
        PackageBox(string address, int capacity, PostalOffice* postaloffice);
        bool CanPacketFit(Packet* packet);
        bool IsValidWeight(Packet* packet);
        void InsertPackage(Packet* packet);
        void ExtractPackage(Packet* packet);
        int GetAvailableBoxes();
        string GetAddress();
        void PrintInfo();
};

PackageBox::PackageBox(string address, int capacity, PostalOffice* postaloffice){
    this->postOffice = postaloffice;
    this->address = address;
    this->capacity = capacity;
    this->availableBoxes = this->capacity;
}

void PackageBox::InsertPackage(Packet* packet){
    if(this->CanPacketFit(packet) && this->IsValidWeight(packet)){
        this->availableBoxes--;
    }
}

void PackageBox::ExtractPackage(Packet* packet){
    this->availableBoxes++;
}

int PackageBox::GetAvailableBoxes(){
    return this->availableBoxes;
}

string PackageBox::GetAddress(){
    return this->address;
}

void PackageBox::PrintInfo(){
    cout << "The postal box at: '" << this->GetAddress();
    cout << "' has " << this->GetAvailableBoxes() << " available boxes!" << endl;
}

bool PackageBox::CanPacketFit(Packet* packet){
    vector<float> packetDims = packet->GetDimensions();
    vector<float> maxDims = this->postOffice->GetMaxDimensons();

    if(packetDims[0] > maxDims[0]){
        cout << "Packet["<< packet->GetId() << "]: width is too large, ";
        return false;
    }
    else if(packetDims[1] > maxDims[1]){
        cout << "Packet[" << packet->GetId() << "]: heigth is too large, ";
        return false;
    }
    else if(packetDims[2] > maxDims[2]){
        cout << "Packet[" << packet->GetId() << "]: length is too large, ";
        return false;
    }
    else{
        cout << "Packet[" << packet->GetId() << "]: packet can fit, " << endl;
        return true;
    }
}

bool PackageBox::IsValidWeight(Packet* packet){
    if(packet->GetWeight() > postOffice->GetMaxWeight()){
        cout << "packet is too heavy" << endl;
        return false;
    }
    cout << "packet is valid weight" << endl;
    return true;
}


class Sender : public Person{
    private:
        vector<Packet*> sentPackets;
        int numSentPackets;
    public:
        Sender(int id, string name, string surname, string address) : Person(id, name, surname, address) {} 
        void Send(Packet* packet, Receiver* receiver);
        void PrintInfo();
};

void Sender::PrintInfo(){
    Person::PrintInfo();    
    cout << ", Sent packets: " << this->numSentPackets;
    cout << endl;
}

void Sender::Send(Packet* packet, Receiver* receiver){
    this->sentPackets.push_back(packet);
    this->numSentPackets++;
}

class Receiver : public Person{
    private:
        vector<Packet*> receivedPackets;
        int numReceivedPackets;
    public:
        Receiver(int id, string name, string surname, string address) : Person(id, name, surname, address) {}
        void GetPacket(Packet* packet, PackageBox* PackageBox);
        void PrintInfo();
};

void Receiver::GetPacket(Packet* packet, PackageBox* packageBox){
    this->receivedPackets.push_back(packet);
    this->numReceivedPackets++;
    packageBox->ExtractPackage(packet);
}

void Receiver::PrintInfo(){
    Person::PrintInfo();
    cout << ", Received packets: " << this->numReceivedPackets;
    cout << endl;
}


// Neco jako zásilkovna: postovni system
int main(){
    PostalOffice* postalOffice1 = new PostalOffice("Česká Pošta", 1.2);
    PostalOffice* postalOffice2 = new PostalOffice("BOX Pošta", 1.5);

    postalOffice1->SetMaxDimensions(70, 70, 70);
    postalOffice1->SetMaxWeight(15);

    Sender* sender1 = new Sender(0, "Jan", "Ošík", "Zelená 35");
    Sender* sender2 = new Sender(1, "Pavel", "Loupák", "Pod Kotlem 5");
    Sender* sender3 = new Sender(2, "Lucie", "Bílá", "Něco 75");

    Receiver* receiver1 = new Receiver(0, "František", "Dobrota", "Banánová 12");
    Receiver* receiver2 = new Receiver(1, "Martin", "Down", "Hrušková 31");
    Receiver* receiver3 = new Receiver(2, "John", "Doe", "Sesame Street 11");

    Packet* packet1 = new Package(0, 10, 20, 25, 13);
    Packet* packet2 = new Letter(1, 10, 10);
    Packet* packet3 = new Package(2, 120, 30, 25, 5);
    Packet* packet4 = new Package(3, 6, 7, 5, 2);
    Packet* packet5 = new Letter(4, 5, 5);
    Packet* packet6 = new Package(5, 40, 50, 40, 20);

    vector<Packet*> packets = {packet1, packet2, packet3, packet4, packet5, packet6};

    vector<Sender*> senders = {sender1, sender2, sender3};

    vector<Receiver*> receivers = {receiver1, receiver2, receiver3};

    PackageBox* packageBox1 = new PackageBox("Na duze 14", 20, postalOffice1);
    packageBox1->PrintInfo();

    for(auto& pack : packets){
        packageBox1->InsertPackage(pack);
    }

    cout << "After inserting packages:" << endl;
    packageBox1->PrintInfo();

    cout << "-----------------------------------------" << endl;

    receiver1->GetPacket(packet1, packageBox1);
    receiver2->GetPacket(packet2, packageBox1);
    cout << "After receiver gets packages:" << endl;
    packageBox1->PrintInfo();

    cout << "-----------------------------------------" << endl;

    sender1->Send(packet1, receiver1);
    sender1->Send(packet2, receiver2);

    cout << "Sender Info:" << endl;
    for(auto& sender: senders){
        sender->PrintInfo();
    }

    cout << "-----------------------------------------" << endl;

    cout << "Receiver Info:" << endl;
    for(auto& receiver: receivers){
        receiver->PrintInfo();
    }

    cout << "-----------------------------------------" << endl;

    cout << "calculating prices at: " << postalOffice1->GetName() << endl;
    for(auto& pack : packets){
        cout << "Packet[" << pack->GetId() << "] costs: " << postalOffice1->CalculatePrice(pack) << " Kc" << endl;
    }
    cout << endl;
    cout << "calculating prices at: " << postalOffice2->GetName() << endl;
    for(auto& pack : packets){
        cout << "Packet[" << pack->GetId() << "] costs: " << postalOffice2->CalculatePrice(pack) << " Kc" << endl;
    }
    cout << "-----------------------------------------" << endl;

    cout << "calculating prices at: " << postalOffice2->GetName() << " with discount"<< endl;
    for(auto& pack : packets){
        cout << "Packet[" << pack->GetId() << "] costs: " << postalOffice2->CalculatePrice(pack, 0.3) << " Kc" << endl;
    }
    cout << "-----------------------------------------" << endl;

    cout << "Packets info" << endl;
    for(auto& packet : packets){
        cout << "Packet: ";
        packet->PrintInfo();
    }
    cout << "-----------------------------------------" << endl;

    return 0;
}
