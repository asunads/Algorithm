#include"rbt.h"

int main()
{
    IPH_Redblack_node node(2);
    IPH_Redblack_tree T;

    check_delete( T);
    for(int i = 0; i < 2048*8; ++i)
    {
        T.Iph_insert(i);
        IPH_Redblack_node * p  =T.Iph_find(i);
        if(p->key != i) {
            cout<<"error find"<<endl;
        }
        /* code */
        //	cout<<T.root.left->key<<endl;
        if(!IPH_Check(T.root.left,i+1))
        {
            cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
            printT(T.root.left,0);
            cout<<"error in  i = "<<i<<endl;
            cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
            return 0;
        }else{
            //  printT(T.root.left,0);
            //	cout<<"check pass "<<height<<endl;
        }
    }
    for(int i = 0;i<2048*8;i++)
    {
        IPH_Redblack_node * p  =T.Iph_find(i);
        if(i < 2048*8 - 1)
        {
            int x = p->successor()->key;
            if( x!= i+1)
            {
                cout<<"error successor x  = "<<x<<"i = "<<i<<endl;
                x = p->successor()->key;
            }
        }
        if(i > 0)
        {
            int x = p->predecessor()->key;
            if( x!= i-1)
            {
                cout<<"error predecessor x  = "<<x<<"i = "<<i<<endl;
                x = p->successor()->key;
            }
        }
        if(p->key != i) {
            cout<<"error find 2"<<endl;
        }
    }
    return 0;
    
}
