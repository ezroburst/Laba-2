#ifndef CSH_H
#define CSH_H

#include "unit.h"
#include "classunit.h"
#include "method.h"
#include "printoperator.h"

class CshClass : public ClassUnit {
public:
    CshClass( const std::string& name ) : ClassUnit( name ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level ) + "class " + getName() + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            for( const auto& f : getFields( i ) ) {
                result += f->compile( level + 1 );
                result += "\n";
            }
        }
        result += generateShift( level ) + "}\n";

        return result;
    }
};

class CshMethod : public MethodUnit {
public:
    CshMethod( const std::string& name, const std::string& returnType, Flags flags ) :
        MethodUnit( name, returnType, flags ) { }

    std::string compile( unsigned int level = 0 ) const {
        std::string result = generateShift( level );

        // Учитываем флаг модификатора доступа
        if( getFlags() & PUBLIC ) {
            result += "public ";
        } else if( getFlags() & PROTECTED ) {
            result += "protected ";
        } else {
            result += "private ";
        }

        if( getFlags() & STATIC ) {
            result += "static ";
        } else if( !( getFlags() & VIRTUAL ) ) {
            result += "const ";
        }

        result += getReturnType() + " ";
        result += getName() + "()";

        result += " {\n";

        for( const auto& b : getBody() ) {
            result += b->compile( level + 1 );
        }

        result += generateShift( level ) + "}\n";

        return result;
    }
};



class CshPrintOperator : public PrintOperatorUnit {
public:
    CshPrintOperator( const std::string& text ) : PrintOperatorUnit( text ) { }

    std::string compile( unsigned int level = 0 ) const {
        return generateShift( level ) + "Console.WriteLine( \"" + getText() + "\" );\n";
    }
};


#endif // CSH_H
