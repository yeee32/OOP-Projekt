#include <iostream>
#include <vector>
using namespace std;

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

class Sender : public Person{
    private:
        int packagesSent;
};


class Receiver : public Person{

};

class Packet{
    private:
        Sender* sender;
        Receiver* receiver;
    public:
        virtual int GetId() = 0;
        virtual float GetVolume() = 0;
        virtual float GetWeight() = 0;
        virtual vector<float> GetDimensions() = 0;
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
        int GetId() override { return this->id; };
        float GetVolume() override {
            return height * length;
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
    public:
        PostalOffice(string name);
        float CalculatePrice(Packet* packet);
        float CalculatePrice(Packet* packet, float discount);
        string GetName();
        void SetMaxDimensions(float maxW, float maxH, float maxL);
        vector<float> GetMaxDimensons();
        void SetMaxWeight(float weight);
        float GetMaxWeight();
    };

PostalOffice::PostalOffice(string name){
    this->name = name;
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
    int num = 25;
    return (packet->GetVolume() / 100 + packet->GetWeight()) * num;
}

float PostalOffice::CalculatePrice(Packet* packet, float discount){
    return CalculatePrice(packet) * (1 - discount);
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
class PackageBox{
    public:
        bool CanPacketFit(Packet* packet, PostalOffice* postOffice);
        bool IsValidWeight(Packet* packet, PostalOffice* postOffice);
};

bool PackageBox::CanPacketFit(Packet* packet, PostalOffice* postOffice){
    vector<float> packetDims = packet->GetDimensions();
    vector<float> maxDims = postOffice->GetMaxDimensons();

    if(packetDims[0] > maxDims[0]){
        cout << "width is too large" << endl;
        return false;
    }
    else if(packetDims[1] > maxDims[1]){
        cout << "heigth is too large" << endl;
        return false;
    }
    else if(packetDims[2] > maxDims[2]){
        cout << "length is too large" << endl;
        return false;
    }
    else{
        cout << "packet can fit :)" << endl;
        return true;
    }
}

bool PackageBox::IsValidWeight(Packet* packet, PostalOffice* postOffice){
    if(packet->GetWeight() > postOffice->GetMaxWeight()){
        return false;
    }
    return true;
}

class Depo{

};

// Neco jako zásilkovna: postovni system
int main(){

    Person* person1 = new Person(0, "Jan", "Ošík", "Zelená 35");
    Person* person2 = new Person(1, "František", "Dobrota", "Banánová 12");

    cout << person1->GetName() << endl;
    cout << person1->GetAddress() << endl;

    Packet* packet1 = new Package(0, 10, 20, 25, 13);

    cout << packet1->GetVolume() << endl;
    vector<float> packet1_dims = packet1->GetDimensions();
    for(auto& dim : packet1_dims){
        cout << dim << " " ;
    }
    cout << endl;

    return 0;
}
