#ifndef IPH_RBT_H
#define IPH_RBT_H
#include <iostream>
#include <climits>
#include <vector>
#include <random>
using namespace std;
class IPH_Redblack_node{
    public:
        enum {Iph_red,Iph_black};
        IPH_Redblack_node(){
            parent=0;
            left = 0;
            right =0;
            count = 1;
            data = 0;
        }
        IPH_Redblack_node(int a):key(a){
            parent=0;data = 0;
            left = 0;data_max = 0;
            right =0;
            count = 1;
            data = 0;
            this->color = Iph_red;
        }
        IPH_Redblack_node(int a,int d):key(a){
            parent=0;data = 0;
            left = 0;data_max = 0;
            right =0;prev=-1;
            count = 1;data_max_key = a;
            data = d;
            this->color = Iph_red;
        }
        int key; //存储vec值
        int color;
        int count;
        int data; //存储包含当前key值的链长度。
        int prev;//前一个key值
        int data_max;//子树内最大链路长度值
        int data_max_key;//最大链路长度的key值
        IPH_Redblack_node *parent;
        IPH_Redblack_node *left;
        IPH_Redblack_node *right;
        IPH_Redblack_node *Iph_brother(){
            IPH_Redblack_node *p = this->parent;
            if(p == 0) return 0;
            else{
                if(this == p->left)
                    return p->right;
                else{
                    return p->left;
                }
            }
        }
        IPH_Redblack_node * predecessor();
        IPH_Redblack_node * successor();

        bool is_leaf();
        void rotate_left();
        void rotate_right();
        IPH_Redblack_node *  find(int index);
};
class IPH_Redblack_tree
{
    public:
        IPH_Redblack_tree():_count(0),root(INT_MAX){
            root.count = 0;
        }
        IPH_Redblack_node root;
        void Iph_insert(int key);

        IPH_Redblack_node * Iph_insert(int key,int d);
        void Iph_delete(int key);
        IPH_Redblack_node * Iph_find(int index);
        void Iph_repair(IPH_Redblack_node *p);
        int _count ;
};

void replace_node(struct IPH_Redblack_node* n, struct IPH_Redblack_node* child);
void Iph_delete_repair_left(IPH_Redblack_node * p,IPH_Redblack_node * root);
void Iph_delete_repair_right(IPH_Redblack_node * p,IPH_Redblack_node * root);
void update_count(IPH_Redblack_node *p);
void update_max(IPH_Redblack_node *p);
void printT(IPH_Redblack_node *n,int a);
bool IPH_Check_color(IPH_Redblack_node &n,int a);
int counter(IPH_Redblack_node *T);
bool IPH_Check_count(IPH_Redblack_node * root);
bool IPH_Check(IPH_Redblack_node *T,int count);
void Iph_swap_content(IPH_Redblack_node *n,IPH_Redblack_node *child);
void check_delete(IPH_Redblack_tree & T);

#endif