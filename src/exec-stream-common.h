/*
Copyright (C)  2004 Artem Khodush

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef exec_stream_common_h
#define exec_stream_common_h

#include <list>
#include <cstddef>
#include <ios>

#include <libexecstream/exec-stream.h>

class thread_buffer_t;

// helper classes
class buffer_list_t {
public:
    struct buffer_t {
        std::size_t size;
        char *data;
    };

    buffer_list_t( );
    ~buffer_list_t( );

    void get( char *dst, std::size_t &size );
    void get_translate_crlf( char *dst, std::size_t &size );
    void put( char *const src, std::size_t size );
    void put_translate_crlf( char *const src, std::size_t size );
    buffer_t detach( );

    bool empty( );
    bool full( std::size_t limit ); // limit==0 -> no limit

    void clear( );

private:
    typedef std::list< buffer_t > buffers_t;
    buffers_t m_buffers;
    std::size_t m_read_offset; // offset into the first buffer
    std::size_t m_total_size;
};


// stream buffer class
class exec_stream_buffer_t : public std::streambuf {
public:
    exec_stream_buffer_t( exec_stream_t::stream_kind_t kind, thread_buffer_t &thread_buffer );
    virtual ~exec_stream_buffer_t( );

    void clear( );

protected:
    virtual int_type underflow( );
    virtual int_type overflow( int_type c );
    virtual int sync( );

private:
    bool send_buffer( );
    bool send_char( char c );

    exec_stream_t::stream_kind_t m_kind;
    thread_buffer_t &m_thread_buffer;
    char *m_stream_buffer;
};


// stream classes
class exec_istream_t : public std::istream {
public:
    exec_istream_t( exec_stream_buffer_t &buf )
        : std::istream( &buf ) {
    }
};


class exec_ostream_t : public std::ostream {
public:
    exec_ostream_t( exec_stream_buffer_t &buf )
        : std::ostream( &buf ) {
    }
};

#endif
