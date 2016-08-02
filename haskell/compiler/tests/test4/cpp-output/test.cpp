#include "test.h"

namespace ADL {
namespace test {

CDate::CDate()
    : year(0)
    , month(0)
    , day(0)
{
}

CDate::CDate(
    const int16_t & year_,
    const int16_t & month_,
    const int16_t & day_
    )
    : year(year_)
    , month(month_)
    , day(day_)
{
}

bool
operator<( const CDate &a, const CDate &b )
{
    if( a.year < b.year ) return true;
    if( b.year < a.year ) return false;
    if( a.month < b.month ) return true;
    if( b.month < a.month ) return false;
    if( a.day < b.day ) return true;
    if( b.day < a.day ) return false;
    return false;
}

bool
operator==( const CDate &a, const CDate &b )
{
    return
        a.year == b.year &&
        a.month == b.month &&
        a.day == b.day ;
}

S::S()
    : v2(Date("2000-01-01"))
    , v4(CDate(2000,1,1))
{
}

S::S(
    const Date & v1_,
    const Date & v2_,
    const CDate & v3_,
    const CDate & v4_
    )
    : v1(v1_)
    , v2(v2_)
    , v3(v3_)
    , v4(v4_)
{
}

bool
operator<( const S &a, const S &b )
{
    if( a.v1 < b.v1 ) return true;
    if( b.v1 < a.v1 ) return false;
    if( a.v2 < b.v2 ) return true;
    if( b.v2 < a.v2 ) return false;
    if( a.v3 < b.v3 ) return true;
    if( b.v3 < a.v3 ) return false;
    if( a.v4 < b.v4 ) return true;
    if( b.v4 < a.v4 ) return false;
    return false;
}

bool
operator==( const S &a, const S &b )
{
    return
        a.v1 == b.v1 &&
        a.v2 == b.v2 &&
        a.v3 == b.v3 &&
        a.v4 == b.v4 ;
}

}}; // ADL::test

namespace ADL {

typename Serialiser<ADL::test::CDate>::Ptr
Serialisable<ADL::test::CDate>::serialiser( const SerialiserFlags &sf )
{
    typedef ADL::test::CDate _T;
    
    struct S_ : public Serialiser<_T>
    {
        S_( const SerialiserFlags & sf )
            : year_s( Serialisable<int16_t>::serialiser(sf) )
            , month_s( Serialisable<int16_t>::serialiser(sf) )
            , day_s( Serialisable<int16_t>::serialiser(sf) )
            {}
        
        
        typename Serialiser<int16_t>::Ptr year_s;
        typename Serialiser<int16_t>::Ptr month_s;
        typename Serialiser<int16_t>::Ptr day_s;
        
        void toJson( JsonWriter &json, const _T & v ) const
        {
            json.startObject();
            writeField<int16_t>( json, year_s, "year", v.year );
            writeField<int16_t>( json, month_s, "month", v.month );
            writeField<int16_t>( json, day_s, "day", v.day );
            json.endObject();
        }
        
        void fromJson( _T &v, JsonReader &json ) const
        {
            match( json, JsonReader::START_OBJECT );
            while( !match0( json, JsonReader::END_OBJECT ) )
            {
                readField( year_s, v.year, "year", json ) ||
                readField( month_s, v.month, "month", json ) ||
                readField( day_s, v.day, "day", json ) ||
                ignoreField( json );
            }
        }
    };
    
    return typename Serialiser<_T>::Ptr( new S_(sf) );
};

typename Serialiser<ADL::test::S>::Ptr
Serialisable<ADL::test::S>::serialiser( const SerialiserFlags &sf )
{
    typedef ADL::test::S _T;
    
    struct S_ : public Serialiser<_T>
    {
        S_( const SerialiserFlags & sf )
            : v1_s( Serialisable<Date>::serialiser(sf) )
            , v2_s( Serialisable<Date>::serialiser(sf) )
            , v3_s( Serialisable<ADL::test::CDate>::serialiser(sf) )
            , v4_s( Serialisable<ADL::test::CDate>::serialiser(sf) )
            {}
        
        
        typename Serialiser<Date>::Ptr v1_s;
        typename Serialiser<Date>::Ptr v2_s;
        typename Serialiser<ADL::test::CDate>::Ptr v3_s;
        typename Serialiser<ADL::test::CDate>::Ptr v4_s;
        
        void toJson( JsonWriter &json, const _T & v ) const
        {
            json.startObject();
            writeField<Date>( json, v1_s, "v1", v.v1 );
            writeField<Date>( json, v2_s, "v2", v.v2 );
            writeField<ADL::test::CDate>( json, v3_s, "v3", v.v3 );
            writeField<ADL::test::CDate>( json, v4_s, "v4", v.v4 );
            json.endObject();
        }
        
        void fromJson( _T &v, JsonReader &json ) const
        {
            match( json, JsonReader::START_OBJECT );
            while( !match0( json, JsonReader::END_OBJECT ) )
            {
                readField( v1_s, v.v1, "v1", json ) ||
                readField( v2_s, v.v2, "v2", json ) ||
                readField( v3_s, v.v3, "v3", json ) ||
                readField( v4_s, v.v4, "v4", json ) ||
                ignoreField( json );
            }
        }
    };
    
    return typename Serialiser<_T>::Ptr( new S_(sf) );
};

}; // ADL