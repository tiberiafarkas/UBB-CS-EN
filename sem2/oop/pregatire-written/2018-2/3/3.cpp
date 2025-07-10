#include <iostream>
#include <vector>

using namespace std;

class SaleItem {
private:
    int code;
    double price;

public:
    SaleItem(int c, double p) : code{ c }, price{ p } {}
    ~SaleItem() {};
    int Code() {
        return code;
    }
    double Price() {
        return price;
    }
};

class Sale {
private:
    vector<SaleItem> sales;
public:
    vector<SaleItem> Sales() {
        return sales;
    }
    void add(SaleItem s) {
        sales.push_back(s);
    }
};

class Discount {
public:
    virtual double calc(Sale& s) = 0;
    virtual ~Discount() {};
};

class ItemDiscount : public Discount {
private:
    int code, percentage;
public:
    ItemDiscount(int code, int percentage) : code{ code }, percentage{ percentage } {}
    double calc(Sale& s) {
        double totalDiscount = 0;
        for (auto i : s.Sales()) {
            if (i.Code() == code)
                totalDiscount += i.Price() * percentage / 100.00;
        }
        return totalDiscount;
    }
    ~ItemDiscount() {}
};

class SumDiscount : public Discount {
private:
    vector<Discount*> discounts;
public:
    void add(Discount* d) {
        discounts.push_back(d);
    }

    double calc(Sale& s) override {
        double total = 0;
        for (auto i : discounts) {
            total += i->calc(s);
        }
        return total;
    }
    
    ~SumDiscount() {
        for (auto i : discounts) {
            delete i;
        }
    }
};

int main()
{
    SaleItem s1(0, 100);
    SaleItem s2(2, 140);
    SaleItem s3(1, 155);
    Sale s;
    s.add(s1);
    s.add(s2);
    s.add(s3);

    SumDiscount sum;
    sum.add(new ItemDiscount(0, 10));
    sum.add(new ItemDiscount(1, 10));
    sum.add(new ItemDiscount(2, 15));

    cout << sum.calc(s);

    return 0;

}

