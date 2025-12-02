#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <stack>
#include <queue>
#include <initializer_list>
#include <mutex>    // Usado para Concurrence

using namespace std;

template <typename T>
class BinaryTree {
public:


    //  Nodo Interno
 
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T& v) : value(v), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;
    size_t n;
    mutable std::mutex mtx; // para Concurrence

public:

   
    // Constructor Copia

    BinaryTree(const BinaryTree& other) : root(nullptr), n(0) {
        std::lock_guard<std::mutex> lock(other.mtx);
        if (other.root)
            root = copySubtree(other.root);
        n = other.n;
    }

 
    //  Move Constructor

<<<<<<< HEAD
    BinaryTree(BinaryTree&& other) noexcept 
        : root(other.root), n(other.n) 
=======
template <typename Container>
class binary_tree_iterator : public general_iterator<Container,  class binary_tree_iterator<Container> > // 
{  
public:
    using Parent = class general_iterator<Container, binary_tree_iterator<Container> >;     \
    using Node   = typename Container::Node;
    using Container = binary_tree_iterator<Container>;

  public:
    binary_tree_iterator(Container *pContainer, Node *pNode) : Parent (pContainer,pNode) {}
    binary_tree_iterator(Container &other)  : Parent (other) {}
    binary_tree_iterator(Container &&other) : Parent(other) {} // Move constructor C++11 en adelante

public:
    // TODO: Fuentes Patrick
    binary_tree_iterator operator++() {
        Parent::m_pNode = Parent::m_pNode ? (Node*)Parent::m_pNode->getpNext() : nullptr;
        return *this;
    }
};

template <typename _T>
struct BinaryTreeAscTraits{
    using  T         = _T;
    using  Node      = CBinaryTreeNode<T>;
    using  CompareFn = less<T>;
};

template <typename _T>
struct BinaryTreeDescTraits{
    using  T         = _T;
    using  Node      = CBinaryTreeNode<T>;
    using  CompareFn = greater<T>;
};

template <typename Traits>
class CBinaryTree{
  public:
    using value_type    = typename Traits::T;
    using Node          = typename Traits::Node;
    
    using CompareFn     = typename Traits::CompareFn;
    using Container     = CBinaryTree<Traits>;
    using iterator      = binary_tree_iterator<Container>;

protected:
    Node    *m_pRoot = nullptr;
    size_t   m_size  = 0;
    CompareFn Compfn;
public: 
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }
    // TODO: insert must receive two paramaters: elem and LinkedValueType value
    void insert(value_type elem, Ref ref) {
        m_pRoot = internal_insert(elem, ref, nullptr, nullptr, m_pRoot);
    }

protected:
    Node* CreateNode(Node* pParent, value_type elem, Ref ref) {
        return new Node(pParent, elem, ref);
    }
    virtual Node* internal_insert(value_type elem, Ref ref, LinkedValueType value,
                          Node* pParent, Node*& rpOrigin)
>>>>>>> 0104a03d44ba12cd2ea0003860f373dc5bc775a9
    {
        other.root = nullptr;
        other.n = 0;
    }


    // Constructor Principal
  
    BinaryTree() : root(nullptr), n(0) {}


    // Destructor

    ~BinaryTree() {
        clear(root);
    }

private:

    // Copia recursiva
    Node* copySubtree(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->value);
        newNode->left = copySubtree(node->left);
        newNode->right = copySubtree(node->right);
        return newNode;
    }

    // Liberar memoria
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:


    // Insert
    void insert(const T& value) {
        lock_guard<mutex> lock(mtx);
        root = insertRec(root, value);
        n++;
    }

private:
    Node* insertRec(Node* node, const T& value) {
        if (!node) return new Node(value);

        if (value < node->value)
            node->left = insertRec(node->left, value);
        else
            node->right = insertRec(node->right, value);

        return node;
    }

public:

 
    // forward iterator
 
    class iterator {
        stack<Node*> st;

        void pushLeft(Node* n) {
            while (n) {
                st.push(n);
                n = n->left;
            }
        }

    public:
        iterator(Node* root) {
            pushLeft(root);
        }

        bool operator!=(const iterator& other) const {
            return st != other.st;
        }

        const T& operator*() const {
            return st.top()->value;
        }

        iterator& operator++() {
            Node* n = st.top(); st.pop();
            pushLeft(n->right);
            return *this;
        }
    };

    iterator begin() const { return iterator(root); }
    iterator end()   const { return iterator(nullptr); }


    // backward iterator

    class reverse_iterator {
        stack<Node*> st;

        void pushRight(Node* n) {
            while (n) {
                st.push(n);
                n = n->right;
            }
        }

    public:
        reverse_iterator(Node* root) {
            pushRight(root);
        }

        bool operator!=(const reverse_iterator& other) const {
            return st != other.st;
        }

        const T& operator*() const {
            return st.top()->value;
        }

        reverse_iterator& operator++() {
            Node* n = st.top(); st.pop();
            pushRight(n->left);
            return *this;
        }
    };

    reverse_iterator rbegin() const { return reverse_iterator(root); }
    reverse_iterator rend()   const { return reverse_iterator(nullptr); }


    // preorder (Variadic)

    template <typename F>
    void preorder(F f) const {
        preorderRec(root, f);
    }

    template <typename F>
    void preorderRec(Node* node, F& f) const {
        if (!node) return;
        f(node->value);
        preorderRec(node->left, f);
        preorderRec(node->right, f);
    }


    // inorder (Variadic)

    template <typename F>
    void inorder(F f) const {
        inorderRec(root, f);
    }

private:
    template <typename F>
    void inorderRec(Node* node, F& f) const {
        if (!node) return;
        inorderRec(node->left, f);
        f(node->value);
        inorderRec(node->right, f);
    }

public:

    // postorder (Variadic)

    template <typename F>
    void postorder(F f) const {
        postorderRec(root, f);
    }

private:
    template <typename F>
    void postorderRec(Node* node, F& f) const {
        if (!node) return;
        postorderRec(node->left, f);
        postorderRec(node->right, f);
        f(node->value);
    }

public:

 
    //  Write y operador <<
 
    friend ostream& operator<<(ostream& os, const BinaryTree& bt) {
        os << "{ ";
        bt.inorder([&](const T& v) { os << v << " "; });
        os << "}";
        return os;
    }

 
    // Read y operador >>

    friend istream& operator>>(istream& is, BinaryTree& bt) {
        T value;
        while (is >> value)
            bt.insert(value);
        return is;
    }

    //  print reutiliza inorden
    void print() const {
        inorder([](const T& v) {
            cout << v << " ";
        });
        cout << "\n";
    }

   
    // Concurrence 
    size_t size() const {
        lock_guard<mutex> lock(mtx);
        return n;
    }

    
<<<<<<< HEAD
=======
    CBinaryTree(Binary &&other)
        : m_pRoot(std::move(other.m_pRoot)), 
          m_size (std::move(other.m_size)), 
          Compfn (std::move(other.Compfn))
    { }

    // TODO: Selis Luis (Destructor)
    virtual ~CBinaryTree(){  } 
    
    // TODO: Quispe David
        void inorder  (ostream &os)    {   inorder  (m_pRoot, os, 0);  }
    // TODO: Quispe David
    void inorder(Node  *pNode, ostream &os, size_t level){
        if( pNode ){
            //Node *pParent = pNode->getParent();
            inorder(pNode->getChild(0), os, level+1);
            os << " --> " << pNode->getDataRef();
            inorder(pNode->getChild(1), os, level+1);
        }
    }

    // TODO: generalize this function by using iterators and apply any function
    // TODO: Quispe David
    void inorder(Node  *pNode, void (*visit) (value_type& item)){
        if( pNode ){   
            inorder(pNode->getChild(0), visit);
            (*visit)(pNode->getDataRef());
            inorder(pNode->getChild(1), visit);
        }
    }

    // Variadic templates (See foreach.h)
    // Este esta funcionando bien
    template <typename Function, typename... Args>
    void postorder(Function func, Args const&... args)
    {    postorder(m_pRoot, 0, func, args...);  }

    template <typename Function,typename... Args>
    void postorder(Node* pNode, size_t level, Function func, Args const&... args) {
        if (pNode) {
            postorder(pNode->getChild(0), level + 1, func, args...);
            postorder(pNode->getChild(1), level + 1, func, args...);
            func(pNode->GetDataRef(), level, args...); 
        }
    }
    // TODO: Villanueva Richard
    void preorder (ostream &os)    {   preorder (m_pRoot, os, 0);  }
    // TODO: Generalize this function by using iterators and apply any function
    // Create a new iterator to walk in postorder
    // TODO: Villanueva Richard
    void preorder(Node  *pNode, size_t level, ostream &os){
        //foreach(preorderbegin(), preorderend(), fn)
        if( pNode ){   
            os << " --> " << pNode->getDataRef();
            preorder(pNode->getChild(0), level+1, os);
            preorder(pNode->getChild(1), level+1, os);            
        }
    }

    void print    (ostream &os)    {   print    (m_pRoot, 0, os);  }
    // TODO: generalize this function by using iterators and apply any function
    void print(Node  *pNode, size_t level, ostream &os){
        if( pNode ){
            Node *pParent = pNode->getParent();
            print(pNode->getChild(1), level+1, os);
            os << string(" | ") * level << pNode->getDataRef() << "(" << (pParent?to_string(pParent->getData()):"Root") << ")" <<endl;
            print(pNode->getChild(0), level+1, os);
        }
    }

    // TODO: Open question for everyone
    // Generalizar el recorrido para recibir cualquier funcion
    // con una cantidad flexible de parametros conm variadic templates
    // https://en.cppreference.com/w/cpp/language/parameter_packs
    
    // TODO: Alcazar Joseph
    void postorder(Node  *pNode, size_t level, ostream &os){
        //foreach(postorderbegin(), postorderend(), fn)
        if( pNode ){   
            postorder(pNode->getChild(0), level+1, os);
            postorder(pNode->getChild(1), level+1, os);
            os << " --> " << pNode->getDataRef();
        }
    }

    // TODO: Arriola Aldo
    void Write(ostream &os) { os << *this;  }

    // TODO: Toledo Oscar
    void Read(istream &is)  { /* TODO */  }
>>>>>>> 0104a03d44ba12cd2ea0003860f373dc5bc775a9
};

#endif
