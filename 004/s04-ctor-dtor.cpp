#include <iostream>
#include <string>

class DestructorExample
{
  public:
    DestructorExample(std::string desMsg) 
    {
        this -> desMsg = desMsg;
    }

    
    ~DestructorExample() {
        std::cout << desMsg << '\n';
    };

    private:
        std::string desMsg;
};

void test() {
    auto test = DestructorExample("testEnd");
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
