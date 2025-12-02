#ifndef __AVL_H__
#define __AVL_H__

#include <algorithm>
#include "binarytree.h"


//        NODO AVL

template <typename T>
class CAVLNode : public CBinaryTreeNode<T>{
public:
    using Base = CBinaryTreeNode<T>;

    int m_balanceFactor = 0;

    CAVLNode(const T& value)
        : Base(value), m_balanceFactor(0) {}
};


//               TRAITS ASCENDENTE


template <typename _T>
struct AVLAscTraits{
    using value_type = _T;
    using Node       = CAVLNode<_T>;
    using CompareFn  = std::less<_T>;
};


//             TRAITS DESCENDENTE


template <typename _T>
struct AVLDescTraits{
    using value_type = _T;
    using Node       = CAVLNode<_T>;
    using CompareFn  = std::greater<_T>;
};

template <typename Traits>
class CAVLTree : public CBinaryTree<Traits> {
public:
    using Base       = CBinaryTree<Traits>;
    using Node       = typename Traits::Node;
    using value_type = typename Traits::value_type;
    using CompareFn  = typename Traits::CompareFn;
    using Ref        = typename Base::Ref;

protected:

 
    //      UTILIDADES DE ARBOL AVL
 
    int height(Node* node) {
        return node ? node->m_height : 0;
    }

    int calcBalance(Node* node) {
        int hl = node->m_pLeft  ? node->m_pLeft->m_height  : 0;
        int hr = node->m_pRight ? node->m_pRight->m_height : 0;
        return hl - hr;
    }

    void updateNode(Node* node) {
        int hl = node->m_pLeft  ? node->m_pLeft->m_height  : 0;
        int hr = node->m_pRight ? node->m_pRight->m_height : 0;
        node->m_height = std::max(hl, hr) + 1;
        node->m_balanceFactor = hl - hr;
    }

  
    //         ROTACIONES AVL
  

    Node* rotateRight(Node* y) {
        Node* x  = (Node*)y->m_pLeft;
        Node* T2 = (Node*)x->m_pRight;

        x->m_pRight = y;
        y->m_pLeft  = T2;

        updateNode(y);
        updateNode(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y  = (Node*)x->m_pRight;
        Node* T2 = (Node*)y->m_pLeft;

        y->m_pLeft  = x;
        x->m_pRight = T2;

        updateNode(x);
        updateNode(y);

        return y;
    }


    //    INSERCIÓN AVL MODIFICADA
    

    Node* internal_insert(value_type &elem, Ref ref,
                          Node* pParent, Node*& node) override
    {
        CompareFn Compare;

        // Insertar como BST normal
        if (!node)
        {
            node = new Node(elem);
            Base::m_size++;
            return node;
        }

        if (Compare(elem, node->m_value))
            node->m_pLeft = internal_insert(elem, ref, node, (Node*&)node->m_pLeft);

        else if (Compare(node->m_value, elem))
            node->m_pRight = internal_insert(elem, ref, node, (Node*&)node->m_pRight);

        else
            return node; // duplicado

        // Actualizar altura y balance
        updateNode(node);

        int bf = node->m_balanceFactor;

      
        //   CASOS AVL
     

        // Left Left Case
        if (bf > 1 && Compare(elem, node->m_pLeft->m_value))
            return rotateRight(node);

        // Right Right Case
        if (bf < -1 && Compare(node->m_pRight->m_value, elem))
            return rotateLeft(node);

        // Left Right Case
        if (bf > 1 && Compare(node->m_pLeft->m_value, elem))
        {
            node->m_pLeft = rotateLeft((Node*)node->m_pLeft);
            return rotateRight(node);
        }

        // Right Left Case
        if (bf < -1 && Compare(elem, node->m_pRight->m_value))
        {
            node->m_pRight = rotateRight((Node*)node->m_pRight);
            return rotateLeft(node);
        }

        return node;
    }

public:

    //      CONSTRUCTOR

    CAVLTree() : Base() {}

};

#endif // __AVL_H__