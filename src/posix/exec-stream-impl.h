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

#ifndef exec_stream_impl_h
#define exec_stream_impl_h

#include <sys/types.h>

#include <string>

#include "exec-stream-helpers.h"

// exec_stream_t::impl_t
struct exec_stream_t::impl_t {
    impl_t();
    ~impl_t();
    
    void split_args( std::string const & program, std::string const & arguments );
    void split_args( std::string const & program, exec_stream_t::next_arg_t & next_arg );
    void start( std::string const & program );
    
    pid_t m_child_pid;
    int m_exit_code;
    unsigned long m_child_timeout;

    buf_t< char > m_child_args;
    buf_t< char * > m_child_argp;
    
    pipe_t m_in_pipe;
    pipe_t m_out_pipe;
    pipe_t m_err_pipe;

    thread_buffer_t m_thread;
    
    exec_stream_buffer_t m_in_buffer;
    exec_stream_buffer_t m_out_buffer;
    exec_stream_buffer_t m_err_buffer;

    exec_ostream_t m_in;
    exec_istream_t m_out;
    exec_istream_t m_err;

    void (*m_old_sigpipe_handler)(int);
};

#endif
