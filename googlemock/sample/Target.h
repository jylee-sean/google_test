#include <iostream>
#include <string>
#include <memory>

// 외부 dependency를 갖고 있는 인터페이스
// server connection 이나 system, DB 관련 기능을 사용하는 경우 등이 있다.

class ExternalInterface {
public:
    // 가상의 ExternalInterface 에서 아래와 같이 3가지 기능을 제공한다고 생각해 보자.
    virtual void init() { std::cout << __FUNCTION__ << std::endl; }
    virtual int getInt(std::string prarm) = 0;
    virtual std::string getString(int param) = 0;
};



class Target {
public:
    Target(std::shared_ptr<ExternalInterface> ei) { this->ei = ei; }
   
    virtual ~Target() {}
    
    // ExternalInterface 클래스를 사용하지 않는 멤버 함수
    int testFunction1() { std::cout << __FUNCTION__ << std::endl; return 1; }
    int testFunction2() { std::cout << __FUNCTION__ << std::endl; return 2; }
    
    // ExternalInterface 클래스를 사용하는 멤버 함수
    void testFunction3() {
        std::cout << __FUNCTION__ << std::endl;
        ei->init();
    }
    
    int testFunction4(std::string param) {
        std::cout << __FUNCTION__ << std::endl;
        return ei->getInt(param);
    }
    
    std::string testFunction5(int param) { 
        std::cout << __FUNCTION__ << std::endl;
        std::cout << ei->getString(param) << std::endl;
        return ei->getString(param);
    }

protected:
    std::shared_ptr<ExternalInterface> ei;
};


