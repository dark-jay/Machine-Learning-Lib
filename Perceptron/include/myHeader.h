// User defined sizeof macro
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

template <class t>
int getArrSize(t arr){
    int size = my_sizeof(arr)/my_sizeof(arr[0]);
    return size;
}
