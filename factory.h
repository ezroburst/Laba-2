#ifndef FACTORY_H
#define FACTORY_H

#include "unit.h"
#include "classunit.h"
#include "method.h"
#include "printoperator.h"
#include "classcplpl.h"
#include "classjava.h"
#include "csh.h"

class IFactory {
public:
    virtual ~IFactory() = default;

    virtual std::unique_ptr< ClassUnit > createClass( const std::string& name ) = 0;

    virtual std::unique_ptr< MethodUnit > createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) = 0;

    virtual std::unique_ptr< PrintOperatorUnit > createPrintOperator( const std::string& text ) = 0;
};



class CppFactory : public IFactory {
public:
    std::unique_ptr< ClassUnit > createClass( const std::string& name ) {
        return std::unique_ptr< ClassUnit >( new CppClass( name ) );
    }

    std::unique_ptr< MethodUnit > createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) {
        return std::unique_ptr< MethodUnit >( new CppMethod( name, returnType, flags ) );
    }

    std::unique_ptr< PrintOperatorUnit > createPrintOperator( const std::string& text ) {
        return std::unique_ptr< PrintOperatorUnit >( new CppPrintOperator( text ) );
    }
};


class JavaFactory : public IFactory {
public:
    std::unique_ptr< ClassUnit > createClass( const std::string& name ) {
        return std::unique_ptr< ClassUnit >( new JavaClass( name ) );
    }

    std::unique_ptr< MethodUnit > createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) {
        return std::unique_ptr< MethodUnit >( new JavaMethod( name, returnType, flags ) );
    }

    std::unique_ptr< PrintOperatorUnit > createPrintOperator( const std::string& text ) {
        return std::unique_ptr< PrintOperatorUnit >( new JavaPrintOperator( text ) );
    }
};


class CshFactory : public IFactory {
public:
    std::unique_ptr< ClassUnit > createClass( const std::string& name ) {
        return std::unique_ptr< ClassUnit >( new CshClass( name ) );
    }

    std::unique_ptr< MethodUnit > createMethod(
        const std::string& name,
        const std::string& returnType,
        Unit::Flags flags
    ) {
        return std::unique_ptr< MethodUnit >( new CshMethod( name, returnType, flags ) );
    }

    std::unique_ptr< PrintOperatorUnit > createPrintOperator( const std::string& text ) {
        return std::unique_ptr< PrintOperatorUnit >( new CshPrintOperator( text ) );
    }
};
#endif // FACTORY_H
