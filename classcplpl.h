#ifndef CLASSCPLPL_H
#define CLASSCPLPL_H

#include "unit.h"
#include "classunit.h"
#include "method.h"
#include "printoperator.h"

class CppClass : public ClassUnit {
public:
    CppClass( const std::string& name ) : ClassUnit( name ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level ) + "class " + getName() + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            if( getFields( i ).empty() ) {
                continue;
            }

            result += ACCESS_MODIFIERS[ i ] + ":\n";
            for( const auto& f : getFields( i ) ) {
                result += f->compile( level + 1 );
            }

            result += "\n";
        }
        result += generateShift( level ) + "};\n";

        return result;
    }
};

class CppMethod : public MethodUnit {
public:
    CppMethod( const std::string& name, const std::string& returnType, Flags flags ) :
        MethodUnit( name, returnType, flags ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level );
        if( getFlags() & STATIC ) {
            result += "static ";
        } else if( getFlags() & VIRTUAL ) {
            result += "virtual ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        if( getFlags() & CONST ) {
            result += " const";
        }

        result += " {\n";

        for( const auto& b : getBody() ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "}\n";

        return result;
    }
};

class CppPrintOperator : public PrintOperatorUnit {
public:
    CppPrintOperator( const std::string& text ) : PrintOperatorUnit( text ) { }

    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "printf( \"" + getText() + "\" );\n";
    }
};

#endif // CLASSCPLPL_H
