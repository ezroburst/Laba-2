#ifndef METHOD_H
#define METHOD_H

#include "unit.h"

class MethodUnit : public Unit {
public:
    enum Modifier {
        PUBLIC      = 1,
        PROTECTED   = 1 << 1,
        PRIVATE     = 1 << 2,
        STATIC      = 1 << 3,
        CONST       = 1 << 4,
        VIRTUAL     = 1 << 5
    };

public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags ) :
        m_name( name ), m_returnType( returnType ), m_flags( flags ) { }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) {
        m_body.push_back( unit );
    }

protected:
    const std::string& getName() const { return m_name; }
    const std::string& getReturnType() const { return m_returnType; }
    Flags getFlags() const { return m_flags; }
    const std::vector< std::shared_ptr< Unit > >& getBody() const { return m_body; }

private:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;

    std::vector< std::shared_ptr< Unit > > m_body;
};

#endif // METHOD_H
