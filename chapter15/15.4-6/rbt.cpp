#include <algorithm>
#include "rbt.h"
void replace_node(struct IPH_Redblack_node* n, struct IPH_Redblack_node* child){
    child->parent = n->parent;
    if (n == n->parent->left)
        n->parent->left = child;
    else
        n->parent->right = child;
    child->left = n->left;
    child->right = n->right;
}

void Iph_delete_repair_right(IPH_Redblack_node * p,IPH_Redblack_node * root)
{
    IPH_Redblack_node *parent = p->parent;
    IPH_Redblack_node *temp;
    //case1 跟节点
    if(p == root) {
        cout<<"error repair right at root"<<endl;
        return ;
    }
    if(p->right && p->right->color == IPH_Redblack_node::Iph_red){
        ////case2 p->right为红节点
        p->right->color = IPH_Redblack_node::Iph_black;
    }else{//left为空或者为黑色
        //right为黑节点或者为黑色
        if(p->left->color == IPH_Redblack_node::Iph_red)
        {//缺黑高出节点的兄弟为红色
            //p 为黑色，left为红色，right为黑色
            p->rotate_right();
            int t = p->parent->color;
            p->parent->color = p->color;
            p->color = t;

            // 此处是否return 取决于之后是否处理这里的情况，p为红，左兄弟为黑色 return ;
        }
        //left right颜色为黑色

        if(p->left->color != IPH_Redblack_node::Iph_black)
            cout<<"error color 1"<<endl;

        if((p->left->left == 0 || p->left->left->color == IPH_Redblack_node::Iph_black) &&
                (p->left->right== 0 || p->left->right->color == IPH_Redblack_node::Iph_black))
        {
            if(p->color == IPH_Redblack_node::Iph_black )
            {
                p->left->color = IPH_Redblack_node::Iph_red;
                if(p == p->parent->left)
                    Iph_delete_repair_left(p->parent,root);
                else
                    Iph_delete_repair_right(p->parent,root);
                return ;
            }else{
                p->left->color = IPH_Redblack_node::Iph_red;
                p->color = IPH_Redblack_node::Iph_black;
            }
        }else{
            if(p->left->right &&  p->left->right->color == IPH_Redblack_node::Iph_red)
            {
                p->left->rotate_left();
                p->left->color = IPH_Redblack_node::Iph_black;
                p->left->left->color = IPH_Redblack_node::Iph_red;
            }
            p->rotate_right();
            p->parent->color = p->color;
            p->parent->left->color = IPH_Redblack_node::Iph_black;
            p->color = IPH_Redblack_node::Iph_black;
        }
    }
}
void Iph_delete_repair_left(IPH_Redblack_node * p,IPH_Redblack_node * root)
{
    if(p == root) {
        if(p->left != 0)
            p->left->color =IPH_Redblack_node::Iph_black;
        return ;
    }
    if(p->left && p->left->color == IPH_Redblack_node::Iph_red){
        p->left->color = IPH_Redblack_node::Iph_black;
    }else{
        if(p->right->color == IPH_Redblack_node::Iph_red)
        {
            p->rotate_left();
            p->color = IPH_Redblack_node::Iph_red;
            p->parent->color = IPH_Redblack_node::Iph_black;
        }

        if((p->right->right == 0 || p->right->right->color == IPH_Redblack_node::Iph_black) &&
                (p->right->left == 0  || p->right->left->color == IPH_Redblack_node::Iph_black))
        {
            if(p->color == IPH_Redblack_node::Iph_black)
            {
                p->right->color = IPH_Redblack_node::Iph_red;
                if(p == p->parent->left)
                    Iph_delete_repair_left(p->parent,root);
                else
                    Iph_delete_repair_right(p->parent,root);
            }
            else{
                p->color =IPH_Redblack_node::Iph_black;
                p->right->color = IPH_Redblack_node::Iph_red;
            }
        }else{
            if(p->right->left && p->right->left->color == IPH_Redblack_node::Iph_red)
            {
                p->right->rotate_right();
                p->right->color = IPH_Redblack_node::Iph_black;
                p->right->right->color = IPH_Redblack_node::Iph_red;
            }
            p->rotate_left();
            p->parent->color = p->color;
            p->parent->right->color = IPH_Redblack_node::Iph_black;
            p->color = IPH_Redblack_node::Iph_black;
        }
    }
}
void update_count(IPH_Redblack_node *p)
{
    int re = 0;
    if(p->left != 0){
        re += p->left->count;
    }
    if(p->right != 0){
        re += p->right->count;
    }
    p->count = re+1;
}


void IPH_Redblack_node::rotate_right()
{
    if(this->left == 0)
    {
        cout<<"rotate_right error"<<endl;
        return ;
    }
    IPH_Redblack_node * left = this->left;
    IPH_Redblack_node * parent = this->parent;

    this->left = left->right;
    if(this->left != 0)
        this->left->parent = this;

    left->right = this;
    this->parent = left;

    left->parent = parent;
    if(this  == parent->right)
    {
        parent->right = left;
    }else{
        parent->left = left;
    }
    update_count(this);
    update_count(this->parent);
    update_max(this);
    update_max(this->parent);
}


void IPH_Redblack_node::rotate_left()
{
    if(this->right == 0)
    {
        cout<<"rotate_left error"<<endl;
        return ;
    }
    IPH_Redblack_node * right = this->right;
    IPH_Redblack_node * parent = this->parent;

    this->right = right->left;
    if(this->right!=0)
        this->right->parent = this;

    right->left = this;
    this->parent = right;

    right->parent = parent;
    if(this == parent->left)
        parent->left = right;
    else
        parent->right = right;
    int temp = this->parent->count;

    update_count(this);
    update_count(this->parent);
    update_max(this);
    update_max(this->parent);
}


IPH_Redblack_node * IPH_Redblack_tree::Iph_find(int index)
{
    if(root.left == 0)
        return 0;
    if(index >= _count || index < 0){
      //  cout<<"error Iph_find"<<endl;
        return 0;
    }
    return root.left->find(index);
}

IPH_Redblack_node * IPH_Redblack_node::find(int index)
{
    IPH_Redblack_node *p = this;
    if(p->left!=0)
    {
        if(index < p->left->count){
            return p->left->find(index);
        }
        else if(index == p->left->count)
            return this;
        else{
            if(p->right == 0){
                cout<<"error find p->right"<<endl;
                return 0;
            }
            return p->right->find(index - p->left->count -1);
        }
    }else{
        if(index < 0)
        {
            cout<<"error find"<<endl;
        }else if(index == 0)
            return this;
        else{
            if(p->right == 0){
                cout<<"error find p->right 1"<<endl;
                return 0;
            }
            return p->right->find(index - 1);
            //if(index < 0) cout<<"error find"<<endl;
            //if(p->left == 0 && index == 0 (p->left !=0 && index == p->left->count+1)){
            //}
        }
    }

}
void printT(IPH_Redblack_node *n,int a)
{
    // for(int i = 0;i<a;i++)
    // 	cout<<" ";
    if(n!=0){
        cout<<"("<<n->key<<","<<n->color<<","<<n->count<<")"<<endl;
        for(int i = 0;i<a;i++)
            cout<<" ";
        cout<<"left:";
        printT(n->left,a+4);
        for(int i = 0;i<a;i++)
            cout<<" ";
        cout<<"right:";
        printT(n->right,a+4);

    }
    cout<<endl;
}

IPH_Redblack_node * IPH_Redblack_tree::Iph_insert(int key,int d)
{
    _count++;
    IPH_Redblack_node *p = new IPH_Redblack_node(key,d);
    IPH_Redblack_node *parent = &this->root;
    int data = 0;
    int data_max_key = key;
    int prev = -1;
    while(1)
    {
        parent->count++;
        if(key < parent->key)
        {
            if(parent->left == 0){
                parent->left = p;
                p->parent = parent;
                //	cout<<"cond1"<<endl;
                break;
            }
            parent = parent->left;
        }else{
        	if(parent->data > data)
        	{
        		data = parent->data;
        		prev = parent->key;
        	}
        	if(parent->left)
        	{
        		if(parent->left->data_max > data)
        		{
        			data = parent->left->data_max;
        			prev = parent->left->data_max_key;
        		}
        	}

            if(parent->right == 0){
                parent->right = p;
                p->parent = parent;
                //	cout<<"cond2"<<endl;
                break;
            }
            parent = parent->right;
        }
    }

    p->data = p->data_max = data+1;
    p->prev = prev;
    p->data_max_key = data_max_key;

    parent = p->parent;
    while(parent){
    	update_max(parent);
    	parent= parent->parent;
    }
    Iph_repair(p);
    return p;
}
void update_max(IPH_Redblack_node *p)
{
	int data_max = p->data;
	int data_max_key = p->key;
	if(p->left && p->left->data_max > data_max){
		data_max = p->left->data_max;
		data_max_key = p->left->data_max_key;
	} 

	if(p->right && p->right->data_max > data_max)
	{
		data_max = p->right->data_max;
		data_max_key = p->right->data_max_key;
	} 
	p->data_max = data_max;
	p->data_max_key = data_max_key;
}
void IPH_Redblack_tree::Iph_insert(int key)
{
    _count++;
    IPH_Redblack_node *p = new IPH_Redblack_node(key);
    IPH_Redblack_node *parent = &this->root;
    int data = 0;
    while(1)
    {
        parent->count++;
        if(key < parent->key)
        {
            if(parent->left == 0){
                parent->left = p;
                p->parent = parent;
                //	cout<<"cond1"<<endl;
                break;
            }
            parent = parent->left;
        }else{
            if(parent->right == 0){
                parent->right = p;
                p->parent = parent;
                //	cout<<"cond2"<<endl;
                break;
            }
            parent = parent->right;
        }
    }
    Iph_repair(p);
}

bool IPH_Check_color(IPH_Redblack_node &n,int a)
{
    bool re = true;
    if(n.color == IPH_Redblack_node::Iph_red)
    {
        if(n.left!=0&&n.left->color==IPH_Redblack_node::Iph_red)
        {
            cout<<"color error 1"<<endl;
            return false;
        }
        if(n.right!=0&&n.right->color==IPH_Redblack_node::Iph_red)
        {
            cout<<"color error 2"<<endl;

            return false;
        }
    }else{
        a--;
        if(n.right != 0)
        {
            re = re && IPH_Check_color(*(n.right),a);
        }else{
            if(a != 0)
            {
                cout<<"height error 1"<<endl;
                return false;
            }
        }
        if(n.left !=0){
            re = re && IPH_Check_color(*(n.left),a);
        }else{
            if(a != 0)
            {
                cout<<"height error 2"<<endl;
                return false;
            }
        }
    }
    return re;
}


static int height = 0;
int counter(IPH_Redblack_node *T)
{
    if(T!=0)
    {
        return 1 + counter(T->left) + counter(T->right);
    }
    return 0;
}

bool IPH_Check_count(IPH_Redblack_node * root)
{
    int re = 0;
    if(root->left != 0){
        re+= root->left->count;
        if(!IPH_Check_count(root->left))
            return false;
    }
    if(root->right != 0)
    {
        re += root->right->count;
        if(!IPH_Check_count(root->right))
            return false;
    }
    if(re +1 != root->count)
        return false;
    return true;
}
bool IPH_Check(IPH_Redblack_node *T,int count)
{
	if(count==0 && T==0)
		return true;
    if(T->color != IPH_Redblack_node::Iph_black)
    {
        cout<<"check root color problem"<<endl;
        return false;
    }
    height = 0;
    IPH_Redblack_node *p = T;
    while(p != 0)
    {
        if(p->color == IPH_Redblack_node::Iph_black)
            height++;
        p = p->left;
    }
    if(count != counter(T)){
        cout<<"counter error"<<endl;
        return false;
    }
    if(!IPH_Check_count(T))
        return false;
    return IPH_Check_color(*T,height);
}


void IPH_Redblack_tree::Iph_repair(IPH_Redblack_node *p)
{
    IPH_Redblack_node *parent = p->parent;
    if(parent == &this->root)
    {//case 1
        //	cout<<"check 2"<<endl;
        p->color = IPH_Redblack_node::Iph_black;
    }else if(parent->color == IPH_Redblack_node::Iph_black)
    {//case 2
        return ;
    }else{
        IPH_Redblack_node * uncle = parent->Iph_brother();
        if(parent->color == IPH_Redblack_node::Iph_red &&
                uncle!=0
                &&uncle->color == IPH_Redblack_node::Iph_red)
        {
            parent->color = IPH_Redblack_node::Iph_black;
            uncle->color = IPH_Redblack_node::Iph_black;
            parent->parent->color = IPH_Redblack_node::Iph_red;
            Iph_repair(parent->parent);
            return ;
        }else{
            if(!(uncle == 0 || uncle->color == IPH_Redblack_node::Iph_black))
            {
                cout<<"error condition"<<endl;
            }

            IPH_Redblack_node * pparent = parent->parent;
            if(pparent == &this->root) cout<<"error in Iph_repair"<<endl;

            if(pparent->left&&p == pparent->left->right)
            {
                parent->rotate_left();
                p = parent;
                parent = p->parent;
            }else if(pparent->right && p == pparent->right->left)
            {
                parent->rotate_right();
                p = parent;
                parent = p->parent;
            }

            if (parent == pparent->left)
            {
                /* code */
                pparent->rotate_right();
            }else
                pparent->rotate_left();
            parent->color =IPH_Redblack_node::Iph_black;
            pparent->color = IPH_Redblack_node::Iph_red;
        }
    }
}
bool IPH_Redblack_node::is_leaf()
{
    if(this->left == 0&&this->right == 0)
        return true;
    return false;
}
void Iph_swap_content(IPH_Redblack_node *n,IPH_Redblack_node *child)
{
    int temp = n->key;
    n->key = child->key;
    child->key = temp;
    temp = n->data;
    n->data = child->data;
    child->data = temp;
}
void IPH_Redblack_tree::Iph_delete(int key)
{
    IPH_Redblack_node *p = this->root.left;
    while(p)
    {//找到值为key的p
        if(p->key == key)
        {
            break;
        }else if(key < p->key){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    IPH_Redblack_node *replace = p;
    if(p)
    {
        //处理节点技术connt的问题 != &this->root
        //找到p的替代节点
        if(!p->is_leaf()){
            if(p->left != 0){
                p = p->left;
                while(p->right)
                {
                    p = p->right;
                }
            }else{
                p = p->right;
                while(p->left)
                {
                    p = p->left;
                }
            }
            if(p == replace) cout<<"error find replace"<<endl;
            Iph_swap_content(replace,p);
        }

        replace = p;
        while(replace)
        {
            replace->count--;
            replace = replace->parent;
        }
        this->_count--;

        IPH_Redblack_node *parent = p->parent;
        if(p->is_leaf())
        {
            if(p->color == IPH_Redblack_node::Iph_red){
                if(p == parent->left){
                    delete p;
                    parent->left = 0;
                }
                else{
                    delete p;
                    parent->right = 0;
                }
                return ;
            }else{
                if(p == parent->left){
                    delete p;
                    parent->left = 0;
                    Iph_delete_repair_left(parent,&(this->root));
                }
                else{
                    delete p;
                    parent->right = 0;
                    Iph_delete_repair_right(parent,&(this->root));
                }
            }
        }else{
            if(p->color != IPH_Redblack_node::Iph_black)
            {
                cout<<"error delete rule not match"<<endl;
            }
            if(p->left == 0) replace = p->right;
            else 		     replace = p->left;
            replace->parent = parent;
            if(p==parent->left){
                parent->left = replace;
                delete p;
                Iph_delete_repair_left(parent,&this->root);
            }
            else{
                parent->right = replace;
                delete  p;
                Iph_delete_repair_right(parent,&this->root);
            }
        }
    }
}
void check_delete(IPH_Redblack_tree & T)
{
    int c = 500;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,c);
    int dice_roll = distribution(generator);

    vector<bool> temp(c,true);
    for(int iter = 0;iter < 100;iter++)
    {
        for (int i = 0; i < c; ++i)
        {
            /* code */
            T.Iph_insert(i,i);
        }
        if(!IPH_Check(T.root.left,c))
        {
            cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
            printT(T.root.left,0);
            cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
        }
        int count =0;
        while(count != c)
        {
            dice_roll = distribution(generator);
            if(dice_roll < c && temp[dice_roll])
            {
                //cout<<" dice_roll = "<<dice_roll<<endl;
                if(count == c/2){
                    for (int h = 0; h < c - count; ++h)
                    {
                        IPH_Redblack_node *a = T.Iph_find(h);
                        if(a->data != a->key)
                            cout<<"error 3"<<endl;
                    }
                }
                count++;
                temp[dice_roll] = false;
                T.Iph_delete(dice_roll);
                if(T._count != T.root.count && T._count != c - count)
                {
                    cout <<"error 4 :"<<T.root.count<<" "<<T._count<<" "<<c - count<<endl;
                }

                if(!IPH_Check(T.root.left,c - count))
                {
                    cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
                    printT(T.root.left,0);
                    cout<<"\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
                }

            }
        }

        for (int i = 0; i < c; ++i)
        {
            temp[i] = true;
        }
        //
    }

    cout<<"check"<<endl;
}


IPH_Redblack_node * IPH_Redblack_node::predecessor()
{
	IPH_Redblack_node *p = this;
	if(p->left)
	{
		p = p->left;
		while(p->right)
			p = p->right;
		return p;
	}else{
		while(p == p->parent->left)
		{
			p = p->parent;
		}
		p = p->parent;
		if(p->parent == 0)
			return 0;
		return p;
	}
}
IPH_Redblack_node * IPH_Redblack_node::successor()
{
	IPH_Redblack_node *p = this;
	if(this->right)
	{
		p = this->right;
		while(p->left)
			p = p->left;
		return p;
	}else{
		while(p == p->parent->right)
		{
			p = p->parent;
		}
		p = p->parent;
		if(p->parent == 0)
			return 0;
		return p;
	}
}
