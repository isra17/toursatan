#ifndef BASICTYPE_H
#define BASICTYPE_H

#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>

#define foreach         BOOST_FOREACH
#define reverse_foreach BOOST_REVERSE_FOREACH


//defini les type d'entier de base
typedef boost::int8_t Int8;
typedef boost::int16_t Int16;
typedef boost::int32_t Int32;

typedef boost::uint8_t UInt8;
typedef boost::uint16_t UInt16;
typedef boost::uint32_t UInt32;

#endif