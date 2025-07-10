#include <iostream>
#include <string>

using namespace std;

class Channel {
public:
    virtual void send() = 0;
    virtual ~Channel() {};
};

class Telephone : public Channel {
private:
    string number;
public:
    Telephone(string &n) : number{ n } {}
    virtual void send() override {
        if (rand() % 10 < 3)
            throw exception("line is busy");
        cout << "dialing: " << number << '\n';
    }
    ~Telephone() {};
};

class Fax : public Telephone {
public:
    Fax(string& n) : Telephone(n) {}
    void send() override {
        Telephone::send();
        cout << "sending fax\n";
    }
};

class SMS : public Telephone {
public:
    SMS(string& n) : Telephone(n) {}
    void send() override {
        Telephone::send();
        cout << "sending sms\n";
    }
};

class Failover : public Channel {
private:
    Channel* c1, * c2;
public:
    Failover(Channel* c1, Channel* c2) : c1{c1}, c2{ c2 } {}
    ~Failover() {
        delete c1;
        delete c2;
    }

    void send() override {
        try {
            c1->send();
        }
        catch (exception&) {
            c2->send();
        }
    }
};

class Contact : public Channel {
private:
    Channel* c1, * c2, * c3;
public:
    Contact(Channel* c1, Channel* c2, Channel* c3) : c1{ c1 }, c2{ c2 }, c3{ c3 } {}
    ~Contact() {
        delete c1;
        delete c2;
        delete c3;
    }

    void sendAlarm() {
        while (true) {
            try {
                c1->send();
                return;
            }
            catch (exception&) {
                try {
                    c2->send();
                    return;
                }
                catch (exception&) {
                    try {
                        c3->send();
                        return;
                    }
                    catch (exception&) {}
                }
            }
        }
    }

    void send() {};
};

void createContact(string n) {
    Telephone *t = new Telephone(n);
    Fax* f = new Fax(n);
    SMS* s = new SMS(n);

    Contact *c = new Contact(t, f, s);
    c->sendAlarm();
    delete c;
}

int main()
{
    srand(time(NULL));
    createContact("0744586912");
    return 0;
}
