#include <iostream>
using namespace std;

template < class elemType >
class List
{
	public:
	elemType* p_data;
    int max_size;
	public:
    List(){p_data=NULL;max_size=0;};
    List(elemType data[], int size);
    List(const List& list);
	List operator+(const List list);
	List operator=(List list);
    ~List();
	
};

template < class elemType >
List<elemType>::List(elemType data[], int size)
{
    p_data = new elemType[size];
    max_size = size;
    for(int i=0; i<size; ++i)
    {
        p_data[i] = data[i];
    }
}

template < class elemType >
List<elemType>::List(const List& list)
{
	this->p_data = new elemType[list.max_size];
    this->max_size = list.max_size;
    for(int i=0; i<list.max_size; ++i)
    {
        this->p_data[i] = list.p_data[i];
    }
}

template < class elemType >
List<elemType> List<elemType>::operator+(const List list)
{
    elemType new_data[list.max_size + this->max_size];
    for(int i=0;i<this->max_size;++i)
    {
        new_data[i]=this->p_data[i];
    }
    for(int i=0;i<list.max_size;++i)
    {
        new_data[i+this->max_size]=list.p_data[i];
    }
    return List(new_data, list.max_size + this->max_size);
}

 template < class elemType >
List<elemType> List<elemType>::operator=(List list)
{
    this->p_data = new elemType[list.max_size];
    this->max_size = list.max_size;
    for(int i=0; i<list.max_size;++i)
    {
        this->p_data[i] = list.p_data[i];
    }
   return List(list.p_data, list.max_size); 
}

template < class elemType >
List<elemType>::~List<elemType>()
{
    if(p_data != NULL)
        delete [] p_data;
    p_data = NULL;
}

bool compareChar(char ch1[], char ch2[], int size)
{
    for(int i=0;i<size;i++)
    {
        if(ch1[i]==0||ch2[i]==0)
            break;
        if(ch1[i]!=ch2[i])
            return false;
    }
    return true;
}

int main(void)
{
    char input_type[6]={0};
    char char_int[6] = {'i','n','t','0','0','0'};
    char char_char[6] = {'c','h','a','r','0','0'};
    char char_double[6] = {'d','o','u','b','l','e'};
    cin >> input_type;
    int n,m;
    cin >> n >> m;
    if(compareChar(input_type,char_int,6))
    {  
        int *data1, *data2;
        data1 = new int[n];
        data2 = new int[m];
        for(int i=0; i<n; ++i)
            cin >> data1[i];
        for(int i=0; i<m; ++i)
            cin >> data2[i];

        List<int > list1(data1, n);
        List<int > list2(data2, m);
        List<int > list_new;
        list_new = list1 + list2;

        for(int i=0;i<n+m-1;++i)
            cout << list_new.p_data[i] << " ";

        cout << list_new.p_data[n+m-1] << endl;
        delete[] data1;
        delete[] data2;
    }
    else if(compareChar(input_type,char_char,6))
    {  
        char *data1, *data2;
        data1 = new char[n];
        data2 = new char[m];
        for(int i=0; i<n; ++i)
            cin >> data1[i];
        for(int i=0; i<m; ++i)
            cin >> data2[i];

        List<char > list1(data1, n), list2(data2, m);
        List<char > list_new;
        list_new = list1 + list2;
        for(int i=0;i<n+m-1;++i)
            cout << list_new.p_data[i] << " ";
        cout << list_new.p_data[n+m-1] << endl;
        delete[] data1;
        delete[] data2;
    }
    else if(compareChar(input_type,char_double,6))
    {  
        double *data1, *data2;
        data1 = new double[n];
        data2 = new double[m];
        for(int i=0; i<n; ++i)
            cin >> data1[i];
        for(int i=0; i<m; ++i)
            cin >> data2[i];

        List<double > list1(data1, n), list2(data2, m);
        List<double > list_new;
        list_new = list1 + list2;
        for(int i=0;i<n+m-1;++i)
            cout << list_new.p_data[i] << " ";
        cout << list_new.p_data[n+m-1] << endl;
        delete[] data1;
        delete[] data2;
    }

    return 0;
}
