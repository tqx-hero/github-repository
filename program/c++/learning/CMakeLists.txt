cmake_minimum_required(VERSION 4.2)
project(ln)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件查找目录

# 可执行程序
add_executable(learning
        l1/ticket/main.cpp
        ticket/TicketMachine.cpp
        ticket/TicketMachine.h
        ticket/main.cpp
        new/NewDel.cpp
        new/NewDel.h
        new/main.cpp
        link/ListNode.cpp
        link/ListNode.h
        link/main.cpp
        link/LinkList.cpp
        link/LinkList.h
        link/Reverse_link.cpp
        constr/Initialization.cpp
        constr/Initialization.h
        extends/Parent.cpp
        extends/Parent.h
        extends/Child.cpp
        extends/Child.h
        extends/main.cpp
        const/main.cpp
        leet/Leet027.cpp
        reference/main.cpp
        virtual/main.cpp
        milti/main.cpp
        reference/m.cpp
        reference/qian_kaobei.cpp
        static/main.cpp
        oper/Integer.cpp
        learn/learn1.cpp
        learn/learn2.cpp
        learn/learn3.cpp
 "learn/learn4.cpp" "learn/prime_number.cpp" "learn/guess_number.cpp"
        learn/arr.cpp
        learn/arr2.cpp
        learn/vector.cpp
        learn/string.cpp
        learn/str2.cpp
        leet/leet3754.cpp
        leet/leet2058.cpp
        learn/ifstream.cpp
        learn/ofstream.cpp
        learn/struct.cpp
        learn/test.cpp
        learn/enums.h
        learn/arr3.cpp
        leet/leet3756.cpp
        leet/leet2074.cpp
        learn/ref.cpp
        learn/reverse_arr.cpp
        learn/func/print_str.cpp
        learn/func/main.cpp
        learn/tes.cpp
        learn/func/main.h
        learn/refs.cpp
        learn/arr4.cpp
        learn/digui/test.cpp
        learn/binary/binary_search.cpp
        learn/default_param.cpp
        learn/overload/overload.cpp
        learn/overload/main.cpp
        learn/class/main.cpp
        learn/class/cp.cpp
        learn/class/cp2.cpp
        learn/cpy/depth.cpp
        learn/static/sta.cpp
        learn/static/ts.cpp
        learn/friend/main.cpp
        leet/leet2487.cpp
        learn/friend/cls_friend.cpp
        learn/operator/main.cpp
        learn/operator/denghao.cpp
        learn/arr/myIArray.cpp
        learn/arr/myIArray.h
        learn/overload/test.cpp
        learn/overload/new.cpp
        learn/auto/auto_ptr.cpp
        learn/auto/auto_ptr.h
        learn/str/MyString.cpp
        learn/str/MyString.h
        learn/extends/student.cpp
        learn/extends/ext.cpp
        learn/extends/multi_ext.cpp
        learn/extends/duotai.cpp
        learn/virtual/main.cpp
        learn/virtual/v1.cpp
        learn/virtual/abs.cpp
        learn/virtual/example/Security.h
        learn/virtual/example/xuzhu.cpp
        learn/virtual/example/xuzhu.h
        learn/virtual/example/eastNoFail.cpp
        learn/virtual/example/eastNoFail.h
        learn/virtual/example/main.cpp
        learn/template/tem.cpp
        learn/template/add.cpp
        learn/template/class.cpp
        learn/template/persion.cpp  "learn/template/cpp_h/persion.hpp" "learn/template/cpp_h/main.cpp"
        learn/template/static.cpp
        learn/template/array/myArray.hpp
        learn/template/array/main.cpp
        learn/cast/static_cast.cpp
        learn/exception/main.cpp
        learn/exception/area.cpp
        learn/io/stdIo.cpp
        learn/io/format.cpp
        learn/template/decl/main.cpp
        learn/file/main.cpp
        learn/stl/iter.cpp
        learn/stl/str.cpp
        learn/stl/vec.cpp
        learn/stl/deque.cpp
        learn/stl/set.cpp
        learn/stl/pair.cpp
        learn/stl/func.cpp
        learn/stl/map.cpp
        learn/stl/multi.cpp
        learn/stl/fc.cpp
        learn/stl/bind.cpp
        learn/stl/func_bind.cpp
        learn/stl/search.cpp
        learn/stl/transform.cpp
        pracitce/pra1.cpp
        pracitce/const.cpp
        pracitce/mutable.cpp
        pracitce/new.cpp
        pracitce/cast/average.cpp
        pracitce/cast/test1.cpp
        pracitce/cast/average.h
        pracitce/name/file1.cpp
        pracitce/name/file2.cpp
        pracitce/variable/variable.cpp
        pracitce/transform.cpp
        pracitce/constructor.cpp
        pracitce/virtual.cpp
        pracitce/extends.cpp
        learn/exception/m.cpp
        learn/exception/unexcpeted.cpp
        learn/rtti/type.cpp
        learn/rtti/dynamic.cpp
        learn/智能指针/auto.cpp
        learn/lambda/la.cpp
        learn/可变参数/variables.cpp)

# 链接库
# Debug模式开启内存越界检测
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
#endif()