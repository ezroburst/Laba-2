#include <QCoreApplication>


#include "unit.h"
#include "classunit.h"
#include "method.h"
#include "printoperator.h"
#include "classcplpl.h"
#include "factory.h"


std::string generateProgram( const std::shared_ptr< IFactory >& factory ) {
    auto myClass = factory->createClass( "MyClass" );
    myClass->add( factory->createMethod( "testFunc1", "void", MethodUnit::PUBLIC ) );
    myClass->add( factory->createMethod( "testFunc2", "void", MethodUnit::STATIC ) );
    myClass->add(
        factory->createMethod(
              "testFunc3",
              "void",
              MethodUnit::VIRTUAL | MethodUnit::CONST | MethodUnit::PUBLIC
        )
    );

    std::shared_ptr< MethodUnit > method = factory->createMethod(
        "testFunc4", "void", MethodUnit::STATIC | MethodUnit::PROTECTED
    );
    method->add( factory->createPrintOperator( R"(Hello, world!\n)" ) );
    myClass->add( method );

    return myClass->compile();
}


int main(int argc, char *argv[])
{

    std::cout<<"CppCode"<<endl;
    std::cout << generateProgram( std::make_shared<CppFactory >() ) << std::endl;
    std::cout<<"JavaCode"<<endl;
    std::cout << generateProgram( std::make_shared<JavaFactory >() ) << std::endl;
    std::cout<<"CshCode"<<endl;
    std::cout << generateProgram( std::make_shared<CshFactory >() ) << std::endl;




    QCoreApplication a(argc, argv);

    return a.exec();
}
