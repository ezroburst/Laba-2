#ifndef CLASSUNIT_H
#define CLASSUNIT_H

#include "unit.h"
#include "method.h"

class ClassUnit : public Unit {
public:
    enum AccessModifier {
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    static const std::vector< std::string > ACCESS_MODIFIERS;

    using Fields = std::vector< std::shared_ptr< Unit > >;

public:
    explicit ClassUnit( const std::string& name ) : m_name( name ) {
        m_fields.resize( ACCESS_MODIFIERS.size() );
    }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags - больше этот параметр не нужен */ = 0 ) {
            int accessModifier = PRIVATE;
            if( unit->getFlags() & MethodUnit::PUBLIC ) {
                accessModifier = PUBLIC;
            } else if( unit->getFlags() & MethodUnit::PROTECTED ) {
                accessModifier = PROTECTED;
            }

            m_fields[ accessModifier ].push_back( unit );
        }
    virtual ~ClassUnit(){}

protected:
    const std::string& getName() const { return m_name; }

    const Fields& getFields( unsigned int accessGroup ) const {
        if( ACCESS_MODIFIERS.size() <= accessGroup ) {
            throw std::out_of_range( "Invalid access group index" );
        }
        return m_fields[ accessGroup ];
    }

private:
    std::string m_name;
    std::vector< Fields > m_fields;

};
const std::vector< std::string > ClassUnit::ACCESS_MODIFIERS = { "public", "protected", "private" };


#endif // CLASSUNIT_H
