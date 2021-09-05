/*********************************************************
 * Copyright (C) 2015 All rights reserved.
 * Author        : Ewen Dong
 * Email         : 
 * Last modified : 2015-08-25
 * Description   : 
 *********************************************************/

#include<string>
#include<boost/python.hpp>

using namespace std;
using namespace boost::python;

class World
{
public:
    void set(string msg) { this->msg = msg; }
    string greet() { return msg; }
    string msg;
};

BOOST_PYTHON_MODULE(hello) //导出的module 名字
{
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set);
}
