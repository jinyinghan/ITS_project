#include <iostream>
#include <string>
using namespace std;

class animal
{
    public:
        animal(string n){ name = n; };
        string GetName(){ return name; };
        virtual float GetWeight()= 0;
    private :
        string name;

};

class dog :public animal
{
    public:
        dog(float w, string n) :animal(n){ weight = w; };
        float GetWeight() { return weight; };
    private:
        float weight;
};

class cat : public animal
{
    public:
        cat(float w, string n) :animal(n){ weight = w; };
        float GetWeight() { return weight; };
    private:
        float weight;
};
int main()
{
    dog d(2,"dog1");
    cat c(1, "cat1");
    cout << d.GetName() << ":" << d.GetWeight() << "KG" << endl;
    cout << c.GetName() << ":" << c.GetWeight() << "KG" << endl;
}
