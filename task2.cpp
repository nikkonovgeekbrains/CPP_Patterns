#include <iostream>
#include <map>
#include <ctime>
#include <optional>

using namespace std;


class ISellSystem{
public:
    virtual void changePrice(std::string, float) = 0;
    virtual void sellProduct(std::string) = 0;
    virtual void addProduct(std::string, size_t) = 0;
};


class Automaton: ISellSystem {
private:
    std::string location;
    double spent_money;
    std::map <std::string, float> goods_price;
    std::map <std::string, float> goods_count;
    double recieved_money;
public:

    Automaton(const std::string &location, double recievedMoney) : location(location), recieved_money(recievedMoney) {
        spent_money = 0.0;
    }

    void changePrice(std::string name, float newPrice) override {
        goods_price[name] = newPrice;
    }

    void sellProduct(std::string name) override{
        if(goods_count[name] > 0){
            recieved_money += goods_price[name];
        }
        else{
            std::cerr << "Not enough goods" << std::endl;
        }
    }

    void addProduct(std::string name, size_t count){
        goods_count[name] += count;
    }

    double allMoneyReport() const{
        return recieved_money - spent_money;
    }

    const std::string& getLocationReport() const {
        return location;
    }

    const string goodsCountReport() const{
        string outp_str = "";
        for (auto& [product,count]: goods_count){
            outp_str.append( product +  ": " + to_string(count) + "\n");
        }
//        cout << outp_str << endl;
        return outp_str;
    };

    const string goodsPriceReport() const{
        string outp_str = "";
        for (auto& [product,price]: goods_price){
            outp_str.append( product +  ": " + to_string(price) + "\n");
        }
//        cout << outp_str << endl;
        return outp_str;
    };
};

class Proxy : public ISellSystem{
private:
    Automaton* _real_subject{};
     map<string, optional<time_t>> last_req_time = {
            {"location", nullopt},
            {"goods_count", nullopt},
            {"goods_price", nullopt},
            {"allmoney", nullopt}
    };
     double saved_all_money = 0;
     string saved_location = "";
     string saved_goods_price_rep;
     string saved_goods_count_rep;




public:
    Proxy(Automaton *real_subject) : _real_subject(new Automaton(*real_subject)) {}

    ~Proxy() {
        delete _real_subject;
    }

    void changePrice(std::string name, float newPrice) override {
        this-> _real_subject ->changePrice(name, newPrice);
    }

    void sellProduct(std::string name){
        this-> _real_subject ->sellProduct(name);
    }

    void addProduct(std::string name, size_t count){
        this-> _real_subject ->addProduct(name, count);
    }



    double allMoneyReport(){
        time_t cur_time = time(NULL);
        if(this->last_req_time.find("allmoney")->second.has_value()){
            if((cur_time - this->last_req_time.find("allmoney")->second.value())/3600<1 ){
                this->saved_all_money = this->_real_subject->allMoneyReport();
                this->last_req_time.find("allmoney")->second.value() = cur_time;
            }
        }
        else{
            this->saved_all_money = this->_real_subject->allMoneyReport();
            this->last_req_time.find("allmoney")->second.value() = cur_time;

        }
        return saved_all_money;
    }


    string& getLocationReport() {
        time_t cur_time = time(NULL);
        if(this->last_req_time.find("location")->second.has_value()){
            if((cur_time - this->last_req_time.find("location")->second.value())/3600<1 ){
                this->saved_location = this->_real_subject->getLocationReport();
                this->last_req_time.find("location")->second.value() = cur_time;
            }
        }
        else{
            this->saved_location = this->_real_subject->getLocationReport();
            this->last_req_time.find("location")->second.value() = cur_time;

        }
        return this->saved_location;
    }

    string goodsCountReport() {
        time_t cur_time = time(NULL);
        if(this->last_req_time.find("goods_count")->second.has_value()){
            if((cur_time - this->last_req_time.find("goods_count")->second.value())/3600<1 ){
                this->saved_goods_count_rep = this->_real_subject->goodsCountReport();
                this->last_req_time.find("goods_count")->second.value() = cur_time;
            }
        }
        else{
            this->saved_goods_count_rep = this->_real_subject->goodsCountReport();
            this->last_req_time.find("goods_count")->second.value() = cur_time;

        }
        return this->saved_goods_count_rep;
    }

    string goodsPriceReport() {
        time_t cur_time = time(NULL);
        if (this->last_req_time.find("goods_price")->second.has_value()) {
            if ((cur_time - this->last_req_time.find("goods_price")->second.value()) / 3600 < 1) {
                this->saved_goods_price_rep = this->_real_subject->goodsPriceReport();
                this->last_req_time.find("goods_price")->second.value() = cur_time;
            }
        } else {
            this->saved_goods_price_rep = this->_real_subject->goodsPriceReport();
            this->last_req_time.find("goods_price")->second.value() = cur_time;

        }
        return this->saved_goods_price_rep;
    }
};



int main() {
    cout << "PROXY" << endl;
    Automaton* real_subj = new Automaton("Moscow", 5000);
    Proxy* proxy1 = new Proxy(real_subj);
    proxy1->addProduct("prod2", 10);
    proxy1->changePrice("prod2", 100);
    cout << "loc: " << proxy1->getLocationReport() << endl;
    cout << "mon: " << proxy1->allMoneyReport() << endl;
    cout << "price: " << proxy1->goodsPriceReport() << endl;
    cout << "count: " << proxy1->goodsCountReport() << endl;


    return 0;
}