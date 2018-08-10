#include <vector>
#include <random>
#include <algorithm>
#include"rbt.h"

int main()
{
    int n = 10;

    std::mt19937 generator;
    generator.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0,n-1);


    vector<bool> bool_vec(n,true);
    vector<int> vec;
    vector<int> re_vec;
    int count =0;
    IPH_Redblack_tree T;
    IPH_Redblack_node *p;
    int re = 0;
        while(count != n)
        {
         int dice_roll = distribution(generator);
         if(bool_vec[dice_roll])
            {
                count++;
                vec.push_back(dice_roll);
                bool_vec[dice_roll] = false;
            }
        }

        for(int i = 0;i<n;i++)
        {
            p = T.Iph_insert(vec[i],0);
        }
        int key = T.root.data_max_key;
        cout<<"data_max_key=  "<<key<<endl;
        p = T.Iph_find(key);
        while(p)
        {
            re_vec.push_back(p->key);
            p = T.Iph_find(p->prev);
        }
        reverse(re_vec.begin(),re_vec.end());
        for(int i = 0;i<n;i++)
            cout<<vec[i]<<" ";
        cout<<endl;
        for(int i = 0;i<re_vec.size();i++)
            cout<<re_vec[i]<<" ";
        cout<<" \n data max = "<<T.root.data_max<<endl;

    


    return 0;
    
}
