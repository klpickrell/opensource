#ifndef BYTE_SWAP__H
#define BYTE_SWAP__H

template< typename T >
T byteswap( const T& rhs )
{
    T result;
    const char* indexer = reinterpret_cast<const char*>( &rhs );
    char* result_indexer = reinterpret_cast<char*>( &result );
    for( int i = 0; i < sizeof( T ); ++i ) {
        result_indexer[i] = indexer[sizeof(T)-i-1];
    }

    return result;
}

#endif
