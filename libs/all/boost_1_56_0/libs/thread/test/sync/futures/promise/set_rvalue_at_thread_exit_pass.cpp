//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Copyright (C) 2011 Vicente J. Botet Escriba
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// <boost/thread/future.hpp>

// class promise<R>

// void promise::set_exception_at_thread_exit(exception_ptr p);

#define BOOST_THREAD_VERSION 3

#include <boost/thread/future.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/thread/detail/memory.hpp>
//#include <boost/interprocess/smart_ptr/unique_ptr.hpp>
#include <boost/thread/csbl/memory/unique_ptr.hpp>

//void func(boost::promise<boost::csbl::unique_ptr<int> > p)
boost::promise<boost::csbl::unique_ptr<int> > p;
void func()
{
  boost::csbl::unique_ptr<int> uptr(new int(5));
  p.set_value_at_thread_exit(boost::move(uptr));
}

int main()
{
  {
    //boost::promise<boost::csbl::unique_ptr<int> > > p;
    boost::future<boost::csbl::unique_ptr<int> > f = p.get_future();
    //boost::thread(func, boost::move(p)).detach();
    boost::thread(func).detach();
    BOOST_TEST(*f.get() == 5);
  }

  return boost::report_errors();
}

