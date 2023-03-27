#include "state_machine.h"
#include "gtest/gtest.h"
#include <iostream>

//#define BOOST_TEST_DYN_LINK
// #include <boost/test/included/unit_test.hpp>
// #include <boost/test/tools/output_test_stream.hpp>


//using boost::test_tools::output_test_stream;



//using testing::internal::GetCapturedStdout;


struct state_msg{

	//std::string where = testing::internal::GetCapturedStdout(); 
	
};
class robot_machine_A : public ccl::state_machine<robot_machine_A>{
    public:
    robot_machine_A(){
        std::cout << "start::once,";
		transit(&robot_machine_A::start);
    }
    void run() override{
        (this->*state())();
    }
    void start(){
        once([&](){
            std::cout << "start::once,";
        });
        transit(&robot_machine_A::standby,[&](){
            std::cout << "start::transit,";
        });
    }
    void standby(){
        once([&](){
            std::cout << "standby::once,";
        });
        transit(&robot_machine_A::terminate);
    }
    void terminate(){
        once([&](){
            std::cout << "terminate::once,";
        });
        transit(&robot_machine_A::operation);
    } 

    void operation(){
        once([&](){
            std::cout << "operation::once,";
        });
        transit(&robot_machine_A::operation);
    }
    //state_msg m;
};


void func()
{
	std::cout<<"hello"<<std::endl;
}


TEST(state_machine, DefaultConstructor){

	testing::internal::CaptureStdout();
	robot_machine_A A;

	//func();

	std::string captured = testing::internal::GetCapturedStdout();


	//EXPECT_EQ(0, 0);
	EXPECT_EQ(captured, "start::once,");
}
