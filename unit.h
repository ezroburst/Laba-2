#ifndef UNIT_H
#define UNIT_H


#include <iostream>
#include <vector>
#include <memory>

using namespace std;


class Unit {
public:
using Flags = unsigned int;
public:
virtual ~Unit(){}
virtual void add( const std::shared_ptr< Unit >& /* unit */ ) {
            throw std::runtime_error( "Not supported" );
        }
virtual std::string compile( unsigned int level = 0 ) const = 0;
virtual Flags getFlags() const { return 0; }
protected:
virtual std::string generateShift( unsigned int level ) const
{
static const auto DEFAULT_SHIFT = " ";
std::string result;
for( unsigned int i = 0; i < level; ++i ) {
result += DEFAULT_SHIFT;
}
return result;
}
};


#endif // UNIT_H
