#include <vector>
#include <iostream>
using namespace std;
// class ZigzagIterator {

//     vector<int>* v1_ptr,*v2_ptr;
//     int v1_idx,v2_idx, order;
// public:
//     /*
//     * @param v1: A 1d vector
//     * @param v2: A 1d vector
//     */ZigzagIterator(vector<int>& v1, vector<int>& v2) {
//         // do intialization if necessary
//         v1_ptr = &v1;
//         v2_ptr = &v2;
//         v1_idx = v2_idx = 0;
//         order = 1;
//     }

//     /*
//      * @return: An integer
//      */
//     int next() {
//         // write your code here
//         int ret;
//         if(order ==1){
//             if(v1_idx >= v1_ptr->size()){
//                 order = 2;
//                 return next();
//             }
//             ret = (*v1_ptr)[v1_idx++];
//             order = 2;
//         }else{
//             if(v2_idx >= v2_ptr->size())
//                 {
//                     order = 1;
//                     return next();
//                 }
//                 ret = (*v2_ptr)[v2_idx++];
//                 order =1;
//         }
//         return ret;
//     }

//     /*
//      * @return: True if has next
//      */
//     bool hasNext() {
//         // write your code here
//         return v1_idx < v1_ptr->size() || v2_idx < v2_ptr->size();
//     }
// };
class ZigzagIterator {

    vector<int>::iterator v1_it,v2_it,v1_end,v2_end;
    int order;
public:
    /*
    * @param v1: A 1d vector
    * @param v2: A 1d vector
    */ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        // do intialization if necessary
        v1_it =v1.begin();
        v2_it= v2.begin();
        v1_end = v1.end();
        v2_end = v2.end();
        order = 1;
    }

    /*
     * @return: An integer
     */
    int next() {
        // write your code here
        int ret;
        if(order ==1){
            if(v1_it == v1_end){
                order = 2;
                return next();
            }
            ret = *v1_it++;
            order = 2;
        }else{
            if(v2_it == v2_end)
                {
                    order = 1;
                    return next();
                }
                ret = *v2_it++;
                order =1;
        }
        return ret;
    }

    /*
     * @return: True if has next
     */
    bool hasNext() {
        // write your code here
        return v1_it != v1_end || v2_it != v2_end;
    }
};

// int main(){
//     vector<int> v1{1,2},v2{};
//     ZigzagIterator zz(v1,v2);
//     while(zz.hasNext())
//         cout << zz.next() << " ";
//     cout << endl;
//     return 0;
// }